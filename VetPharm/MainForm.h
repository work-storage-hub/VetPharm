#pragma once

namespace VetPharm
{
    public ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm(void);

    protected:
        ~MainForm();

    private:
        System::ComponentModel::Container^ components;
        System::String^ databasePath;

        System::Windows::Forms::Label^ titleLabel;
        System::Windows::Forms::Label^ subtitleLabel;
        System::Windows::Forms::TabControl^ mainTabs;

        System::Windows::Forms::TabPage^ inventoryTab;
        System::Windows::Forms::TextBox^ productSearchBox;
        System::Windows::Forms::ComboBox^ productCategoryFilter;
        System::Windows::Forms::ComboBox^ productLocationFilter;
        System::Windows::Forms::DataGridView^ productsGrid;
        System::Windows::Forms::Button^ addProductButton;
        System::Windows::Forms::Button^ editProductButton;
        System::Windows::Forms::Button^ deleteProductButton;

        System::Windows::Forms::TabPage^ categoriesTab;
        System::Windows::Forms::DataGridView^ categoriesGrid;
        System::Windows::Forms::Button^ addCategoryButton;
        System::Windows::Forms::Button^ editCategoryButton;
        System::Windows::Forms::Button^ deleteCategoryButton;

        System::Windows::Forms::TabPage^ locationsTab;
        System::Windows::Forms::DataGridView^ locationsGrid;
        System::Windows::Forms::Button^ addLocationButton;
        System::Windows::Forms::Button^ editLocationButton;
        System::Windows::Forms::Button^ deleteLocationButton;

        System::Windows::Forms::TabPage^ petsTab;
        System::Windows::Forms::TextBox^ petSearchBox;
        System::Windows::Forms::DataGridView^ petsGrid;
        System::Windows::Forms::DataGridView^ petHistoryGrid;
        System::Windows::Forms::Button^ addPetButton;
        System::Windows::Forms::Button^ editPetButton;
        System::Windows::Forms::Button^ deletePetButton;
        System::Windows::Forms::Button^ addHistoryButton;
        System::Windows::Forms::Button^ deleteHistoryButton;
        System::Windows::Forms::Label^ allergyAlertLabel;

        System::Data::DataTable^ productsTable;
        System::Data::DataTable^ categoriesTable;
        System::Data::DataTable^ locationsTable;
        System::Data::DataTable^ petsTable;
        System::Data::DataTable^ historyTable;

        void BuildUi();
        void BuildInventoryTab();
        void BuildLookupTabs();
        void BuildPetsTab();
        void CreateBaseTables();

        void LoadProducts();
        void LoadCategories();
        void LoadLocations();
        void LoadPets();
        void LoadPetHistory(int petId);
        void LoadProductFilters();

        void ApplyProductFilter();
        void ApplyPetFilter();

        bool SaveProduct(bool isEdit);
        bool DeleteSelectedProduct();

        bool SaveLookup(System::String^ tableName, bool isEdit);
        bool DeleteLookup(System::String^ tableName, System::Windows::Forms::DataGridView^ grid);

        bool SavePet(bool isEdit);
        bool DeleteSelectedPet();
        bool SaveHistoryEntry();
        bool DeleteSelectedHistoryEntry();
        bool ShowAllergyWarningIfNeeded(System::String^ allergies, System::String^ productName);

        int GetSelectedId(System::Windows::Forms::DataGridView^ grid);
        System::Data::DataRow^ GetSelectedRow(System::Windows::Forms::DataGridView^ grid);
        System::Data::DataTable^ BuildProductsLookup();
        void UpdateAllergyAlert();

        System::Void productSearchBox_TextChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void productFilterChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void addProductButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void editProductButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void deleteProductButton_Click(System::Object^ sender, System::EventArgs^ e);

        System::Void addCategoryButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void editCategoryButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void deleteCategoryButton_Click(System::Object^ sender, System::EventArgs^ e);

        System::Void addLocationButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void editLocationButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void deleteLocationButton_Click(System::Object^ sender, System::EventArgs^ e);

        System::Void addPetButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void editPetButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void deletePetButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void addHistoryButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void deleteHistoryButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void petSearchBox_TextChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void petsGrid_SelectionChanged(System::Object^ sender, System::EventArgs^ e);
    };
}
