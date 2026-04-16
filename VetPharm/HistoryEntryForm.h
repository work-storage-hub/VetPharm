#pragma once

#include "Theme.h"

namespace VetPharm
{
    public ref class HistoryEntryForm : public System::Windows::Forms::Form
    {
    public:
        HistoryEntryForm(System::Data::DataTable^ productsTable)
        {
            this->productsTable = productsTable;
            BuildUi();
        }

        property int ProductId
        {
            int get() { return productComboBox->SelectedValue == nullptr ? 0 : safe_cast<int>(productComboBox->SelectedValue); }
        }

        property System::String^ ProductName
        {
            System::String^ get() { return productComboBox->Text; }
        }

        property System::String^ ActionType
        {
            System::String^ get() { return actionTypeComboBox->Text; }
        }

        property System::String^ ActionDate
        {
            System::String^ get() { return datePicker->Value.ToString(L"yyyy-MM-dd HH:mm:ss"); }
        }

        property System::String^ Notes
        {
            System::String^ get() { return notesTextBox->Text->Trim(); }
        }

    private:
        System::Data::DataTable^ productsTable;
        System::Windows::Forms::ComboBox^ productComboBox;
        System::Windows::Forms::ComboBox^ actionTypeComboBox;
        System::Windows::Forms::DateTimePicker^ datePicker;
        System::Windows::Forms::TextBox^ notesTextBox;

        void BuildUi()
        {
            Theme::ApplyForm(this, L"Запись в историю питомца");
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->ClientSize = System::Drawing::Size(520, 340);
            this->MinimizeBox = false;
            this->MaximizeBox = false;

            AddLabel(L"Препарат", 28, 28);
            productComboBox = gcnew System::Windows::Forms::ComboBox();
            productComboBox->Location = System::Drawing::Point(28, 54);
            productComboBox->Size = System::Drawing::Size(462, 31);
            productComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            productComboBox->DisplayMember = L"name";
            productComboBox->ValueMember = L"id";
            productComboBox->DataSource = productsTable;
            Theme::StyleInput(productComboBox);

            AddLabel(L"Тип действия", 28, 98);
            actionTypeComboBox = gcnew System::Windows::Forms::ComboBox();
            actionTypeComboBox->Location = System::Drawing::Point(28, 124);
            actionTypeComboBox->Size = System::Drawing::Size(220, 31);
            actionTypeComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            actionTypeComboBox->Items->AddRange(gcnew cli::array<System::Object^> { L"purchase", L"procedure" });
            actionTypeComboBox->SelectedIndex = 0;
            Theme::StyleInput(actionTypeComboBox);

            AddLabel(L"Дата", 270, 98);
            datePicker = gcnew System::Windows::Forms::DateTimePicker();
            datePicker->Location = System::Drawing::Point(270, 124);
            datePicker->Size = System::Drawing::Size(220, 30);
            datePicker->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
            datePicker->CustomFormat = L"dd.MM.yyyy HH:mm";
            Theme::StyleInput(datePicker);

            AddLabel(L"Примечания", 28, 172);
            notesTextBox = gcnew System::Windows::Forms::TextBox();
            notesTextBox->Location = System::Drawing::Point(28, 198);
            notesTextBox->Size = System::Drawing::Size(462, 80);
            notesTextBox->Multiline = true;
            Theme::StyleInput(notesTextBox);

            System::Windows::Forms::Button^ saveButton = gcnew System::Windows::Forms::Button();
            saveButton->Text = L"Добавить";
            saveButton->Location = System::Drawing::Point(274, 292);
            saveButton->Size = System::Drawing::Size(104, 36);
            saveButton->DialogResult = System::Windows::Forms::DialogResult::OK;
            Theme::StylePrimaryButton(saveButton);

            System::Windows::Forms::Button^ cancelButton = gcnew System::Windows::Forms::Button();
            cancelButton->Text = L"Отмена";
            cancelButton->Location = System::Drawing::Point(386, 292);
            cancelButton->Size = System::Drawing::Size(104, 36);
            cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            Theme::StyleSecondaryButton(cancelButton);

            this->Controls->Add(productComboBox);
            this->Controls->Add(actionTypeComboBox);
            this->Controls->Add(datePicker);
            this->Controls->Add(notesTextBox);
            this->Controls->Add(saveButton);
            this->Controls->Add(cancelButton);
            this->AcceptButton = saveButton;
            this->CancelButton = cancelButton;
        }

        void AddLabel(System::String^ text, int x, int y)
        {
            System::Windows::Forms::Label^ label = gcnew System::Windows::Forms::Label();
            label->Text = text;
            label->Location = System::Drawing::Point(x, y);
            label->Size = System::Drawing::Size(200, 22);
            label->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.0f);
            this->Controls->Add(label);
        }
    };
}
