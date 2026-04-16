#include "MainForm.h"
#include "AddProductForm.h"
#include "DbHelpers.h"
#include "HistoryEntryForm.h"
#include "PetEditorForm.h"
#include "TextInputDialog.h"
#include "Theme.h"
#include <sqlite3.h>

using namespace System;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Text;
using namespace System::Windows::Forms;

namespace VetPharm
{
    MainForm::MainForm(void)
    {
        components = nullptr;
        databasePath = DbHelpers::ResolveDatabasePath();
        DbHelpers::EnsurePasswordConfig(databasePath);
        CreateBaseTables();
        BuildUi();
        LoadCategories();
        LoadLocations();
        LoadProducts();
        LoadProductFilters();
        LoadPets();
    }

    MainForm::~MainForm()
    {
        if (components)
        {
            delete components;
        }
    }

    void MainForm::CreateBaseTables()
    {
        const char* sql =
            "CREATE TABLE IF NOT EXISTS Categories ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL UNIQUE"
            ");"
            "CREATE TABLE IF NOT EXISTS Locations ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL UNIQUE"
            ");"
            "CREATE TABLE IF NOT EXISTS Products ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"
            "category INTEGER NOT NULL,"
            "packaging_size INTEGER,"
            "quantity INTEGER,"
            "unit TEXT,"
            "location INTEGER NOT NULL,"
            "price INTEGER,"
            "FOREIGN KEY (category) REFERENCES Categories(id),"
            "FOREIGN KEY (location) REFERENCES Locations(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS Owners ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "full_name TEXT NOT NULL,"
            "phone TEXT"
            ");"
            "CREATE TABLE IF NOT EXISTS Pets ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"
            "owner_id INTEGER NOT NULL,"
            "animal_type TEXT NOT NULL,"
            "weight REAL,"
            "allergies TEXT,"
            "FOREIGN KEY (owner_id) REFERENCES Owners(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS PetHistory ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "pet_id INTEGER NOT NULL,"
            "product_id INTEGER NOT NULL,"
            "action_type TEXT NOT NULL,"
            "date TEXT NOT NULL,"
            "notes TEXT,"
            "FOREIGN KEY (pet_id) REFERENCES Pets(id),"
            "FOREIGN KEY (product_id) REFERENCES Products(id)"
            ");";
        DbHelpers::ExecuteNonQuery(databasePath, sql);

        if (!DbHelpers::TableHasColumn(databasePath, L"Owners", L"phone"))
        {
            DbHelpers::ExecuteNonQuery(databasePath, "ALTER TABLE Owners ADD COLUMN phone TEXT;");
        }
    }

    void MainForm::BuildUi()
    {
        Theme::ApplyForm(this, L"VetPharm");
        this->ClientSize = Drawing::Size(1420, 860);

        titleLabel = gcnew Label();
        titleLabel->Text = L"VetPharm";
        titleLabel->Location = Point(28, 20);
        titleLabel->Size = Drawing::Size(220, 42);
        titleLabel->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 24.0f);

        subtitleLabel = gcnew Label();
        subtitleLabel->Text = L"Управление ветеринарной аптекой: склад, справочники, питомцы и история";
        subtitleLabel->Location = Point(30, 62);
        subtitleLabel->Size = Drawing::Size(800, 24);
        subtitleLabel->ForeColor = Theme::TextMuted;

        mainTabs = gcnew TabControl();
        mainTabs->Location = Point(24, 104);
        mainTabs->Size = Drawing::Size(1370, 730);
        mainTabs->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.0f);

        inventoryTab = gcnew TabPage(L"Умный склад");
        categoriesTab = gcnew TabPage(L"Категории");
        locationsTab = gcnew TabPage(L"Локации");
        petsTab = gcnew TabPage(L"Питомцы и история");

        inventoryTab->BackColor = Theme::Background;
        categoriesTab->BackColor = Theme::Background;
        locationsTab->BackColor = Theme::Background;
        petsTab->BackColor = Theme::Background;

        BuildInventoryTab();
        BuildLookupTabs();
        BuildPetsTab();

        mainTabs->TabPages->Add(inventoryTab);
        mainTabs->TabPages->Add(categoriesTab);
        mainTabs->TabPages->Add(locationsTab);
        mainTabs->TabPages->Add(petsTab);

        this->Controls->Add(titleLabel);
        this->Controls->Add(subtitleLabel);
        this->Controls->Add(mainTabs);
    }

    void MainForm::BuildInventoryTab()
    {
        Panel^ toolbar = Theme::CreateSectionPanel(16, 18, 1320, 92);
        inventoryTab->Controls->Add(toolbar);

        Label^ searchLabel = gcnew Label();
        searchLabel->Text = L"Поиск";
        searchLabel->Location = Point(18, 16);
        searchLabel->Size = Drawing::Size(80, 22);
        searchLabel->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.0f);

        productSearchBox = gcnew TextBox();
        productSearchBox->Location = Point(18, 42);
        productSearchBox->Size = Drawing::Size(280, 30);
        Theme::StyleInput(productSearchBox);
        productSearchBox->TextChanged += gcnew EventHandler(this, &MainForm::productSearchBox_TextChanged);

        Label^ categoryLabel = gcnew Label();
        categoryLabel->Text = L"Категория";
        categoryLabel->Location = Point(318, 16);
        categoryLabel->Size = Drawing::Size(100, 22);
        categoryLabel->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.0f);

        productCategoryFilter = gcnew ComboBox();
        productCategoryFilter->Location = Point(318, 42);
        productCategoryFilter->Size = Drawing::Size(220, 31);
        productCategoryFilter->DropDownStyle = ComboBoxStyle::DropDownList;
        Theme::StyleInput(productCategoryFilter);
        productCategoryFilter->SelectedIndexChanged += gcnew EventHandler(this, &MainForm::productFilterChanged);

        Label^ locationLabel = gcnew Label();
        locationLabel->Text = L"Локация";
        locationLabel->Location = Point(558, 16);
        locationLabel->Size = Drawing::Size(100, 22);
        locationLabel->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.0f);

        productLocationFilter = gcnew ComboBox();
        productLocationFilter->Location = Point(558, 42);
        productLocationFilter->Size = Drawing::Size(220, 31);
        productLocationFilter->DropDownStyle = ComboBoxStyle::DropDownList;
        Theme::StyleInput(productLocationFilter);
        productLocationFilter->SelectedIndexChanged += gcnew EventHandler(this, &MainForm::productFilterChanged);

        addProductButton = gcnew Button();
        addProductButton->Text = L"Добавить";
        addProductButton->Location = Point(936, 36);
        addProductButton->Size = Drawing::Size(112, 38);
        Theme::StylePrimaryButton(addProductButton);
        addProductButton->Click += gcnew EventHandler(this, &MainForm::addProductButton_Click);

        editProductButton = gcnew Button();
        editProductButton->Text = L"Изменить";
        editProductButton->Location = Point(1060, 36);
        editProductButton->Size = Drawing::Size(112, 38);
        Theme::StyleSecondaryButton(editProductButton);
        editProductButton->Click += gcnew EventHandler(this, &MainForm::editProductButton_Click);

        deleteProductButton = gcnew Button();
        deleteProductButton->Text = L"Удалить";
        deleteProductButton->Location = Point(1184, 36);
        deleteProductButton->Size = Drawing::Size(112, 38);
        Theme::StyleDangerButton(deleteProductButton);
        deleteProductButton->Click += gcnew EventHandler(this, &MainForm::deleteProductButton_Click);

        toolbar->Controls->Add(searchLabel);
        toolbar->Controls->Add(productSearchBox);
        toolbar->Controls->Add(categoryLabel);
        toolbar->Controls->Add(productCategoryFilter);
        toolbar->Controls->Add(locationLabel);
        toolbar->Controls->Add(productLocationFilter);
        toolbar->Controls->Add(addProductButton);
        toolbar->Controls->Add(editProductButton);
        toolbar->Controls->Add(deleteProductButton);

        productsGrid = gcnew DataGridView();
        productsGrid->Location = Point(16, 128);
        productsGrid->Size = Drawing::Size(1320, 550);
        Theme::StyleGrid(productsGrid);
        inventoryTab->Controls->Add(productsGrid);
    }

    void MainForm::BuildLookupTabs()
    {
        categoriesGrid = gcnew DataGridView();
        categoriesGrid->Location = Point(18, 90);
        categoriesGrid->Size = Drawing::Size(1310, 580);
        Theme::StyleGrid(categoriesGrid);

        addCategoryButton = gcnew Button();
        addCategoryButton->Text = L"Добавить категорию";
        addCategoryButton->Location = Point(18, 24);
        addCategoryButton->Size = Drawing::Size(170, 38);
        Theme::StylePrimaryButton(addCategoryButton);
        addCategoryButton->Click += gcnew EventHandler(this, &MainForm::addCategoryButton_Click);

        editCategoryButton = gcnew Button();
        editCategoryButton->Text = L"Изменить";
        editCategoryButton->Location = Point(198, 24);
        editCategoryButton->Size = Drawing::Size(120, 38);
        Theme::StyleSecondaryButton(editCategoryButton);
        editCategoryButton->Click += gcnew EventHandler(this, &MainForm::editCategoryButton_Click);

        deleteCategoryButton = gcnew Button();
        deleteCategoryButton->Text = L"Удалить";
        deleteCategoryButton->Location = Point(328, 24);
        deleteCategoryButton->Size = Drawing::Size(120, 38);
        Theme::StyleDangerButton(deleteCategoryButton);
        deleteCategoryButton->Click += gcnew EventHandler(this, &MainForm::deleteCategoryButton_Click);

        categoriesTab->Controls->Add(addCategoryButton);
        categoriesTab->Controls->Add(editCategoryButton);
        categoriesTab->Controls->Add(deleteCategoryButton);
        categoriesTab->Controls->Add(categoriesGrid);

        locationsGrid = gcnew DataGridView();
        locationsGrid->Location = Point(18, 90);
        locationsGrid->Size = Drawing::Size(1310, 580);
        Theme::StyleGrid(locationsGrid);

        addLocationButton = gcnew Button();
        addLocationButton->Text = L"Добавить локацию";
        addLocationButton->Location = Point(18, 24);
        addLocationButton->Size = Drawing::Size(170, 38);
        Theme::StylePrimaryButton(addLocationButton);
        addLocationButton->Click += gcnew EventHandler(this, &MainForm::addLocationButton_Click);

        editLocationButton = gcnew Button();
        editLocationButton->Text = L"Изменить";
        editLocationButton->Location = Point(198, 24);
        editLocationButton->Size = Drawing::Size(120, 38);
        Theme::StyleSecondaryButton(editLocationButton);
        editLocationButton->Click += gcnew EventHandler(this, &MainForm::editLocationButton_Click);

        deleteLocationButton = gcnew Button();
        deleteLocationButton->Text = L"Удалить";
        deleteLocationButton->Location = Point(328, 24);
        deleteLocationButton->Size = Drawing::Size(120, 38);
        Theme::StyleDangerButton(deleteLocationButton);
        deleteLocationButton->Click += gcnew EventHandler(this, &MainForm::deleteLocationButton_Click);

        locationsTab->Controls->Add(addLocationButton);
        locationsTab->Controls->Add(editLocationButton);
        locationsTab->Controls->Add(deleteLocationButton);
        locationsTab->Controls->Add(locationsGrid);
    }

    void MainForm::BuildPetsTab()
    {
        Label^ petSearchLabel = gcnew Label();
        petSearchLabel->Text = L"Поиск хозяина";
        petSearchLabel->Location = Point(456, 30);
        petSearchLabel->Size = Drawing::Size(120, 22);
        petSearchLabel->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.0f);

        petSearchBox = gcnew TextBox();
        petSearchBox->Location = Point(580, 26);
        petSearchBox->Size = Drawing::Size(250, 30);
        Theme::StyleInput(petSearchBox);
        petSearchBox->TextChanged += gcnew EventHandler(this, &MainForm::petSearchBox_TextChanged);

        addPetButton = gcnew Button();
        addPetButton->Text = L"Добавить питомца";
        addPetButton->Location = Point(18, 22);
        addPetButton->Size = Drawing::Size(160, 38);
        Theme::StylePrimaryButton(addPetButton);
        addPetButton->Click += gcnew EventHandler(this, &MainForm::addPetButton_Click);

        editPetButton = gcnew Button();
        editPetButton->Text = L"Изменить";
        editPetButton->Location = Point(188, 22);
        editPetButton->Size = Drawing::Size(118, 38);
        Theme::StyleSecondaryButton(editPetButton);
        editPetButton->Click += gcnew EventHandler(this, &MainForm::editPetButton_Click);

        deletePetButton = gcnew Button();
        deletePetButton->Text = L"Удалить";
        deletePetButton->Location = Point(316, 22);
        deletePetButton->Size = Drawing::Size(118, 38);
        Theme::StyleDangerButton(deletePetButton);
        deletePetButton->Click += gcnew EventHandler(this, &MainForm::deletePetButton_Click);

        addHistoryButton = gcnew Button();
        addHistoryButton->Text = L"Добавить в историю";
        addHistoryButton->Location = Point(1030, 22);
        addHistoryButton->Size = Drawing::Size(170, 38);
        Theme::StylePrimaryButton(addHistoryButton);
        addHistoryButton->Click += gcnew EventHandler(this, &MainForm::addHistoryButton_Click);

        deleteHistoryButton = gcnew Button();
        deleteHistoryButton->Text = L"Удалить запись";
        deleteHistoryButton->Location = Point(1210, 22);
        deleteHistoryButton->Size = Drawing::Size(118, 38);
        Theme::StyleDangerButton(deleteHistoryButton);
        deleteHistoryButton->Click += gcnew EventHandler(this, &MainForm::deleteHistoryButton_Click);

        allergyAlertLabel = gcnew Label();
        allergyAlertLabel->Location = Point(18, 72);
        allergyAlertLabel->Size = Drawing::Size(1310, 40);
        allergyAlertLabel->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.0f);
        allergyAlertLabel->ForeColor = Theme::Danger;

        petsGrid = gcnew DataGridView();
        petsGrid->Location = Point(18, 120);
        petsGrid->Size = Drawing::Size(620, 540);
        Theme::StyleGrid(petsGrid);
        petsGrid->SelectionChanged += gcnew EventHandler(this, &MainForm::petsGrid_SelectionChanged);

        petHistoryGrid = gcnew DataGridView();
        petHistoryGrid->Location = Point(658, 120);
        petHistoryGrid->Size = Drawing::Size(670, 540);
        Theme::StyleGrid(petHistoryGrid);

        petsTab->Controls->Add(addPetButton);
        petsTab->Controls->Add(editPetButton);
        petsTab->Controls->Add(deletePetButton);
        petsTab->Controls->Add(petSearchLabel);
        petsTab->Controls->Add(petSearchBox);
        petsTab->Controls->Add(addHistoryButton);
        petsTab->Controls->Add(deleteHistoryButton);
        petsTab->Controls->Add(allergyAlertLabel);
        petsTab->Controls->Add(petsGrid);
        petsTab->Controls->Add(petHistoryGrid);
    }

    void MainForm::LoadProducts()
    {
        productsTable = gcnew DataTable();
        productsTable->Columns->Add(L"id", Int32::typeid);
        productsTable->Columns->Add(L"name", String::typeid);
        productsTable->Columns->Add(L"category_id", Int32::typeid);
        productsTable->Columns->Add(L"category", String::typeid);
        productsTable->Columns->Add(L"packaging_size", Int32::typeid);
        productsTable->Columns->Add(L"quantity", Int32::typeid);
        productsTable->Columns->Add(L"unit", String::typeid);
        productsTable->Columns->Add(L"location_id", Int32::typeid);
        productsTable->Columns->Add(L"location", String::typeid);
        productsTable->Columns->Add(L"price", Int32::typeid);

        sqlite3* db = DbHelpers::OpenDatabase(databasePath);
        if (db == nullptr)
        {
            return;
        }

        const char* sql =
            "SELECT p.id, p.name, p.category, c.name, p.packaging_size, p.quantity, p.unit, p.location, l.name, p.price "
            "FROM Products p "
            "INNER JOIN Categories c ON c.id = p.category "
            "INNER JOIN Locations l ON l.id = p.location "
            "ORDER BY p.id DESC";

        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
        {
            while (sqlite3_step(stmt) == SQLITE_ROW)
            {
                DataRow^ row = productsTable->NewRow();
                row[L"id"] = sqlite3_column_int(stmt, 0);
                row[L"name"] = DbHelpers::FromUtf8Column(stmt, 1);
                row[L"category_id"] = sqlite3_column_int(stmt, 2);
                row[L"category"] = DbHelpers::FromUtf8Column(stmt, 3);
                row[L"packaging_size"] = sqlite3_column_int(stmt, 4);
                row[L"quantity"] = sqlite3_column_int(stmt, 5);
                row[L"unit"] = DbHelpers::FromUtf8Column(stmt, 6);
                row[L"location_id"] = sqlite3_column_int(stmt, 7);
                row[L"location"] = DbHelpers::FromUtf8Column(stmt, 8);
                row[L"price"] = sqlite3_column_int(stmt, 9);
                productsTable->Rows->Add(row);
            }
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        productsGrid->DataSource = productsTable;
        if (productsGrid->Columns->Contains(L"id")) productsGrid->Columns[L"id"]->HeaderText = L"ID";
        if (productsGrid->Columns->Contains(L"name")) productsGrid->Columns[L"name"]->HeaderText = L"Название";
        if (productsGrid->Columns->Contains(L"category")) productsGrid->Columns[L"category"]->HeaderText = L"Категория";
        if (productsGrid->Columns->Contains(L"packaging_size")) productsGrid->Columns[L"packaging_size"]->HeaderText = L"Фасовка";
        if (productsGrid->Columns->Contains(L"quantity")) productsGrid->Columns[L"quantity"]->HeaderText = L"Количество";
        if (productsGrid->Columns->Contains(L"unit")) productsGrid->Columns[L"unit"]->HeaderText = L"Ед.";
        if (productsGrid->Columns->Contains(L"location")) productsGrid->Columns[L"location"]->HeaderText = L"Место";
        if (productsGrid->Columns->Contains(L"price")) productsGrid->Columns[L"price"]->HeaderText = L"Цена";
        if (productsGrid->Columns->Contains(L"category_id")) productsGrid->Columns[L"category_id"]->Visible = false;
        if (productsGrid->Columns->Contains(L"location_id")) productsGrid->Columns[L"location_id"]->Visible = false;
    }

    void MainForm::LoadCategories()
    {
        categoriesTable = DbHelpers::LoadLookupTable(databasePath, L"Categories");
        categoriesGrid->DataSource = categoriesTable;
        if (categoriesGrid->Columns->Contains(L"id")) categoriesGrid->Columns[L"id"]->HeaderText = L"ID";
        if (categoriesGrid->Columns->Contains(L"name")) categoriesGrid->Columns[L"name"]->HeaderText = L"Название";
    }

    void MainForm::LoadLocations()
    {
        locationsTable = DbHelpers::LoadLookupTable(databasePath, L"Locations");
        locationsGrid->DataSource = locationsTable;
        if (locationsGrid->Columns->Contains(L"id")) locationsGrid->Columns[L"id"]->HeaderText = L"ID";
        if (locationsGrid->Columns->Contains(L"name")) locationsGrid->Columns[L"name"]->HeaderText = L"Название";
    }

    void MainForm::LoadPets()
    {
        petsTable = gcnew DataTable();
        petsTable->Columns->Add(L"id", Int32::typeid);
        petsTable->Columns->Add(L"name", String::typeid);
        petsTable->Columns->Add(L"owner_id", Int32::typeid);
        petsTable->Columns->Add(L"owner_name", String::typeid);
        petsTable->Columns->Add(L"phone", String::typeid);
        petsTable->Columns->Add(L"animal_type", String::typeid);
        petsTable->Columns->Add(L"weight", Double::typeid);
        petsTable->Columns->Add(L"allergies", String::typeid);

        sqlite3* db = DbHelpers::OpenDatabase(databasePath);
        if (db == nullptr)
        {
            return;
        }

        const char* sql =
            "SELECT p.id, p.name, p.owner_id, o.full_name, COALESCE(o.phone, ''), p.animal_type, p.weight, p.allergies "
            "FROM Pets p "
            "INNER JOIN Owners o ON o.id = p.owner_id "
            "ORDER BY p.name";

        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
        {
            while (sqlite3_step(stmt) == SQLITE_ROW)
            {
                DataRow^ row = petsTable->NewRow();
                row[L"id"] = sqlite3_column_int(stmt, 0);
                row[L"name"] = DbHelpers::FromUtf8Column(stmt, 1);
                row[L"owner_id"] = sqlite3_column_int(stmt, 2);
                row[L"owner_name"] = DbHelpers::FromUtf8Column(stmt, 3);
                row[L"phone"] = DbHelpers::FromUtf8Column(stmt, 4);
                row[L"animal_type"] = DbHelpers::FromUtf8Column(stmt, 5);
                row[L"weight"] = sqlite3_column_double(stmt, 6);
                row[L"allergies"] = DbHelpers::FromUtf8Column(stmt, 7);
                petsTable->Rows->Add(row);
            }
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        petsGrid->DataSource = petsTable;
        if (petsGrid->Columns->Contains(L"id")) petsGrid->Columns[L"id"]->HeaderText = L"ID";
        if (petsGrid->Columns->Contains(L"name")) petsGrid->Columns[L"name"]->HeaderText = L"Кличка";
        if (petsGrid->Columns->Contains(L"owner_name")) petsGrid->Columns[L"owner_name"]->HeaderText = L"Хозяин";
        if (petsGrid->Columns->Contains(L"phone")) petsGrid->Columns[L"phone"]->HeaderText = L"Телефон";
        if (petsGrid->Columns->Contains(L"animal_type")) petsGrid->Columns[L"animal_type"]->HeaderText = L"Вид";
        if (petsGrid->Columns->Contains(L"weight")) petsGrid->Columns[L"weight"]->HeaderText = L"Вес";
        if (petsGrid->Columns->Contains(L"allergies")) petsGrid->Columns[L"allergies"]->HeaderText = L"Аллергии";
        if (petsGrid->Columns->Contains(L"owner_id")) petsGrid->Columns[L"owner_id"]->Visible = false;
        ApplyPetFilter();

        if (petsGrid->Rows->Count > 0)
        {
            DataRowView^ firstPetView = dynamic_cast<DataRowView^>(petsGrid->Rows[0]->DataBoundItem);
            DataRow^ firstPetRow = firstPetView == nullptr ? nullptr : firstPetView->Row;
            petsGrid->Rows[0]->Selected = true;
            if (firstPetRow != nullptr)
            {
                LoadPetHistory(Convert::ToInt32(firstPetRow[L"id"]));
            }
        }
        else
        {
            historyTable = gcnew DataTable();
            petHistoryGrid->DataSource = historyTable;
            allergyAlertLabel->Text = L"";
        }
    }

    void MainForm::LoadPetHistory(int petId)
    {
        historyTable = gcnew DataTable();
        historyTable->Columns->Add(L"id", Int32::typeid);
        historyTable->Columns->Add(L"date", String::typeid);
        historyTable->Columns->Add(L"action_type", String::typeid);
        historyTable->Columns->Add(L"product_id", Int32::typeid);
        historyTable->Columns->Add(L"product_name", String::typeid);
        historyTable->Columns->Add(L"notes", String::typeid);

        sqlite3* db = DbHelpers::OpenDatabase(databasePath);
        if (db == nullptr)
        {
            return;
        }

        const char* sql =
            "SELECT h.id, h.date, h.action_type, h.product_id, p.name, h.notes "
            "FROM PetHistory h "
            "INNER JOIN Products p ON p.id = h.product_id "
            "WHERE h.pet_id = ? "
            "ORDER BY h.date DESC, h.id DESC";

        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
        {
            sqlite3_bind_int(stmt, 1, petId);
            while (sqlite3_step(stmt) == SQLITE_ROW)
            {
                DataRow^ row = historyTable->NewRow();
                row[L"id"] = sqlite3_column_int(stmt, 0);
                row[L"date"] = DbHelpers::FromUtf8Column(stmt, 1);
                row[L"action_type"] = DbHelpers::FromUtf8Column(stmt, 2);
                row[L"product_id"] = sqlite3_column_int(stmt, 3);
                row[L"product_name"] = DbHelpers::FromUtf8Column(stmt, 4);
                row[L"notes"] = DbHelpers::FromUtf8Column(stmt, 5);
                historyTable->Rows->Add(row);
            }
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        petHistoryGrid->DataSource = historyTable;
        if (petHistoryGrid->Columns->Contains(L"id")) petHistoryGrid->Columns[L"id"]->HeaderText = L"ID";
        if (petHistoryGrid->Columns->Contains(L"date")) petHistoryGrid->Columns[L"date"]->HeaderText = L"Дата";
        if (petHistoryGrid->Columns->Contains(L"action_type")) petHistoryGrid->Columns[L"action_type"]->HeaderText = L"Тип";
        if (petHistoryGrid->Columns->Contains(L"product_name")) petHistoryGrid->Columns[L"product_name"]->HeaderText = L"Препарат";
        if (petHistoryGrid->Columns->Contains(L"notes")) petHistoryGrid->Columns[L"notes"]->HeaderText = L"Примечания";
        if (petHistoryGrid->Columns->Contains(L"product_id")) petHistoryGrid->Columns[L"product_id"]->Visible = false;

        UpdateAllergyAlert();
    }

    void MainForm::LoadProductFilters()
    {
        productCategoryFilter->Items->Clear();
        productLocationFilter->Items->Clear();
        productCategoryFilter->Items->Add(L"Все категории");
        productLocationFilter->Items->Add(L"Все локации");

        for each (DataRow ^ row in categoriesTable->Rows)
        {
            productCategoryFilter->Items->Add(row[L"name"]);
        }

        for each (DataRow ^ row in locationsTable->Rows)
        {
            productLocationFilter->Items->Add(row[L"name"]);
        }

        if (productCategoryFilter->Items->Count > 0) productCategoryFilter->SelectedIndex = 0;
        if (productLocationFilter->Items->Count > 0) productLocationFilter->SelectedIndex = 0;
    }

    void MainForm::ApplyProductFilter()
    {
        if (productsTable == nullptr)
        {
            return;
        }

        StringBuilder^ filter = gcnew StringBuilder();
        bool first = true;

        String^ search = productSearchBox->Text->Trim();
        if (!String::IsNullOrWhiteSpace(search))
        {
            filter->Append(String::Format(L"name LIKE '%{0}%'", DbHelpers::EscapeRowFilterValue(search)));
            first = false;
        }

        if (productCategoryFilter->SelectedItem != nullptr && productCategoryFilter->SelectedItem->ToString() != L"Все категории")
        {
            if (!first) filter->Append(L" AND ");
            filter->Append(String::Format(L"category = '{0}'", DbHelpers::EscapeRowFilterValue(productCategoryFilter->SelectedItem->ToString())));
            first = false;
        }

        if (productLocationFilter->SelectedItem != nullptr && productLocationFilter->SelectedItem->ToString() != L"Все локации")
        {
            if (!first) filter->Append(L" AND ");
            filter->Append(String::Format(L"location = '{0}'", DbHelpers::EscapeRowFilterValue(productLocationFilter->SelectedItem->ToString())));
        }

        productsTable->DefaultView->RowFilter = filter->ToString();
    }

    void MainForm::ApplyPetFilter()
    {
        if (petsTable == nullptr)
        {
            return;
        }

        String^ search = petSearchBox == nullptr ? String::Empty : petSearchBox->Text->Trim();
        if (String::IsNullOrWhiteSpace(search))
        {
            petsTable->DefaultView->RowFilter = String::Empty;
            return;
        }

        String^ escaped = DbHelpers::EscapeRowFilterValue(search);
        petsTable->DefaultView->RowFilter = String::Format(
            L"name LIKE '%{0}%' OR owner_name LIKE '%{0}%' OR phone LIKE '%{0}%'",
            escaped);
    }

    int MainForm::GetSelectedId(DataGridView^ grid)
    {
        DataRow^ row = GetSelectedRow(grid);
        if (row == nullptr)
        {
            return 0;
        }

        return Convert::ToInt32(row[L"id"]);
    }

    DataRow^ MainForm::GetSelectedRow(DataGridView^ grid)
    {
        if (grid->CurrentRow == nullptr || grid->CurrentRow->DataBoundItem == nullptr)
        {
            return nullptr;
        }

        DataRowView^ rowView = dynamic_cast<DataRowView^>(grid->CurrentRow->DataBoundItem);
        return rowView == nullptr ? nullptr : rowView->Row;
    }

    DataTable^ MainForm::BuildProductsLookup()
    {
        DataTable^ table = gcnew DataTable();
        table->Columns->Add(L"id", Int32::typeid);
        table->Columns->Add(L"name", String::typeid);

        for each (DataRow ^ row in productsTable->Rows)
        {
            DataRow^ newRow = table->NewRow();
            newRow[L"id"] = row[L"id"];
            newRow[L"name"] = row[L"name"];
            table->Rows->Add(newRow);
        }

        return table;
    }

    void MainForm::UpdateAllergyAlert()
    {
        DataRow^ petRow = GetSelectedRow(petsGrid);
        if (petRow == nullptr)
        {
            allergyAlertLabel->Text = L"";
            return;
        }

        String^ allergies = Convert::ToString(petRow[L"allergies"]);
        if (String::IsNullOrWhiteSpace(allergies))
        {
            allergyAlertLabel->Text = L"У выбранного питомца аллергии не указаны.";
            allergyAlertLabel->ForeColor = Theme::TextMuted;
        }
        else
        {
            allergyAlertLabel->Text = L"Аллергии питомца: " + allergies;
            allergyAlertLabel->ForeColor = Theme::Danger;
        }
    }

    bool MainForm::SaveProduct(bool isEdit)
    {
        DataRow^ selectedRow = GetSelectedRow(productsGrid);
        AddProductForm^ form = gcnew AddProductForm(databasePath, isEdit);

        if (isEdit)
        {
            if (selectedRow == nullptr)
            {
                MessageBox::Show(L"Выберите препарат для редактирования.", L"Препараты", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return false;
            }

            form->SetProductValues(
                Convert::ToInt32(selectedRow[L"id"]),
                Convert::ToString(selectedRow[L"name"]),
                Convert::ToInt32(selectedRow[L"category_id"]),
                Convert::ToInt32(selectedRow[L"location_id"]),
                Convert::ToInt32(selectedRow[L"packaging_size"]),
                Convert::ToInt32(selectedRow[L"quantity"]),
                Convert::ToString(selectedRow[L"unit"]),
                Convert::ToInt32(selectedRow[L"price"]));
        }

        if (form->ShowDialog() != System::Windows::Forms::DialogResult::OK || !form->ValidateInput())
        {
            return false;
        }

        sqlite3* db = DbHelpers::OpenDatabase(databasePath);
        if (db == nullptr)
        {
            return false;
        }

        const char* sql = isEdit
            ? "UPDATE Products SET name = ?, category = ?, packaging_size = ?, quantity = ?, unit = ?, location = ?, price = ? WHERE id = ?"
            : "INSERT INTO Products(name, category, packaging_size, quantity, unit, location, price) VALUES(?, ?, ?, ?, ?, ?, ?)";

        sqlite3_stmt* stmt = nullptr;
        bool success = false;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
        {
            std::string name = DbHelpers::ToUtf8String(form->ProductName);
            std::string unit = DbHelpers::ToUtf8String(form->Unit);
            sqlite3_bind_text(stmt, 1, name.c_str(), static_cast<int>(name.size()), SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 2, form->SelectedCategoryId);
            sqlite3_bind_int(stmt, 3, form->PackagingSize);
            sqlite3_bind_int(stmt, 4, form->Quantity);
            sqlite3_bind_text(stmt, 5, unit.c_str(), static_cast<int>(unit.size()), SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 6, form->SelectedLocationId);
            sqlite3_bind_int(stmt, 7, form->Price);
            if (isEdit)
            {
                sqlite3_bind_int(stmt, 8, form->ProductId);
            }
            success = sqlite3_step(stmt) == SQLITE_DONE;
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        if (!success)
        {
            MessageBox::Show(L"Не удалось сохранить препарат.", L"Препараты", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        LoadProducts();
        ApplyProductFilter();
        if (petsGrid->CurrentRow != nullptr)
        {
            LoadPetHistory(GetSelectedId(petsGrid));
        }
        return true;
    }

    bool MainForm::DeleteSelectedProduct()
    {
        const int productId = GetSelectedId(productsGrid);
        if (productId == 0)
        {
            MessageBox::Show(L"Выберите препарат для удаления.", L"Препараты", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return false;
        }

        if (MessageBox::Show(L"Удалить выбранный препарат?", L"Подтверждение", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) != System::Windows::Forms::DialogResult::Yes)
        {
            return false;
        }

        sqlite3* db = DbHelpers::OpenDatabase(databasePath);
        if (db == nullptr)
        {
            return false;
        }

        const char* sql = "DELETE FROM Products WHERE id = ?";
        sqlite3_stmt* stmt = nullptr;
        bool success = false;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
        {
            sqlite3_bind_int(stmt, 1, productId);
            success = sqlite3_step(stmt) == SQLITE_DONE;
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);

        if (!success)
        {
            MessageBox::Show(L"Не удалось удалить препарат. Возможно, он используется в истории питомцев.", L"Препараты",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        LoadProducts();
        ApplyProductFilter();
        return true;
    }

    bool MainForm::SaveLookup(String^ tableName, bool isEdit)
    {
        DataGridView^ grid = tableName == L"Categories" ? categoriesGrid : locationsGrid;
        DataRow^ selectedRow = GetSelectedRow(grid);
        String^ initialValue = isEdit && selectedRow != nullptr ? Convert::ToString(selectedRow[L"name"]) : String::Empty;

        if (isEdit && selectedRow == nullptr)
        {
            MessageBox::Show(L"Сначала выберите запись.", L"Справочники", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return false;
        }

        TextInputDialog^ dialog = gcnew TextInputDialog(
            tableName == L"Categories" ? L"Категория" : L"Локация",
            tableName == L"Categories" ? L"Введите название категории" : L"Введите адрес хранения",
            initialValue);

        if (dialog->ShowDialog() != System::Windows::Forms::DialogResult::OK || String::IsNullOrWhiteSpace(dialog->Value))
        {
            return false;
        }

        sqlite3* db = DbHelpers::OpenDatabase(databasePath);
        if (db == nullptr)
        {
            return false;
        }

        std::string table = DbHelpers::ToUtf8String(tableName);
        std::string sql = isEdit
            ? "UPDATE " + table + " SET name = ? WHERE id = ?"
            : "INSERT INTO " + table + "(name) VALUES(?)";
        sqlite3_stmt* stmt = nullptr;
        bool success = false;

        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
        {
            std::string name = DbHelpers::ToUtf8String(dialog->Value);
            sqlite3_bind_text(stmt, 1, name.c_str(), static_cast<int>(name.size()), SQLITE_TRANSIENT);
            if (isEdit)
            {
                sqlite3_bind_int(stmt, 2, Convert::ToInt32(selectedRow[L"id"]));
            }
            success = sqlite3_step(stmt) == SQLITE_DONE;
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        if (!success)
        {
            MessageBox::Show(L"Не удалось сохранить запись. Проверьте уникальность названия.", L"Справочники",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        LoadCategories();
        LoadLocations();
        LoadProducts();
        LoadProductFilters();
        ApplyProductFilter();
        return true;
    }

    bool MainForm::DeleteLookup(String^ tableName, DataGridView^ grid)
    {
        DataRow^ row = GetSelectedRow(grid);
        if (row == nullptr)
        {
            MessageBox::Show(L"Выберите запись для удаления.", L"Справочники", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return false;
        }

        if (MessageBox::Show(L"Удалить выбранную запись?", L"Подтверждение", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) != System::Windows::Forms::DialogResult::Yes)
        {
            return false;
        }

        sqlite3* db = DbHelpers::OpenDatabase(databasePath);
        if (db == nullptr)
        {
            return false;
        }

        std::string sql = "DELETE FROM " + DbHelpers::ToUtf8String(tableName) + " WHERE id = ?";
        sqlite3_stmt* stmt = nullptr;
        bool success = false;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
        {
            sqlite3_bind_int(stmt, 1, Convert::ToInt32(row[L"id"]));
            success = sqlite3_step(stmt) == SQLITE_DONE;
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        if (!success)
        {
            MessageBox::Show(L"Не удалось удалить запись. Возможно, она уже используется в препаратах.", L"Справочники",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        LoadCategories();
        LoadLocations();
        LoadProducts();
        LoadProductFilters();
        ApplyProductFilter();
        return true;
    }

    bool MainForm::SavePet(bool isEdit)
    {
        DataRow^ selectedRow = GetSelectedRow(petsGrid);
        if (isEdit && selectedRow == nullptr)
        {
            MessageBox::Show(L"Выберите питомца для редактирования.", L"Питомцы", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return false;
        }

        PetEditorForm^ form = gcnew PetEditorForm();
        if (isEdit)
        {
            form->SetValues(
                Convert::ToString(selectedRow[L"name"]),
                Convert::ToString(selectedRow[L"owner_name"]),
                Convert::ToString(selectedRow[L"phone"]),
                Convert::ToString(selectedRow[L"animal_type"]),
                Convert::ToDouble(selectedRow[L"weight"]),
                Convert::ToString(selectedRow[L"allergies"]));
        }

        if (form->ShowDialog() != System::Windows::Forms::DialogResult::OK)
        {
            return false;
        }

        if (String::IsNullOrWhiteSpace(form->PetName) || String::IsNullOrWhiteSpace(form->OwnerName) || String::IsNullOrWhiteSpace(form->AnimalType))
        {
            MessageBox::Show(L"Заполните кличку, хозяина и вид животного.", L"Питомцы", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return false;
        }

        const int ownerId = DbHelpers::EnsureOwner(databasePath, form->OwnerName, form->OwnerPhone);
        if (ownerId == 0)
        {
            MessageBox::Show(L"Не удалось сохранить хозяина питомца.", L"Питомцы", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        sqlite3* db = DbHelpers::OpenDatabase(databasePath);
        if (db == nullptr)
        {
            return false;
        }

        const char* sql = isEdit
            ? "UPDATE Pets SET name = ?, owner_id = ?, animal_type = ?, weight = ?, allergies = ? WHERE id = ?"
            : "INSERT INTO Pets(name, owner_id, animal_type, weight, allergies) VALUES(?, ?, ?, ?, ?)";

        sqlite3_stmt* stmt = nullptr;
        bool success = false;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
        {
            std::string petName = DbHelpers::ToUtf8String(form->PetName);
            std::string animalType = DbHelpers::ToUtf8String(form->AnimalType);
            std::string allergies = DbHelpers::ToUtf8String(form->Allergies);
            sqlite3_bind_text(stmt, 1, petName.c_str(), static_cast<int>(petName.size()), SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 2, ownerId);
            sqlite3_bind_text(stmt, 3, animalType.c_str(), static_cast<int>(animalType.size()), SQLITE_TRANSIENT);
            sqlite3_bind_double(stmt, 4, form->WeightValue);
            sqlite3_bind_text(stmt, 5, allergies.c_str(), static_cast<int>(allergies.size()), SQLITE_TRANSIENT);
            if (isEdit)
            {
                sqlite3_bind_int(stmt, 6, Convert::ToInt32(selectedRow[L"id"]));
            }
            success = sqlite3_step(stmt) == SQLITE_DONE;
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        if (!success)
        {
            MessageBox::Show(L"Не удалось сохранить карточку питомца.", L"Питомцы", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        LoadPets();
        return true;
    }

    bool MainForm::DeleteSelectedPet()
    {
        const int petId = GetSelectedId(petsGrid);
        if (petId == 0)
        {
            MessageBox::Show(L"Выберите питомца для удаления.", L"Питомцы", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return false;
        }

        if (MessageBox::Show(L"Удалить карточку питомца и его историю?", L"Подтверждение", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) != System::Windows::Forms::DialogResult::Yes)
        {
            return false;
        }

        sqlite3* db = DbHelpers::OpenDatabase(databasePath);
        if (db == nullptr)
        {
            return false;
        }

        bool success = false;
        sqlite3_exec(db, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);

        sqlite3_stmt* historyStmt = nullptr;
        sqlite3_stmt* petStmt = nullptr;
        if (sqlite3_prepare_v2(db, "DELETE FROM PetHistory WHERE pet_id = ?", -1, &historyStmt, nullptr) == SQLITE_OK &&
            sqlite3_prepare_v2(db, "DELETE FROM Pets WHERE id = ?", -1, &petStmt, nullptr) == SQLITE_OK)
        {
            sqlite3_bind_int(historyStmt, 1, petId);
            sqlite3_step(historyStmt);

            sqlite3_bind_int(petStmt, 1, petId);
            success = sqlite3_step(petStmt) == SQLITE_DONE;
        }

        sqlite3_finalize(historyStmt);
        sqlite3_finalize(petStmt);
        sqlite3_exec(db, success ? "COMMIT;" : "ROLLBACK;", nullptr, nullptr, nullptr);
        sqlite3_close(db);

        if (!success)
        {
            MessageBox::Show(L"Не удалось удалить питомца.", L"Питомцы", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        LoadPets();
        return true;
    }

    bool MainForm::ShowAllergyWarningIfNeeded(String^ allergies, String^ productName)
    {
        if (String::IsNullOrWhiteSpace(allergies) || String::IsNullOrWhiteSpace(productName))
        {
            return true;
        }

        array<wchar_t>^ separators = gcnew array<wchar_t> { ',', ';', '\n' };
        array<String^>^ parts = allergies->Split(separators, StringSplitOptions::RemoveEmptyEntries);
        String^ lowerName = DbHelpers::ToLowerInvariant(productName);

        for each (String ^ part in parts)
        {
            String^ allergy = DbHelpers::ToLowerInvariant(part->Trim());
            if (!String::IsNullOrWhiteSpace(allergy) && lowerName->Contains(allergy))
            {
                String^ message =
                    L"ВНИМАНИЕ!\n\n"
                    L"У выбранного питомца указана аллергия: " + part->Trim() + L"\n"
                    L"Вы пытаетесь добавить препарат: " + productName + L"\n\n"
                    L"Проверьте назначение ещё раз. Продолжить запись в историю?";

                return MessageBox::Show(message, L"Критическое предупреждение по аллергии",
                    MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == System::Windows::Forms::DialogResult::Yes;
            }
        }

        return true;
    }

    bool MainForm::SaveHistoryEntry()
    {
        DataRow^ petRow = GetSelectedRow(petsGrid);
        if (petRow == nullptr)
        {
            MessageBox::Show(L"Сначала выберите питомца.", L"История", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return false;
        }

        if (productsTable == nullptr || productsTable->Rows->Count == 0)
        {
            MessageBox::Show(L"Сначала добавьте хотя бы один препарат.", L"История", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return false;
        }

        HistoryEntryForm^ form = gcnew HistoryEntryForm(BuildProductsLookup());
        if (form->ShowDialog() != System::Windows::Forms::DialogResult::OK)
        {
            return false;
        }

        if (!ShowAllergyWarningIfNeeded(Convert::ToString(petRow[L"allergies"]), form->ProductName))
        {
            return false;
        }

        sqlite3* db = DbHelpers::OpenDatabase(databasePath);
        if (db == nullptr)
        {
            return false;
        }

        const char* sql = "INSERT INTO PetHistory(pet_id, product_id, action_type, date, notes) VALUES(?, ?, ?, ?, ?)";
        sqlite3_stmt* stmt = nullptr;
        bool success = false;

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
        {
            std::string actionType = DbHelpers::ToUtf8String(form->ActionType);
            std::string actionDate = DbHelpers::ToUtf8String(form->ActionDate);
            std::string notes = DbHelpers::ToUtf8String(form->Notes);
            sqlite3_bind_int(stmt, 1, Convert::ToInt32(petRow[L"id"]));
            sqlite3_bind_int(stmt, 2, form->ProductId);
            sqlite3_bind_text(stmt, 3, actionType.c_str(), static_cast<int>(actionType.size()), SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 4, actionDate.c_str(), static_cast<int>(actionDate.size()), SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 5, notes.c_str(), static_cast<int>(notes.size()), SQLITE_TRANSIENT);
            success = sqlite3_step(stmt) == SQLITE_DONE;
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        if (!success)
        {
            MessageBox::Show(L"Не удалось сохранить запись в истории.", L"История", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        LoadPetHistory(Convert::ToInt32(petRow[L"id"]));
        return true;
    }

    bool MainForm::DeleteSelectedHistoryEntry()
    {
        const int historyId = GetSelectedId(petHistoryGrid);
        if (historyId == 0)
        {
            MessageBox::Show(L"Выберите запись в истории.", L"История", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return false;
        }

        if (MessageBox::Show(L"Удалить выбранную запись из истории?", L"Подтверждение", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) != System::Windows::Forms::DialogResult::Yes)
        {
            return false;
        }

        sqlite3* db = DbHelpers::OpenDatabase(databasePath);
        if (db == nullptr)
        {
            return false;
        }

        sqlite3_stmt* stmt = nullptr;
        bool success = false;
        if (sqlite3_prepare_v2(db, "DELETE FROM PetHistory WHERE id = ?", -1, &stmt, nullptr) == SQLITE_OK)
        {
            sqlite3_bind_int(stmt, 1, historyId);
            success = sqlite3_step(stmt) == SQLITE_DONE;
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);

        if (!success)
        {
            MessageBox::Show(L"Не удалось удалить запись.", L"История", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        const int petId = GetSelectedId(petsGrid);
        if (petId != 0)
        {
            LoadPetHistory(petId);
        }
        return true;
    }

    System::Void MainForm::productSearchBox_TextChanged(System::Object^ sender, System::EventArgs^ e)
    {
        ApplyProductFilter();
    }

    System::Void MainForm::productFilterChanged(System::Object^ sender, System::EventArgs^ e)
    {
        ApplyProductFilter();
    }

    System::Void MainForm::addProductButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        SaveProduct(false);
    }

    System::Void MainForm::editProductButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        SaveProduct(true);
    }

    System::Void MainForm::deleteProductButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        DeleteSelectedProduct();
    }

    System::Void MainForm::addCategoryButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        SaveLookup(L"Categories", false);
    }

    System::Void MainForm::editCategoryButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        SaveLookup(L"Categories", true);
    }

    System::Void MainForm::deleteCategoryButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        DeleteLookup(L"Categories", categoriesGrid);
    }

    System::Void MainForm::addLocationButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        SaveLookup(L"Locations", false);
    }

    System::Void MainForm::editLocationButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        SaveLookup(L"Locations", true);
    }

    System::Void MainForm::deleteLocationButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        DeleteLookup(L"Locations", locationsGrid);
    }

    System::Void MainForm::addPetButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        SavePet(false);
    }

    System::Void MainForm::editPetButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        SavePet(true);
    }

    System::Void MainForm::deletePetButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        DeleteSelectedPet();
    }

    System::Void MainForm::addHistoryButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        SaveHistoryEntry();
    }

    System::Void MainForm::deleteHistoryButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        DeleteSelectedHistoryEntry();
    }

    System::Void MainForm::petSearchBox_TextChanged(System::Object^ sender, System::EventArgs^ e)
    {
        ApplyPetFilter();
    }

    System::Void MainForm::petsGrid_SelectionChanged(System::Object^ sender, System::EventArgs^ e)
    {
        const int petId = GetSelectedId(petsGrid);
        if (petId != 0)
        {
            LoadPetHistory(petId);
        }
        else
        {
            UpdateAllergyAlert();
        }
    }
}
