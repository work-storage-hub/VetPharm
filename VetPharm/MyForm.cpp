//#include "MyForm.h"
//
//namespace VetPharm {
//	
//}
//
//#pragma once
//
//namespace VetPharm {
//
//    using namespace System;
//    using namespace System::ComponentModel;
//    using namespace System::Collections;
//    using namespace System::Windows::Forms;
//    using namespace System::Data;
//    using namespace System::Drawing;
//
//    public ref class MyForm : public System::Windows::Forms::Form
//    {
//    public:
//        MyForm(void)
//        {
//            InitializeComponent();
//            InitializeDataTable();
//        }
//
//    protected:
//        ~MyForm()
//        {
//            if (components)
//            {
//                delete components;
//            }
//        }
//
//    private:
//        System::Data::DataTable^ dataTable;
//        System::Windows::Forms::TextBox^ textBox1;
//        System::Windows::Forms::Label^ label1;
//        System::Windows::Forms::DataGridView^ dataGridView1;
//        System::Windows::Forms::ComboBox^ comboBox1;
//        System::Windows::Forms::Button^ button1;
//        System::Windows::Forms::ComboBox^ comboBox3;
//        System::Windows::Forms::Button^ button2;
//
//        System::ComponentModel::Container^ components;
//
//#pragma region Windows Form Designer generated code
//        void InitializeComponent(void)
//        {
//            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
//            this->label1 = (gcnew System::Windows::Forms::Label());
//            this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
//            this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
//            this->button1 = (gcnew System::Windows::Forms::Button());
//            this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
//            this->button2 = (gcnew System::Windows::Forms::Button());
//            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
//            this->SuspendLayout();
//            // 
//            // textBox1
//            // 
//            this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
//            this->textBox1->Location = System::Drawing::Point(72, 52);
//            this->textBox1->Name = L"textBox1";
//            this->textBox1->Size = System::Drawing::Size(134, 27);
//            this->textBox1->TabIndex = 0;
//            // 
//            // label1
//            // 
//            this->label1->AutoSize = true;
//            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
//            this->label1->Location = System::Drawing::Point(12, 55);
//            this->label1->Name = L"label1";
//            this->label1->Size = System::Drawing::Size(65, 20);
//            this->label1->TabIndex = 1;
//            this->label1->Text = L"Поиск:";
//            // 
//            // dataGridView1
//            // 
//            this->dataGridView1->AllowUserToAddRows = false;
//            this->dataGridView1->AllowUserToDeleteRows = false;
//            this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
//            this->dataGridView1->Location = System::Drawing::Point(16, 163);
//            this->dataGridView1->Name = L"dataGridView1";
//            this->dataGridView1->RowHeadersWidth = 51;
//            this->dataGridView1->RowTemplate->Height = 24;
//            this->dataGridView1->Size = System::Drawing::Size(1250, 556);
//            this->dataGridView1->TabIndex = 2;
//            // 
//            // comboBox1
//            // 
//            this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
//            this->comboBox1->FormattingEnabled = true;
//            this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
//                L"Все", L"Антибиотики", L"Корма", L"Мазь", L"Витамины",
//                    L"Антигельминтики"
//            });
//            this->comboBox1->Location = System::Drawing::Point(212, 52);
//            this->comboBox1->Name = L"comboBox1";
//            this->comboBox1->Size = System::Drawing::Size(121, 28);
//            this->comboBox1->TabIndex = 3;
//            this->comboBox1->Text = L"Категория";
//            this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
//            // 
//            // button1
//            // 
//            this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
//            this->button1->Location = System::Drawing::Point(12, 12);
//            this->button1->Name = L"button1";
//            this->button1->Size = System::Drawing::Size(115, 34);
//            this->button1->TabIndex = 4;
//            this->button1->Text = L"Добавить";
//            this->button1->UseVisualStyleBackColor = true;
//            this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
//            // 
//            // comboBox3
//            // 
//            this->comboBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
//            this->comboBox3->FormattingEnabled = true;
//            this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"Все", L"Склад 1", L"Склад 2", L"Аптека", L"Магазин" });
//            this->comboBox3->Location = System::Drawing::Point(339, 52);
//            this->comboBox3->Name = L"comboBox3";
//            this->comboBox3->Size = System::Drawing::Size(121, 28);
//            this->comboBox3->TabIndex = 6;
//            this->comboBox3->Text = L"Локация";
//            this->comboBox3->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox3_SelectedIndexChanged);
//            // 
//            // button2
//            // 
//            this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
//            this->button2->Location = System::Drawing::Point(466, 49);
//            this->button2->Name = L"button2";
//            this->button2->Size = System::Drawing::Size(102, 32);
//            this->button2->TabIndex = 7;
//            this->button2->Text = L"Найти";
//            this->button2->UseVisualStyleBackColor = true;
//            this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
//            // 
//            // MyForm
//            // 
//            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
//            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
//            this->ClientSize = System::Drawing::Size(1278, 731);
//            this->Controls->Add(this->button2);
//            this->Controls->Add(this->comboBox3);
//            this->Controls->Add(this->button1);
//            this->Controls->Add(this->comboBox1);
//            this->Controls->Add(this->dataGridView1);
//            this->Controls->Add(this->textBox1);
//            this->Controls->Add(this->label1);
//            this->Name = L"MyForm";
//            this->Text = L"Ветеринарная аптека";
//            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
//            this->ResumeLayout(false);
//            this->PerformLayout();
//
//        }
//#pragma endregion
//
//    private:
//        void InitializeDataTable()
//        {
//            // Создаем DataTable
//            dataTable = gcnew System::Data::DataTable("VetPharm");
//
//            // Колонка ID с автоинкрементом
//            DataColumn^ idColumn = gcnew DataColumn(L"id", System::Type::GetType(L"System.Int32"));
//            idColumn->AutoIncrement = true;
//            idColumn->AutoIncrementSeed = 1;
//            idColumn->AutoIncrementStep = 1;
//            idColumn->ReadOnly = true;
//            idColumn->Unique = true;
//            dataTable->Columns->Add(idColumn);
//
//            // Остальные колонки
//            dataTable->Columns->Add(L"name", System::Type::GetType(L"System.String"));
//            dataTable->Columns->Add(L"category", System::Type::GetType(L"System.String"));
//            dataTable->Columns->Add(L"quantity", System::Type::GetType(L"System.Int32"));
//            dataTable->Columns->Add(L"unit", System::Type::GetType(L"System.String"));
//            dataTable->Columns->Add(L"location", System::Type::GetType(L"System.String"));  // Новая колонка
//
//            // Первичный ключ
//            dataTable->PrimaryKey = gcnew cli::array<DataColumn^>{ dataTable->Columns[L"id"] };
//
//            // Привязываем к DataGridView
//            dataGridView1->DataSource = dataTable;
//
//            // Настройка отображения
//            dataGridView1->AutoGenerateColumns = true;
//            dataGridView1->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
//
//            // Делаем колонку ID только для чтения
//            if (dataGridView1->Columns[L"id"] != nullptr)
//            {
//                dataGridView1->Columns[L"id"]->ReadOnly = true;
//            }
//
//            // Добавляем тестовые данные
//            AddTestData();
//        }
//
//        void AddTestData()
//        {
//            // ID генерируется автоматически (передаем nullptr)
//            dataTable->Rows->Add(nullptr, L"Амоксициллин", L"Антибиотики", 100, L"флакон", L"Склад 1");
//            dataTable->Rows->Add(nullptr, L"Корм Royal Canin", L"Корма", 50, L"кг", L"Склад 2");
//            dataTable->Rows->Add(nullptr, L"Ихтиоловая мазь", L"Мазь", 30, L"туба", L"Аптека");
//            dataTable->Rows->Add(nullptr, L"Гамавит", L"Витамины", 75, L"флакон", L"Склад 1");
//            dataTable->Rows->Add(nullptr, L"Празицид", L"Антигельминтики", 40, L"таблетка", L"Магазин");
//        }
//
//        // ДОБАВЛЕНИЕ ПУСТОЙ СТРОКИ
//        void AddEmptyRecord()
//        {
//            // Добавляем пустую строку (ID сгенерируется автоматически)
//            DataRow^ newRow = dataTable->NewRow();
//            newRow[L"name"] = L"";
//            newRow[L"category"] = L"";
//            newRow[L"quantity"] = 0;
//            newRow[L"unit"] = L"";
//            newRow[L"location"] = L"";
//            dataTable->Rows->Add(newRow);
//
//            // Прокручиваем к новой строке
//            dataGridView1->FirstDisplayedScrollingRowIndex = dataGridView1->Rows->Count - 1;
//
//            MessageBox::Show(String::Format(L"Добавлена новая строка с ID: {0}", newRow[L"id"]),
//                L"Успешно", MessageBoxButtons::OK, MessageBoxIcon::Information);
//        }
//
//        // ПОИСК ПО НАЗВАНИЮ
//        void Search(String^ searchText)
//        {
//            if (String::IsNullOrEmpty(searchText))
//            {
//                // Если есть фильтр по категории или локации, сохраняем их
//                ApplyCombinedFilter();
//            }
//            else
//            {
//                // Поиск по названию с учетом других фильтров
//                String^ category = (comboBox1->SelectedItem != nullptr && comboBox1->SelectedItem->ToString() != L"Все")
//                    ? comboBox1->SelectedItem->ToString() : nullptr;
//                String^ location = (comboBox3->SelectedItem != nullptr && comboBox3->SelectedItem->ToString() != L"Все")
//                    ? comboBox3->SelectedItem->ToString() : nullptr;
//
//                System::Text::StringBuilder^ filter = gcnew System::Text::StringBuilder();
//                filter->Append(String::Format(L"name LIKE '%{0}%'", searchText));
//
//                if (!String::IsNullOrEmpty(category))
//                {
//                    filter->Append(String::Format(L" AND category = '{0}'", category));
//                }
//                if (!String::IsNullOrEmpty(location))
//                {
//                    filter->Append(String::Format(L" AND location = '{0}'", location));
//                }
//
//                dataTable->DefaultView->RowFilter = filter->ToString();
//            }
//        }
//
//        // ФИЛЬТРАЦИЯ ПО КАТЕГОРИИ
//        void FilterByCategory(String^ category)
//        {
//            if (String::IsNullOrEmpty(category) || category == L"Все")
//            {
//                // Применяем поиск и фильтр по локации
//                ApplyCombinedFilter();
//            }
//            else
//            {
//                // Фильтр по категории с учетом поиска и локации
//                ApplyCombinedFilter();
//            }
//        }
//
//        // ФИЛЬТРАЦИЯ ПО ЛОКАЦИИ
//        void FilterByLocation(String^ location)
//        {
//            if (String::IsNullOrEmpty(location) || location == L"Все")
//            {
//                ApplyCombinedFilter();
//            }
//            else
//            {
//                ApplyCombinedFilter();
//            }
//        }
//
//        // ПРИМЕНЕНИЕ КОМБИНИРОВАННОГО ФИЛЬТРА
//        void ApplyCombinedFilter()
//        {
//            String^ searchText = textBox1->Text;
//            String^ category = (comboBox1->SelectedItem != nullptr && comboBox1->SelectedItem->ToString() != L"Все")
//                ? comboBox1->SelectedItem->ToString() : nullptr;
//            String^ location = (comboBox3->SelectedItem != nullptr && comboBox3->SelectedItem->ToString() != L"Все")
//                ? comboBox3->SelectedItem->ToString() : nullptr;
//
//            if (String::IsNullOrEmpty(searchText) && String::IsNullOrEmpty(category) && String::IsNullOrEmpty(location))
//            {
//                dataTable->DefaultView->RowFilter = nullptr;
//                return;
//            }
//
//            System::Text::StringBuilder^ filter = gcnew System::Text::StringBuilder();
//            bool first = true;
//
//            if (!String::IsNullOrEmpty(searchText))
//            {
//                filter->Append(String::Format(L"name LIKE '%{0}%'", searchText));
//                first = false;
//            }
//
//            if (!String::IsNullOrEmpty(category))
//            {
//                if (!first) filter->Append(L" AND ");
//                filter->Append(String::Format(L"category = '{0}'", category));
//                first = false;
//            }
//
//            if (!String::IsNullOrEmpty(location))
//            {
//                if (!first) filter->Append(L" AND ");
//                filter->Append(String::Format(L"location = '{0}'", location));
//            }
//
//            dataTable->DefaultView->RowFilter = filter->ToString();
//        }
//
//        // ВЫПОЛНИТЬ ПОИСК ПО КНОПКЕ
//        void PerformSearch()
//        {
//            Search(textBox1->Text);
//        }
//
//    private:
//        // ОБРАБОТЧИКИ СОБЫТИЙ
//
//        System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
//        {
//            // Добавляем пустую строку с автоинкрементным ID
//            AddEmptyRecord();
//        }
//
//        System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
//        {
//            // Выполняем поиск
//            PerformSearch();
//        }
//
//        System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e)
//        {
//            // Автоматический поиск при изменении текста (можно закомментировать если не нужно)
//            // Search(textBox1->Text);
//        }
//
//        System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
//        {
//            // Фильтрация по категории
//            FilterByCategory(comboBox1->SelectedItem->ToString());
//        }
//
//        System::Void comboBox3_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
//        {
//            // Фильтрация по локации
//            FilterByLocation(comboBox3->SelectedItem->ToString());
//        }
//    };
//}