#pragma once

#include "Theme.h"

namespace VetPharm
{
    public ref class TextInputDialog : public System::Windows::Forms::Form
    {
    public:
        TextInputDialog(System::String^ caption, System::String^ prompt, System::String^ initialValue)
        {
            Theme::ApplyForm(this, caption);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->ClientSize = System::Drawing::Size(420, 180);
            this->MinimizeBox = false;
            this->MaximizeBox = false;

            promptLabel = gcnew System::Windows::Forms::Label();
            promptLabel->Text = prompt;
            promptLabel->Location = System::Drawing::Point(24, 24);
            promptLabel->Size = System::Drawing::Size(360, 24);
            promptLabel->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.0f);

            valueTextBox = gcnew System::Windows::Forms::TextBox();
            valueTextBox->Location = System::Drawing::Point(24, 64);
            valueTextBox->Size = System::Drawing::Size(360, 30);
            valueTextBox->Text = initialValue;
            Theme::StyleInput(valueTextBox);

            okButton = gcnew System::Windows::Forms::Button();
            okButton->Text = L"Сохранить";
            okButton->Location = System::Drawing::Point(164, 116);
            okButton->Size = System::Drawing::Size(106, 36);
            okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
            Theme::StylePrimaryButton(okButton);

            cancelButton = gcnew System::Windows::Forms::Button();
            cancelButton->Text = L"Отмена";
            cancelButton->Location = System::Drawing::Point(278, 116);
            cancelButton->Size = System::Drawing::Size(106, 36);
            cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            Theme::StyleSecondaryButton(cancelButton);

            this->Controls->Add(promptLabel);
            this->Controls->Add(valueTextBox);
            this->Controls->Add(okButton);
            this->Controls->Add(cancelButton);
            this->AcceptButton = okButton;
            this->CancelButton = cancelButton;
        }

        property System::String^ Value
        {
            System::String^ get()
            {
                return valueTextBox->Text->Trim();
            }
        }

    private:
        System::Windows::Forms::Label^ promptLabel;
        System::Windows::Forms::TextBox^ valueTextBox;
        System::Windows::Forms::Button^ okButton;
        System::Windows::Forms::Button^ cancelButton;
    };
}
