#pragma once
#include <memory>
#include <stdexcept>
#include <set>
#include <map>
#include <string>
#include <Windows.h>
#include <cfgmgr32.h>
#include <boost/function.hpp>

class usb_monitor_exception : public std::runtime_error
{
public:
	explicit usb_monitor_exception(const std::string& message);
};

class usb_monitor
{
public:
	//������� ������������ ��������� ������ usb_monitor
	//monitor_hard_drives - ����� ������������ ������� ������� ������
	static usb_monitor* create(bool monitor_hard_drives = false);

	//������� ��������� ������ �� ������
	static void remove();

	//��������� �������, ���������� ��� ���������� ������ USB flash-�����
	//������ ��������: void(char letter), ��� letter - ����� ������������� �����
	template<typename Handler>
	void on_device_add(Handler handler)
	{
		on_device_added_ = handler;
	}
	
	//��������� �������, ���������� ��� ������������ ���������� USB flash-�����
	//������ ��������: void(char letter), ��� letter - ����� ������������ �����
	template<typename Handler>
	void on_device_remove(Handler handler)
	{
		on_device_removed_ = handler;
	}
	
	//��������� �������, ���������� ��� ���������� ���������� USB flash-�����
	//������ ��������: bool(char letter), ��� letter - ����� ������������ �����
	//������� �� �������� false, ���� �� ������ ��������� ����������, ��� true � ��������� ������
	template<typename Handler>
	void on_device_safe_remove(Handler handler)
	{
		on_device_safe_removed_ = handler;
	}
	
	//��������� �������, ���������� ��� ��������� ���������� ���������� USB flash-�����
	//(������� ��� ����� ������ �������� ����������� ����)
	//������ ��������: void(char letter), ��� letter - ����� �����
	template<typename Handler>
	void on_device_remove_fail(Handler handler)
	{
		on_device_remove_failed_ = handler;
	}

	//������� ��� �������� ������������ ���������
	void on_device_add();
	void on_device_remove();
	void on_device_safe_remove();
	void on_device_remove_fail();

	//�������� ������������ USB
	void start();
	//������������� ������������ USB
	void stop();
	//�������� �� ������������ USB
	bool is_started() const;
	
	//�������� ����� ���� USB flash-������, ��������� � ������� � ������ ������ �������
	//���� include_usb_hard_drives == true, �� � ������ ������� ����� ������� ������� ������,
	//� ��������� ������ - ������ ������
	static std::set<wchar_t> get_flash_disks(bool include_usb_hard_drives);
	
	//����� ��� �������� ������������ USB-������
	//���� ���������� ��� ���� �������������, ������ �� ����������
	//��� ������� ���������������� ���������� ����� ������ ������� on_device_add
	void mount_existing_devices();
	
	//���������� ��� ������, ������� ����� ���� ����� ��� ��������
	void unmount_all_devices();

	//��������� ������� �����-���� ����������
	void safe_eject(char letter);

	//���������� ����� - ��������� �� ��������� USB-���������� ���� � ��� ������,
	//���� ����� ������� �� ���������� �� Windows ������ ������� �������� ������
	//�� ����������
	//�� ��������� ��������
	void set_safe_remove_on_timeout(bool remove);
	
	//�������� �� ����� ����������� ���������� ����� �������� �������� Windows
	bool is_set_safe_remove_on_timeout_on() const;

	//�������� ����� ������������ ������� ������� ������
	//�� ��������� �������� ����� ������������ ������ USB-������
	void enable_usb_hard_drive_monitoring(bool enable);

	//�������� �� ����� ������������ ������� ������� ������
	bool is_usb_hard_drive_monitoring_enabled() const;

	//��������������� ������� ��� ���������� ����������
	static void message_pump();

	//����������
	~usb_monitor();

private:
	explicit usb_monitor(bool monitor_hard_drives);
	usb_monitor(const usb_monitor&);
	usb_monitor& operator=(const usb_monitor&);

	bool started_, safe_remove_on_timeout_, monitor_hard_drives_;
	HWND mon_hwnd_;
	
	std::set<wchar_t> existing_usb_devices_;
	typedef std::map<size_t, std::pair<HDEVNOTIFY, wchar_t> > notifications;
	notifications existing_notifications_;

	static INT_PTR WINAPI WinProcCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static std::auto_ptr<usb_monitor> instanse_;

	void detect_changed_devices();
	void mount_device(wchar_t letter);
	void unmount_device(wchar_t letter, bool call_unsafe_callback = true);
	BOOL devices_changed(WPARAM wParam, LPARAM lParam);

	struct device_info
	{
		DEVINST dev_inst;
		GUID dev_class;
		long dev_number;
	};

	static const device_info get_device_info(char letter);

	boost::function<void(char)> on_device_added_;
	boost::function<void(char)> on_device_removed_;
	boost::function<bool(char)> on_device_safe_removed_;
	boost::function<void(char)> on_device_remove_failed_;

	static const std::wstring class_name;
};
