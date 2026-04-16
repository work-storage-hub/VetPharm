#pragma once

#include "Theme.h"

namespace VetPharm
{
    public ref class PetEditorForm : public System::Windows::Forms::Form
    {
    public:
        PetEditorForm()
        {
            BuildUi();
        }

        void SetValues(System::String^ petName, System::String^ ownerName, System::String^ ownerPhone, System::String^ animalType, double weight, System::String^ allergies)
        {
            nameTextBox->Text = petName;
            ownerTextBox->Text = ownerName;
            ownerPhoneTextBox->Text = ownerPhone;
            animalTypeTextBox->Text = animalType;
            weightNumeric->Value = System::Decimal(weight);
            allergiesTextBox->Text = allergies;
        }

        property System::String^ PetName
        {
            System::String^ get() { return nameTextBox->Text->Trim(); }
        }

        property System::String^ OwnerName
        {
            System::String^ get() { return ownerTextBox->Text->Trim(); }
        }

        property System::String^ AnimalType
        {
            System::String^ get() { return animalTypeTextBox->Text->Trim(); }
        }

        property System::String^ OwnerPhone
        {
            System::String^ get() { return ownerPhoneTextBox->Text->Trim(); }
        }

        property double WeightValue
        {
            double get() { return System::Decimal::ToDouble(weightNumeric->Value); }
        }

        property System::String^ Allergies
        {
            System::String^ get() { return allergiesTextBox->Text->Trim(); }
        }

    private:
        System::Windows::Forms::TextBox^ nameTextBox;
        System::Windows::Forms::TextBox^ ownerTextBox;
        System::Windows::Forms::TextBox^ ownerPhoneTextBox;
        System::Windows::Forms::TextBox^ animalTypeTextBox;
        System::Windows::Forms::NumericUpDown^ weightNumeric;
        System::Windows::Forms::TextBox^ allergiesTextBox;

        void BuildUi()
        {
            Theme::ApplyForm(this, L"Карточка питомца");
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->ClientSize = System::Drawing::Size(500, 430);
            this->MinimizeBox = false;
            this->MaximizeBox = false;

            AddLabel(L"Кличка", 28, 28);
            nameTextBox = AddTextBox(28, 54, 200);

            AddLabel(L"Хозяин", 256, 28);
            ownerTextBox = AddTextBox(256, 54, 210);

            AddLabel(L"Телефон хозяина", 28, 100);
            ownerPhoneTextBox = AddTextBox(28, 126, 200);

            AddLabel(L"Вид животного", 256, 100);
            animalTypeTextBox = AddTextBox(256, 126, 210);

            AddLabel(L"Вес (кг)", 28, 172);
            weightNumeric = gcnew System::Windows::Forms::NumericUpDown();
            weightNumeric->Location = System::Drawing::Point(28, 198);
            weightNumeric->Size = System::Drawing::Size(200, 30);
            weightNumeric->DecimalPlaces = 2;
            weightNumeric->Maximum = System::Decimal(500);
            Theme::StyleInput(weightNumeric);

            AddLabel(L"Аллергии (через запятую)", 28, 244);
            allergiesTextBox = AddTextBox(28, 270, 438);
            allergiesTextBox->Multiline = true;
            allergiesTextBox->Height = 88;

            System::Windows::Forms::Button^ saveButton = gcnew System::Windows::Forms::Button();
            saveButton->Text = L"Сохранить";
            saveButton->Location = System::Drawing::Point(248, 374);
            saveButton->Size = System::Drawing::Size(104, 36);
            saveButton->DialogResult = System::Windows::Forms::DialogResult::OK;
            Theme::StylePrimaryButton(saveButton);

            System::Windows::Forms::Button^ cancelButton = gcnew System::Windows::Forms::Button();
            cancelButton->Text = L"Отмена";
            cancelButton->Location = System::Drawing::Point(362, 374);
            cancelButton->Size = System::Drawing::Size(104, 36);
            cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            Theme::StyleSecondaryButton(cancelButton);

            this->Controls->Add(weightNumeric);
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

        System::Windows::Forms::TextBox^ AddTextBox(int x, int y, int width)
        {
            System::Windows::Forms::TextBox^ box = gcnew System::Windows::Forms::TextBox();
            box->Location = System::Drawing::Point(x, y);
            box->Size = System::Drawing::Size(width, 30);
            Theme::StyleInput(box);
            this->Controls->Add(box);
            return box;
        }
    };
}
