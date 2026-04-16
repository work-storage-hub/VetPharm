#include "MainForm.h"
#include "DbHelpers.h"
#include "PasswordForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	String^ dbPath = VetPharm::DbHelpers::ResolveDatabasePath();
	VetPharm::PasswordForm authForm(dbPath);
	if (authForm.ShowDialog() != DialogResult::OK)
	{
		return 0;
	}

	VetPharm::MainForm form;
	Application::Run(% form);
	return 0;
}
