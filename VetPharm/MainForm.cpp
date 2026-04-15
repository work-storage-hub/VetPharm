#include "MainForm.h"
#include "AddProductForm.h"

namespace VetPharm {
    void MainForm::InitializeDataTable()
    {
        // Создаем DataTable
        dataTable = gcnew System::Data::DataTable("VetPharm");

        // Колонка ID с автоинкрементом
        DataColumn^ idColumn = gcnew DataColumn(L"id", System::Type::GetType(L"System.Int32"));
        idColumn->AutoIncrement = true;
        idColumn->AutoIncrementSeed = 1;
        idColumn->AutoIncrementStep = 1;
        idColumn->ReadOnly = true;
        idColumn->Unique = true;
        dataTable->Columns->Add(idColumn);

        // Остальные колонки
        dataTable->Columns->Add(L"Название", System::Type::GetType(L"System.String"));
        dataTable->Columns->Add(L"Категория", System::Type::GetType(L"System.String"));
        dataTable->Columns->Add(L"Фасовка", System::Type::GetType(L"System.Int32"));
        dataTable->Columns->Add(L"Количество", System::Type::GetType(L"System.Int32"));
        dataTable->Columns->Add(L"Единица", System::Type::GetType(L"System.String"));
        dataTable->Columns->Add(L"Цена", System::Type::GetType(L"System.Decimal"));
        dataTable->Columns->Add(L"Локация", System::Type::GetType(L"System.String"));

        // Первичный ключ
        dataTable->PrimaryKey = gcnew cli::array<DataColumn^>{ dataTable->Columns[L"id"] };

        // Привязываем к DataGridView
        dataGridView1->DataSource = dataTable;

        // Настройка отображения
        dataGridView1->AutoGenerateColumns = true;
        dataGridView1->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

        // Делаем колонку ID только для чтения
        if (dataGridView1->Columns[L"id"] != nullptr)
        {
            dataGridView1->Columns[L"id"]->ReadOnly = true;
        }

        // Добавляем тестовые данные
        AddTestData();
    }

    void MainForm::AddTestData()
    {
        // id, name, category, packaging_size, quantity, unit, price, location
        dataTable->Rows->Add(nullptr, L"Амоксициллин", L"Антибиотики", 10, 10, L"таблетка", Decimal(500), L"Стенд 1");
        dataTable->Rows->Add(nullptr, L"Корм Royal Canin", L"Корма", 1, 50, L"кг", Decimal(2500), L"Стенд 2");
        dataTable->Rows->Add(nullptr, L"Гамавит", L"Витамины", 1, 75, L"флакон", Decimal(850), L"Стенд 1");
        dataTable->Rows->Add(nullptr, L"Празицид", L"Антигельминтики", 6, 40, L"таблетка", Decimal(380), L"Склад");
    }

    // ПОКАЗАТЬ ФОРМУ ДОБАВЛЕНИЯ С ВЫПАДАЮЩИМИ СПИСКАМИ
    void MainForm::ShowAddDialog()
    {
        AddProductForm^ addform = gcnew AddProductForm(dataTable);
        addform->ShowDialog();
    }

    // ДОБАВЛЕНИЕ ЗАПИСИ (основной метод)
    void MainForm::AddRecord(String^ name, String^ category, int packaging_size, int quantity, String^ unit, Decimal price, String^ location)
    {
        DataRow^ newRow = dataTable->NewRow();
        newRow[L"name"] = name;
        newRow[L"category"] = category;
        newRow[L"packaging_size"] = packaging_size;
        newRow[L"quantity"] = quantity;
        newRow[L"unit"] = unit;
        newRow[L"price"] = price;
        newRow[L"location"] = location;
        dataTable->Rows->Add(newRow);
    }

    void MainForm::Search(String^ searchText)
    {
        if (String::IsNullOrEmpty(searchText))
        {
            ApplyCombinedFilter();
        }
        else
        {
            String^ category = (category_combo_box->SelectedItem != nullptr && category_combo_box->SelectedItem->ToString() != L"Все")
                ? category_combo_box->SelectedItem->ToString() : nullptr;
            String^ location = (location_combo_box->SelectedItem != nullptr && location_combo_box->SelectedItem->ToString() != L"Все")
                ? location_combo_box->SelectedItem->ToString() : nullptr;

            System::Text::StringBuilder^ filter = gcnew System::Text::StringBuilder();
            filter->Append(String::Format(L"Название LIKE '%{0}%'", searchText));  // ← исправлено

            if (!String::IsNullOrEmpty(category))
            {
                filter->Append(String::Format(L" AND Категория = '{0}'", category));  // ← исправлено
            }
            if (!String::IsNullOrEmpty(location))
            {
                filter->Append(String::Format(L" AND Локация = '{0}'", location));    // ← исправлено
            }

            dataTable->DefaultView->RowFilter = filter->ToString();
        }
    }

    void MainForm::ApplyCombinedFilter()
    {
        String^ searchText = search_text_box->Text;
        String^ category = (category_combo_box->SelectedItem != nullptr && category_combo_box->SelectedItem->ToString() != L"Все")
            ? category_combo_box->SelectedItem->ToString() : nullptr;
        String^ location = (location_combo_box->SelectedItem != nullptr && location_combo_box->SelectedItem->ToString() != L"Все")
            ? location_combo_box->SelectedItem->ToString() : nullptr;

        if (String::IsNullOrEmpty(searchText) && String::IsNullOrEmpty(category) && String::IsNullOrEmpty(location))
        {
            dataTable->DefaultView->RowFilter = nullptr;
            return;
        }

        System::Text::StringBuilder^ filter = gcnew System::Text::StringBuilder();
        bool first = true;

        if (!String::IsNullOrEmpty(searchText))
        {
            filter->Append(String::Format(L"Название LIKE '%{0}%'", searchText));  // ← исправлено
            first = false;
        }

        if (!String::IsNullOrEmpty(category))
        {
            if (!first) filter->Append(L" AND ");
            filter->Append(String::Format(L"Категория = '{0}'", category));  // ← исправлено
            first = false;
        }

        if (!String::IsNullOrEmpty(location))
        {
            if (!first) filter->Append(L" AND ");
            filter->Append(String::Format(L"Локация = '{0}'", location));  // ← исправлено
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
        FilterByCategory(category_combo_box->SelectedItem->ToString());
    }

    System::Void MainForm::location_combo_box_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
    {
        FilterByLocation(location_combo_box->SelectedItem->ToString());
    }
}