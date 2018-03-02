#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ arg)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Проект1::MyForm form; 
	Application::Run(%form);

}

int Проект1::MyForm::CloseHandle(HANDLE  handle)
{
	return 0;
}

int Проект1::MyForm::DeviceIoControl(HANDLE deviceHandle, UInt32 ioControlCode, IntPtr inBuffer, int inBufferSize, IntPtr outBuffer, int outBufferSize, int bytesReturned, IntPtr overlapped)
{
	return 0;
}

IntPtr Проект1::MyForm::CreateFile(HANDLE filename, UInt32 desiredAccess, UInt32 shareMode, IntPtr securityAttributes, int creationDisposition, int flagsAndAttributes, IntPtr templateFile)
{
	return IntPtr();
}
