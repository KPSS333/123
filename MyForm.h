#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <string>
#include <math.h>
#include <mmsystem.h>
#include <Cfgmgr32.h>
#include <Setupapi.h>
#include <winioctl.h>
#include <devguid.h>
#include <sstream>
#include "usb_monitor.h"
#include <boost/function.hpp>
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <tchar.h>
#pragma comment(lib, "WinMM.Lib")
#define GENERIC_READ 0x80000000
#define GENERIC_WRITE 0x40000000
#define IOCTL_STORAGE_EJECT_MEDIA 0x0002D4808
#define FILE_SHARE_WRITE 0x00000002
#define OPEN_EXISTING 3
#define CREATE_ALWAYS 1
DEFINE_GUID( GUID_DEVCLASS_USB,0x36FC9E60, 0xC465, 0x11CF, 0x80, 0x56, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 );
DEFINE_GUID( GUID_DEVCLASS_DISKDRIVE,0x4d36e967L, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18 );

#pragma once

namespace Проект1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Collections::Generic;
	using namespace System::ComponentModel;
	using namespace System::Text;
	using namespace System::Threading::Tasks;
	using namespace System::Windows::Forms;
	using namespace System::Runtime::InteropServices;
	using namespace Microsoft::Win32;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		ArrayList^ Volumelabels;
		
		
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label9;


	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(115, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Список накопителей:";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(133, 6);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(74, 21);
			this->comboBox1->TabIndex = 5;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(213, 4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(142, 23);
			this->button1->TabIndex = 6;
			this->button1->Text = L"Получить информацию";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(213, 33);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(142, 23);
			this->button2->TabIndex = 7;
			this->button2->Text = L"Извлечь носитель";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::SystemColors::Control;
			this->groupBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->groupBox1->Controls->Add(this->label9);
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Location = System::Drawing::Point(15, 62);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(338, 203);
			this->groupBox1->TabIndex = 8;
			this->groupBox1->TabStop = false;
			this->groupBox1->Enter += gcnew System::EventHandler(this, &MyForm::groupBox1_Enter);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(6, 166);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(0, 13);
			this->label8->TabIndex = 6;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(6, 140);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(0, 13);
			this->label7->TabIndex = 5;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(6, 116);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(0, 13);
			this->label6->TabIndex = 4;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(6, 90);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(0, 13);
			this->label5->TabIndex = 3;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 65);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 13);
			this->label4->TabIndex = 2;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 42);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 13);
			this->label3->TabIndex = 1;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 16);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(0, 13);
			this->label2->TabIndex = 0;
			this->label2->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(15, 33);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(193, 23);
			this->button3->TabIndex = 9;
			this->button3->Text = L"Открыть дисковод";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(297, 187);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(0, 13);
			this->label9->TabIndex = 10;
			this->label9->Visible = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(365, 278);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->Text = L"Информационная панель";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		
	public: static int CloseHandle(HANDLE handle);

       
	public: static int DeviceIoControl
            (HANDLE deviceHandle, UInt32 ioControlCode,
              IntPtr inBuffer, int inBufferSize,
              IntPtr outBuffer, int outBufferSize,
              int bytesReturned, IntPtr overlapped);

      
	public: static IntPtr CreateFile
            (HANDLE filename, UInt32 desiredAccess,
              UInt32 shareMode, IntPtr securityAttributes,
              int creationDisposition, int flagsAndAttributes,
              IntPtr templateFile);
		

	public: Void EjectDrive(String^ driveLetter)
        {

			/*IntPtr CreateFile
            (String^ filename, UInt32 desiredAccess,
              UInt32 shareMode, IntPtr securityAttributes,
              int creationDisposition, int flagsAndAttributes,
              IntPtr templateFile);*/
			//HANDLE hF;
			//char drive_string[7];
			//wchar_t drive_letter;
			//LPCWSTR s = L"driveLetter";
			
	String^ path = "\\\\.\\" + driveLetter;
	TCHAR stdPath[30] = _T("\\\\.\\" + driveLetter);		
			HANDLE FileHandle;

FileHandle=CreateFile(path,GENERIC_READ |

GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_NEW,

FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);

CloseHandle(FileHandle);




            String^ path = "\\\\.\\" + driveLetter;
			//sprintf(drive_string, "\\\\.\\%c:", driveLetter);
			const TCHAR szCounterFileName[] = L"driveLetter";
			TCHAR stdPath[30] = TEXT("driveLetter");
			//const wchar_t i = Convert::ToSingle(drive_string);
			//char fName[100] = path;
			//hF = CreateFile(s,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
			HANDLE hDevice;  
			hDevice = CreateFile(stdPath,  // открываемое устройство
                    0,                // нет доступа к устройству
                    FILE_SHARE_READ | // режим совместного использования
                    FILE_SHARE_WRITE, 
					0,             // атрибуты безопасности по умолчанию
                    OPEN_EXISTING,    // расположение
                    0,                // атрибуты файла
                    0);            // не копировать атрибуты файла


           /* IntPtr^ handle = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0,
                IntPtr::Zero, OPEN_EXISTING, 0, IntPtr::Zero);*/

				if (hDevice = 0)
            {
                MessageBox::Show("Невозможно извлечь устройство!",
           "Извлечение устройств", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }
            int dummy = 0;
            DeviceIoControl(hDevice, IOCTL_STORAGE_EJECT_MEDIA, 0, 0,
                0, 0,  0, 0);
            int returnValue = DeviceIoControl(hDevice, IOCTL_STORAGE_EJECT_MEDIA,
				0, 0, 0, 0,  0, 0);
            CloseHandle(hDevice);
            MessageBox::Show("USB устройство, успешно извлечено!",
         "Извлечение устройств", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

	//

	//			void device_remove_failed(char letter)
	//			{
	//				std::cout << "Failed to eject device: " << letter << std::endl;
	//			}


	//		bool device_safe_removed(char letter)
	//			{
	//				
	//				std::wstringstream ss;
	//				ss << L"Разрешить извлечь диск " << static_cast<wchar_t>(letter) << L":?";
	//				if(MB_ICONQUESTION | MB_YESNO == IDYES)
	//				{
	//					std::cout << "Safe-removed USB disk: " << letter << std::endl;
	//					return true;
	//				}
	//				else
	//				{
	//					return false;
	//				}
	//			}

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
			array<DriveInfo^>^ allDriver=System::IO::DriveInfo::GetDrives();
			ArrayList^ Dirvernames=gcnew ArrayList(); 
			ArrayList^ Volumelabels=gcnew ArrayList(); 
			for each (DriveInfo^ d in allDriver)
			{
			Dirvernames->Add(d->Name);
				if(d->IsReady==true)
				{
					comboBox1->Items->Add(d->Name);
                    Volumelabels->Add(d->Name->Remove(2));
				}
			}			
			
	 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				// usb_monitor* mon = usb_monitor::create();
				 String^ strokaFormCmb;
				 strokaFormCmb = Convert::ToString(comboBox1->SelectedItem);
				 array<String^, 1>^ parts = strokaFormCmb->Split(gcnew array<Char, 1>{'/'}, System::StringSplitOptions::RemoveEmptyEntries);
				 String^ strokaFormCmb1 = Convert::ToString(parts[0]);
				 EjectDrive(strokaFormCmb);
				// String^ path = "\\\\.\\" + strokaFormCmb1;
				 /*
				IntPtr handle = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0,
                IntPtr::Zero, OPEN_EXISTING, 0, IntPtr::Zero);
				 mon->on_device_safe_remove(handle);
				 mon->on_device_remove_fail(handle);
				 device_safe_removed(strokaFormCmb1)*/;
			 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 
			 label1->Text = " "; 
			 label2->Text = " ";
			 label3->Text = " ";
			 label4->Text = " ";
			 label5->Text = " ";
			 label6->Text = " ";
			 label7->Text = " ";
			 label8->Text = " ";
			 array<DriveInfo^>^ allDriver=System::IO::DriveInfo::GetDrives();
			 for each (DriveInfo^ d in allDriver)
			{
				if(comboBox1->Text == d->Name)
				{
					 label1->Text = /*textBox1->Text + */"Тип диска: " + Convert::ToString(d->DriveType);//+ Environment::NewLine;
                    if (d->IsReady == true)
                    {						
                        label2->Text += "  Имя диска: " + d->Name + Environment::NewLine;
                        label3->Text += "  Файловая система: " + d->DriveFormat + Environment::NewLine;
                        label4->Text += "  Доступное пространство  : " + d->AvailableFreeSpace + " bytes"
                            + Environment::NewLine;
                        label5->Text += "  Общее доступное пространство: " + d->TotalFreeSpace + " bytes" + Environment::NewLine;
                        label6->Text += "  Общий размер диска : " + d->TotalSize + " bytes " + Environment::NewLine;
                        label7->Text += "  Доступность диска : " + d->IsReady + Environment::NewLine;
                        label8->Text += "  Метка тома диска : " + d->VolumeLabel + Environment::NewLine;
                    }
                }
		 }
}
private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 mciSendString(_T("Set cdaudio door open wait"), NULL, 0, NULL);
		 }
};
}