#pragma once

#include "Theme.h"

namespace VetPharm
{
    public ref class AddProductForm : public System::Windows::Forms::Form
    {
    public:
        AddProductForm(System::String^ databasePath, bool isEditMode)
        {
            this->databasePath = databasePath;
            this->isEditMode = isEditMode;
            BuildUi();
        }

        void SetProductValues(int productId, System::String^ name, int categoryId, int locationId, int packagingSize, int quantity, System::String^ unit, int price);

        property int ProductId
        {
            int get() { return productId; }
        }

        property System::String^ ProductName
        {
            System::String^ get() { return nameTextBox->Text->Trim(); }
        }

        property int SelectedCategoryId
        {
            int get() { return categoryComboBox->SelectedValue == nullptr ? 0 : safe_cast<int>(categoryComboBox->SelectedValue); }
        }

        property System::String^ SelectedCategoryName
        {
            System::String^ get() { return categoryComboBox->Text; }
        }

        property int SelectedLocationId
        {
            int get() { return locationComboBox->SelectedValue == nullptr ? 0 : safe_cast<int>(locationComboBox->SelectedValue); }
        }

        property System::String^ SelectedLocationName
        {
            System::String^ get() { return locationComboBox->Text; }
        }

        property int PackagingSize
        {
            int get() { return System::Decimal::ToInt32(packagingNumeric->Value); }
        }

        property int Quantity
        {
            int get() { return System::Decimal::ToInt32(quantityNumeric->Value); }
        }

        property System::String^ Unit
        {
            System::String^ get() { return unitComboBox->Text; }
        }

        property int Price
        {
            int get() { return System::Decimal::ToInt32(priceNumeric->Value); }
        }

        bool ValidateInput();

    private:
        System::String^ databasePath;
        bool isEditMode;
        int productId;
        System::Windows::Forms::TextBox^ nameTextBox;
        System::Windows::Forms::ComboBox^ categoryComboBox;
        System::Windows::Forms::ComboBox^ locationComboBox;
        System::Windows::Forms::ComboBox^ unitComboBox;
        System::Windows::Forms::NumericUpDown^ packagingNumeric;
        System::Windows::Forms::NumericUpDown^ quantityNumeric;
        System::Windows::Forms::NumericUpDown^ priceNumeric;

        void BuildUi();
        void LoadLookups();
        void AddLabel(System::String^ text, int x, int y);
        System::Windows::Forms::TextBox^ AddTextBox(int x, int y, int width);
    };
}
