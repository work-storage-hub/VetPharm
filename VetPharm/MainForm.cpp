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
    System::String^ MainForm::ResolveDatabasePath()
    {
        array<String^>^ candidates = gcnew array<String^>
        {
            Path::Combine(Application::StartupPath, L"VetPharmDB.db"),
            Path::GetFullPath(Path::Combine(Application::StartupPath, L"..\\..\\VetPharm\\VetPharmDB.db")),
            Path::GetFullPath(Path::Combine(Application::StartupPath, L"..\\..\\..\\VetPharm\\VetPharmDB.db")),
            Path::GetFullPath(Path::Combine(Application::StartupPath, L"..\\..\\..\\..\\VetPharm\\VetPharmDB.db"))
        };

        for each (String ^ candidate in candidates)
        {
            if (File::Exists(candidate))
            {
                return candidate;
            }
        }

        return Path::Combine(Application::StartupPath, L"VetPharmDB.db");
    }

    System::String^ MainForm::EscapeRowFilterValue(System::String^ value)
    {
        if (String::IsNullOrEmpty(value))
        {
            return String::Empty;
        }

        return value->Replace(L"'", L"''")->Replace(L"[", L"[[]")->Replace(L"%", L"[%]")->Replace(L"*", L"[*]");
    }

    void MainForm::InitializeDataTable()
    {
        sqlite3* db = nullptr;
        if (sqlite3_open(ToUtf8String(databasePath).c_str(), &db) != SQLITE_OK)
        {
            MessageBox::Show(L"Не удалось открыть БД!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        dataTable = gcnew DataTable(L"Products");
        dataTable->Columns->Add(L"id", Int32::typeid);
        dataTable->Columns->Add(L"Название", String::typeid);
        dataTable->Columns->Add(L"Категория", String::typeid);
        dataTable->Columns->Add(L"Фасовка", Int32::typeid);
        dataTable->Columns->Add(L"Количество", Int32::typeid);
        dataTable->Columns->Add(L"Единица", String::typeid);
        dataTable->Columns->Add(L"Локация", String::typeid);
        dataTable->Columns->Add(L"Цена", Int32::typeid);

        const char* sql =
            "SELECT p.id, p.name, c.name, p.packaging_size, p.quantity, p.unit, l.name, p.price "
            "FROM Products p "
            "INNER JOIN Categories c ON c.id = p.category "
            "INNER JOIN Locations l ON l.id = p.location "
            "ORDER BY p.id";

        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
        {
            while (sqlite3_step(stmt) == SQLITE_ROW)
            {
                DataRow^ row = dataTable->NewRow();
                row[L"id"] = sqlite3_column_int(stmt, 0);
                row[L"Название"] = FromUtf8Column(stmt, 1);
                row[L"Категория"] = FromUtf8Column(stmt, 2);
                row[L"Фасовка"] = sqlite3_column_int(stmt, 3);
                row[L"Количество"] = sqlite3_column_int(stmt, 4);
                row[L"Единица"] = FromUtf8Column(stmt, 5);
                row[L"Локация"] = FromUtf8Column(stmt, 6);
                row[L"Цена"] = sqlite3_column_int(stmt, 7);
                dataTable->Rows->Add(row);
            }
        }
        else
        {
            MessageBox::Show(L"Ошибка чтения таблицы Products.", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        dataGridView1->DataSource = dataTable;
        dataGridView1->AutoGenerateColumns = true;
        dataGridView1->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

        if (dataGridView1->Columns->Contains(L"id"))
        {
            dataGridView1->Columns[L"id"]->HeaderText = L"ID";
        }
    }

    void MainForm::LoadFilterComboBoxes()
    {
        category_combo_box->Items->Clear();
        location_combo_box->Items->Clear();

        category_combo_box->Items->Add(L"Все");
        location_combo_box->Items->Add(L"Все");

        sqlite3* db = nullptr;
        if (sqlite3_open(ToUtf8String(databasePath).c_str(), &db) != SQLITE_OK)
        {
            MessageBox::Show(L"Не удалось загрузить категории и локации.", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        const char* categorySql = "SELECT name FROM Categories ORDER BY name";
        sqlite3_stmt* categoryStmt = nullptr;
        if (sqlite3_prepare_v2(db, categorySql, -1, &categoryStmt, nullptr) == SQLITE_OK)
        {
            while (sqlite3_step(categoryStmt) == SQLITE_ROW)
            {
                category_combo_box->Items->Add(FromUtf8Column(categoryStmt, 0));
            }
        }
        sqlite3_finalize(categoryStmt);

        const char* locationSql = "SELECT name FROM Locations ORDER BY name";
        sqlite3_stmt* locationStmt = nullptr;
        if (sqlite3_prepare_v2(db, locationSql, -1, &locationStmt, nullptr) == SQLITE_OK)
        {
            while (sqlite3_step(locationStmt) == SQLITE_ROW)
            {
                location_combo_box->Items->Add(FromUtf8Column(locationStmt, 0));
            }
        }
        sqlite3_finalize(locationStmt);
        sqlite3_close(db);

        category_combo_box->SelectedIndex = 0;
        location_combo_box->SelectedIndex = 0;
    }

    void MainForm::ShowAddDialog()
    {
        AddProductForm^ addform = gcnew AddProductForm(dataTable, databasePath);
        addform->ShowDialog();
    }

    void MainForm::AddRecord(String^ name, String^ category, int packaging_size, int quantity, String^ unit, Decimal price, String^ location)
    {
        // Логика перенесена в AddProductForm::InsertProductIntoDatabase.
    }

    void MainForm::Search(String^ searchText)
    {
        if (String::IsNullOrWhiteSpace(searchText))
        {
            ApplyCombinedFilter();
            return;
        }

        ApplyCombinedFilter();
    }

    void MainForm::ApplyCombinedFilter()
    {
        String^ searchText = search_text_box->Text->Trim();
        String^ category = (category_combo_box->SelectedItem != nullptr && category_combo_box->SelectedItem->ToString() != L"Все")
            ? category_combo_box->SelectedItem->ToString() : nullptr;
        String^ location = (location_combo_box->SelectedItem != nullptr && location_combo_box->SelectedItem->ToString() != L"Все")
            ? location_combo_box->SelectedItem->ToString() : nullptr;

        if (String::IsNullOrEmpty(searchText) && String::IsNullOrEmpty(category) && String::IsNullOrEmpty(location))
        {
            dataTable->DefaultView->RowFilter = String::Empty;
            return;
        }

        StringBuilder^ filter = gcnew StringBuilder();
        bool first = true;

        if (!String::IsNullOrEmpty(searchText))
        {
            filter->Append(String::Format(L"Название LIKE '%{0}%'", EscapeRowFilterValue(searchText)));
            first = false;
        }

        if (!String::IsNullOrEmpty(category))
        {
            if (!first) filter->Append(L" AND ");
            filter->Append(String::Format(L"Категория = '{0}'", EscapeRowFilterValue(category)));
            first = false;
        }

        if (!String::IsNullOrEmpty(location))
        {
            if (!first) filter->Append(L" AND ");
            filter->Append(String::Format(L"Локация = '{0}'", EscapeRowFilterValue(location)));
        }

        dataTable->DefaultView->RowFilter = filter->ToString();
    }

    void MainForm::FilterByCategory(String^ category)
    {
        ApplyCombinedFilter();
    }

    void MainForm::FilterByLocation(String^ location)
    {
        ApplyCombinedFilter();
    }

    void MainForm::PerformSearch()
    {
        Search(search_text_box->Text);
    }

    System::Void MainForm::add_button_Click(System::Object^ sender, System::EventArgs^ e)
    {
        ShowAddDialog();
    }

    System::Void MainForm::search_button_Click(System::Object^ sender, System::EventArgs^ e)
    {
        PerformSearch();
    }

    System::Void MainForm::category_combo_box_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
    {
        ApplyCombinedFilter();
    }

    System::Void MainForm::location_combo_box_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
    {
        ApplyCombinedFilter();
    }
}
