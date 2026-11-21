#include "MyForm1.h"
#include <Windows.h>

using namespace Finals;
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<System::String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    Finals::MyForm form;
    Application::Run(% form);

    return 0;
}
