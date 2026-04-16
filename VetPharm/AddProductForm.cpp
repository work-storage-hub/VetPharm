#include "AddProductForm.h"
#include "DbHelpers.h"

namespace VetPharm
{
    void AddProductForm::BuildUi()
    {
        productId = 0;

        Theme::ApplyForm(this, isEditMode ? L"Редактирование препарата" : L"Добавление препарата");
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->ClientSize = System::Drawing::Size(560, 380);
        this->MinimizeBox = false;
        this->MaximizeBox = false;

        AddLabel(L"Название", 28, 24);
        nameTextBox = AddTextBox(28, 50, 240);

        AddLabel(L"Категория", 292, 24);
        categoryComboBox = gcnew System::Windows::Forms::ComboBox();
        categoryComboBox->Location = System::Drawing::Point(292, 50);
        categoryComboBox->Size = System::Drawing::Size(240, 31);
        categoryComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
        Theme::StyleInput(categoryComboBox);

        AddLabel(L"Единица", 28, 98);
        unitComboBox = gcnew System::Windows::Forms::ComboBox();
        unitComboBox->Location = System::Drawing::Point(28, 124);
        unitComboBox->Size = System::Drawing::Size(240, 31);
        unitComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
        unitComboBox->Items->AddRange(gcnew cli::array<System::Object^> { L"миллилитры", L"граммы", L"таблетки", L"штуки", L"килограммы" });
        unitComboBox->SelectedIndex = 0;
        Theme::StyleInput(unitComboBox);

        AddLabel(L"Локация", 292, 98);
        locationComboBox = gcnew System::Windows::Forms::ComboBox();
        locationComboBox->Location = System::Drawing::Point(292, 124);
        locationComboBox->Size = System::Drawing::Size(240, 31);
        locationComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
        Theme::StyleInput(locationComboBox);

        AddLabel(L"Фасовка", 28, 172);
        packagingNumeric = gcnew System::Windows::Forms::NumericUpDown();
        packagingNumeric->Location = System::Drawing::Point(28, 198);
        packagingNumeric->Size = System::Drawing::Size(240, 30);
        packagingNumeric->Maximum = System::Decimal(100000);
        Theme::StyleInput(packagingNumeric);

        AddLabel(L"Количество", 292, 172);
        quantityNumeric = gcnew System::Windows::Forms::NumericUpDown();
        quantityNumeric->Location = System::Drawing::Point(292, 198);
        quantityNumeric->Size = System::Drawing::Size(240, 30);
        quantityNumeric->Maximum = System::Decimal(100000);
        Theme::StyleInput(quantityNumeric);

        AddLabel(L"Цена", 28, 246);
        priceNumeric = gcnew System::Windows::Forms::NumericUpDown();
        priceNumeric->Location = System::Drawing::Point(28, 272);
        priceNumeric->Size = System::Drawing::Size(240, 30);
        priceNumeric->Maximum = System::Decimal(1000000);
        Theme::StyleInput(priceNumeric);

        System::Windows::Forms::Button^ saveButton = gcnew System::Windows::Forms::Button();
        saveButton->Text = isEditMode ? L"Сохранить" : L"Добавить";
        saveButton->Location = System::Drawing::Point(314, 322);
        saveButton->Size = System::Drawing::Size(104, 36);
        saveButton->DialogResult = System::Windows::Forms::DialogResult::OK;
        Theme::StylePrimaryButton(saveButton);

        System::Windows::Forms::Button^ cancelButton = gcnew System::Windows::Forms::Button();
        cancelButton->Text = L"Отмена";
        cancelButton->Location = System::Drawing::Point(428, 322);
        cancelButton->Size = System::Drawing::Size(104, 36);
        cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
        Theme::StyleSecondaryButton(cancelButton);

        this->Controls->Add(categoryComboBox);
        this->Controls->Add(unitComboBox);
        this->Controls->Add(locationComboBox);
        this->Controls->Add(packagingNumeric);
        this->Controls->Add(quantityNumeric);
        this->Controls->Add(priceNumeric);
        this->Controls->Add(saveButton);
        this->Controls->Add(cancelButton);
        this->AcceptButton = saveButton;
        this->CancelButton = cancelButton;

        LoadLookups();
    }

    void AddProductForm::LoadLookups()
    {
        System::Data::DataTable^ categories = DbHelpers::LoadLookupTable(databasePath, L"Categories");
        System::Data::DataTable^ locations = DbHelpers::LoadLookupTable(databasePath, L"Locations");

        categoryComboBox->DisplayMember = L"name";
        categoryComboBox->ValueMember = L"id";
        categoryComboBox->DataSource = categories;

        locationComboBox->DisplayMember = L"name";
        locationComboBox->ValueMember = L"id";
        locationComboBox->DataSource = locations;
    }

    void AddProductForm::SetProductValues(int productId, System::String^ name, int categoryId, int locationId, int packagingSize, int quantity, System::String^ unit, int price)
    {
        this->productId = productId;
        nameTextBox->Text = name;
        categoryComboBox->SelectedValue = categoryId;
        locationComboBox->SelectedValue = locationId;
        packagingNumeric->Value = packagingSize;
        quantityNumeric->Value = quantity;
        unitComboBox->Text = unit;
        priceNumeric->Value = price;
    }

    bool AddProductForm::ValidateInput()
    {
        if (System::String::IsNullOrWhiteSpace(ProductName))
        {
            System::Windows::Forms::MessageBox::Show(L"Введите название препарата.", L"Проверка",
                System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Warning);
            return false;
        }

        if (SelectedCategoryId == 0 || SelectedLocationId == 0)
        {
            System::Windows::Forms::MessageBox::Show(L"Выберите категорию и локацию из базы данных.", L"Проверка",
                System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Warning);
            return false;
        }

        return true;
    }

    void AddProductForm::AddLabel(System::String^ text, int x, int y)
    {
        System::Windows::Forms::Label^ label = gcnew System::Windows::Forms::Label();
        label->Text = text;
        label->Location = System::Drawing::Point(x, y);
        label->Size = System::Drawing::Size(160, 22);
        label->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.0f);
        this->Controls->Add(label);
    }

    System::Windows::Forms::TextBox^ AddProductForm::AddTextBox(int x, int y, int width)
    {
        System::Windows::Forms::TextBox^ box = gcnew System::Windows::Forms::TextBox();
        box->Location = System::Drawing::Point(x, y);
        box->Size = System::Drawing::Size(width, 30);
        Theme::StyleInput(box);
        this->Controls->Add(box);
        return box;
    }
}
