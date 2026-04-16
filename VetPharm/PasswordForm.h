#pragma once

#include "DbHelpers.h"
#include "Theme.h"

namespace VetPharm
{
    public ref class PasswordForm : public System::Windows::Forms::Form
    {
    public:
        PasswordForm(System::String^ databasePath)
        {
            this->databasePath = databasePath;

            Theme::ApplyForm(this, L"VetPharm | Авторизация");
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->ClientSize = System::Drawing::Size(430, 320);
            this->MinimizeBox = false;
            this->MaximizeBox = false;

            titleLabel = gcnew System::Windows::Forms::Label();
            titleLabel->Text = L"Вход в VetPharm";
            titleLabel->Location = System::Drawing::Point(28, 24);
            titleLabel->Size = System::Drawing::Size(240, 32);
            titleLabel->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 18.0f);

            subtitleLabel = gcnew System::Windows::Forms::Label();
            subtitleLabel->Text = L"Введите логин и пароль пользователя из таблицы Users";
            subtitleLabel->Location = System::Drawing::Point(30, 64);
            subtitleLabel->Size = System::Drawing::Size(360, 40);
            subtitleLabel->ForeColor = Theme::TextMuted;

            usernameLabel = gcnew System::Windows::Forms::Label();
            usernameLabel->Text = L"Имя пользователя";
            usernameLabel->Location = System::Drawing::Point(30, 122);
            usernameLabel->Size = System::Drawing::Size(160, 24);
            usernameLabel->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.0f);

            usernameTextBox = gcnew System::Windows::Forms::TextBox();
            usernameTextBox->Location = System::Drawing::Point(30, 150);
            usernameTextBox->Size = System::Drawing::Size(360, 30);
            Theme::StyleInput(usernameTextBox);

            passwordLabel = gcnew System::Windows::Forms::Label();
            passwordLabel->Text = L"Пароль";
            passwordLabel->Location = System::Drawing::Point(30, 194);
            passwordLabel->Size = System::Drawing::Size(80, 24);
            passwordLabel->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.0f);

            passwordTextBox = gcnew System::Windows::Forms::TextBox();
            passwordTextBox->Location = System::Drawing::Point(30, 222);
            passwordTextBox->Size = System::Drawing::Size(360, 30);
            passwordTextBox->UseSystemPasswordChar = true;
            Theme::StyleInput(passwordTextBox);

            loginButton = gcnew System::Windows::Forms::Button();
            loginButton->Text = L"Войти";
            loginButton->Location = System::Drawing::Point(284, 268);
            loginButton->Size = System::Drawing::Size(106, 38);
            Theme::StylePrimaryButton(loginButton);
            loginButton->Click += gcnew System::EventHandler(this, &PasswordForm::loginButton_Click);

            this->Controls->Add(titleLabel);
            this->Controls->Add(subtitleLabel);
            this->Controls->Add(usernameLabel);
            this->Controls->Add(usernameTextBox);
            this->Controls->Add(passwordLabel);
            this->Controls->Add(passwordTextBox);
            this->Controls->Add(loginButton);
            this->AcceptButton = loginButton;
        }

    private:
        System::String^ databasePath;
        System::Windows::Forms::Label^ titleLabel;
        System::Windows::Forms::Label^ subtitleLabel;
        System::Windows::Forms::Label^ usernameLabel;
        System::Windows::Forms::TextBox^ usernameTextBox;
        System::Windows::Forms::Label^ passwordLabel;
        System::Windows::Forms::TextBox^ passwordTextBox;
        System::Windows::Forms::Button^ loginButton;

        System::Void loginButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (System::String::IsNullOrWhiteSpace(usernameTextBox->Text) || System::String::IsNullOrWhiteSpace(passwordTextBox->Text))
            {
                System::Windows::Forms::MessageBox::Show(
                    L"Введите имя пользователя и пароль.",
                    L"Авторизация",
                    System::Windows::Forms::MessageBoxButtons::OK,
                    System::Windows::Forms::MessageBoxIcon::Information);
                return;
            }

            if (DbHelpers::ValidateUserCredentials(databasePath, usernameTextBox->Text, passwordTextBox->Text))
            {
                this->DialogResult = System::Windows::Forms::DialogResult::OK;
                this->Close();
                return;
            }

            System::Windows::Forms::MessageBox::Show(
                L"Пользователь не найден или пароль неверный.",
                L"Доступ запрещён",
                System::Windows::Forms::MessageBoxButtons::OK,
                System::Windows::Forms::MessageBoxIcon::Warning);
            passwordTextBox->SelectAll();
            passwordTextBox->Focus();
        }
    };
}
