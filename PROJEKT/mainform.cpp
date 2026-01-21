#include "mainform.h"
#include <iostream>
#include <string>
#include <exception>
// Pamiêtaj o ustawieniu $(ProjectDir) w opcjach projektu
#include "serial/serial.h" 


using namespace System;
using namespace System::Windows::Forms;
void main(array<String^>^ args)
{	

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	UartWindow::mainform form;
	Application::Run(% form);

}

