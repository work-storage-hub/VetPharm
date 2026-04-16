#include "MainForm.h"
#include "AddProductForm.h"
#include <sqlite3.h>
#include <string>
#include <cstring>
#include <vcclr.h>

using namespace System::IO;
using namespace System::Text;

namespace
{
    static std::string ToUtf8String(System::String^ value)
    {
        if (value == nullptr)
        {
            return std::string();
        }

        array<System::Byte>^ bytes = Encoding::UTF8->GetBytes(value);
        std::string result(bytes->Length, '\0');
        if (bytes->Length > 0)
        {
            pin_ptr<System::Byte> pinnedBytes = &bytes[0];
            memcpy(&result[0], pinnedBytes, bytes->Length);
        }

        return result;
    }

    static System::String^ FromUtf8Column(sqlite3_stmt* stmt, int index)
    {
        const unsigned char* value = sqlite3_column_text(stmt, index);
        if (value == nullptr)
        {
            return System::String::Empty;
        }

        return gcnew System::String(reinterpret_cast<const char*>(value), 0, sqlite3_column_bytes(stmt, index), Encoding::UTF8);
    }
}

namespace VetPharm {
    void AddProductForm::InitializeComboBoxes()
    {
        unit_combo_box->Items->Clear();
        unit_combo_box->Items->AddRange(gcnew cli::array<System::Object^> {
            L"миллилитры",
            L"граммы",
            L"таблетки",
            L"штуки"
        });
        unit_combo_box->SelectedIndex = 0;
    }

    void AddProductForm::ConfigureLookupComboBox(System::Windows::Forms::ComboBox^ comboBox, DataTable^ sourceTable)
    {
        comboBox->DataSource = sourceTable;
        comboBox->DisplayMember = L"name";
        comboBox->ValueMember = L"id";

        if (sourceTable != nullptr && sourceTable->Rows->Count > 0)
        {
            comboBox->SelectedIndex = 0;
        }
    }

    void AddProductForm::LoadLookupData()
    {
        categoriesTable = gcnew DataTable();
        locationsTable = gcnew DataTable();

        sqlite3* db = nullptr;
        if (sqlite3_open(ToUtf8String(databasePath).c_str(), &db) != SQLITE_OK)
        {
            MessageBox::Show(L"Не удалось открыть БД для загрузки справочников.", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        const char* categorySql = "SELECT id, name FROM Categories ORDER BY name";
        sqlite3_stmt* categoryStmt = nullptr;
        if (sqlite3_prepare_v2(db, categorySql, -1, &categoryStmt, nullptr) == SQLITE_OK)
        {
            categoriesTable->Columns->Add(L"id", Int32::typeid);
            categoriesTable->Columns->Add(L"name", String::typeid);

            while (sqlite3_step(categoryStmt) == SQLITE_ROW)
            {
                DataRow^ row = categoriesTable->NewRow();
                row[L"id"] = sqlite3_column_int(categoryStmt, 0);
                row[L"name"] = FromUtf8Column(categoryStmt, 1);
                categoriesTable->Rows->Add(row);
            }
        }
        sqlite3_finalize(categoryStmt);

        const char* locationSql = "SELECT id, name FROM Locations ORDER BY name";
        sqlite3_stmt* locationStmt = nullptr;
        if (sqlite3_prepare_v2(db, locationSql, -1, &locationStmt, nullptr) == SQLITE_OK)
        {
            locationsTable->Columns->Add(L"id", Int32::typeid);
            locationsTable->Columns->Add(L"name", String::typeid);

            while (sqlite3_step(locationStmt) == SQLITE_ROW)
            {
                DataRow^ row = locationsTable->NewRow();
                row[L"id"] = sqlite3_column_int(locationStmt, 0);
                row[L"name"] = FromUtf8Column(locationStmt, 1);
                locationsTable->Rows->Add(row);
            }
        }
        sqlite3_finalize(locationStmt);
        sqlite3_close(db);

        ConfigureLookupComboBox(category_combo_box, categoriesTable);
        ConfigureLookupComboBox(location_combo_box, locationsTable);

        add_button->Enabled = categoriesTable->Rows->Count > 0 && locationsTable->Rows->Count > 0;
        if (!add_button->Enabled)
        {
            MessageBox::Show(L"Для добавления товара в БД должны быть заполнены таблицы Categories и Locations.",
                L"Нет справочников", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }
    }

    bool AddProductForm::InsertProductIntoDatabase(int% newProductId)
    {
        sqlite3* db = nullptr;
        if (sqlite3_open(ToUtf8String(databasePath).c_str(), &db) != SQLITE_OK)
        {
            MessageBox::Show(L"Не удалось открыть БД.", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        const char* sql = "INSERT INTO Products (name, category, packaging_size, quantity, unit, location, price) "
            "VALUES (?, ?, ?, ?, ?, ?, ?)";

        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        {
            MessageBox::Show(L"Не удалось подготовить INSERT-запрос.", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            sqlite3_close(db);
            return false;
        }

        std::string nameUtf8 = ToUtf8String(name_text_box->Text->Trim());
        std::string unitUtf8 = ToUtf8String(unit_combo_box->Text);

        sqlite3_bind_text(stmt, 1, nameUtf8.c_str(), static_cast<int>(nameUtf8.size()), SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, safe_cast<int>(category_combo_box->SelectedValue));
        sqlite3_bind_int(stmt, 3, Decimal::ToInt32(packaging_size_numericUpDown->Value));
        sqlite3_bind_int(stmt, 4, Decimal::ToInt32(quantity_numericUpDown->Value));
        sqlite3_bind_text(stmt, 5, unitUtf8.c_str(), static_cast<int>(unitUtf8.size()), SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 6, safe_cast<int>(location_combo_box->SelectedValue));
        sqlite3_bind_int(stmt, 7, Decimal::ToInt32(price_numericUpDown->Value));

        bool success = sqlite3_step(stmt) == SQLITE_DONE;
        if (success)
        {
            newProductId = static_cast<int>(sqlite3_last_insert_rowid(db));
        }
        else
        {
            MessageBox::Show(L"Ошибка при сохранении товара в БД.", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return success;
    }

    System::Void AddProductForm::exit_button_Click(System::Object^ sender, System::EventArgs^ e)
    {
        Close();
    }

    System::Void AddProductForm::add_button_Click(System::Object^ sender, System::EventArgs^ e)
    {
        String^ productName = name_text_box->Text->Trim();
        if (String::IsNullOrWhiteSpace(productName))
        {
            MessageBox::Show(L"Введите название товара!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        if (category_combo_box->SelectedValue == nullptr || location_combo_box->SelectedValue == nullptr)
        {
            MessageBox::Show(L"Выберите категорию и локацию из базы данных.", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        int newProductId = 0;
        if (!InsertProductIntoDatabase(newProductId))
        {
            return;
        }

        DataRow^ newRow = productsTable->NewRow();
        newRow[L"id"] = newProductId;
        newRow[L"Название"] = productName;
        newRow[L"Категория"] = category_combo_box->Text;
        newRow[L"Фасовка"] = Decimal::ToInt32(packaging_size_numericUpDown->Value);
        newRow[L"Количество"] = Decimal::ToInt32(quantity_numericUpDown->Value);
        newRow[L"Единица"] = unit_combo_box->Text;
        newRow[L"Локация"] = location_combo_box->Text;
        newRow[L"Цена"] = Decimal::ToInt32(price_numericUpDown->Value);
        productsTable->Rows->Add(newRow);

        MessageBox::Show(
            String::Format(L"Товар успешно добавлен.\nID: {0}", newProductId),
            L"Успешно", MessageBoxButtons::OK, MessageBoxIcon::Information);
        Close();
    }
}
