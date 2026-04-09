//#pragma once
//
//namespace VetPharm {
//
//	using namespace System;
//	using namespace System::ComponentModel;
//	using namespace System::Collections;
//	using namespace System::Windows::Forms;
//	using namespace System::Data;
//	using namespace System::Drawing;
//
//	public ref class MyForm : public System::Windows::Forms::Form
//	{
//	public:
//		MyForm(void)
//		{
//			InitializeComponent();
//			InitializeDataGridView();  // ← ВЫЗЫВАЕМ ЗДЕСЬ
//		}
//
//	protected:
//		~MyForm()
//		{
//			if (components)
//			{
//				delete components;
//			}
//		}
//
//	private:
//		System::Data::DataTable^ dataTable;
//		System::Windows::Forms::TextBox^ textBox1;
//		System::Windows::Forms::Label^ label1;
//		System::Windows::Forms::DataGridView^ dataGridView1;
//		System::Windows::Forms::ComboBox^ comboBox1;
//		System::Windows::Forms::Button^ button1;
//		System::Windows::Forms::ComboBox^ comboBox3;
//
//		System::ComponentModel::Container^ components;
//
//#pragma region Windows Form Designer generated code
//		void InitializeComponent(void)
//		{
//			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
//			this->label1 = (gcnew System::Windows::Forms::Label());
//			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
//			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
//			this->button1 = (gcnew System::Windows::Forms::Button());
//			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
//			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
//			this->SuspendLayout();
//			// 
//			// textBox1
//			// 
//			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
//			this->textBox1->Location = System::Drawing::Point(72, 52);
//			this->textBox1->Name = L"textBox1";
//			this->textBox1->Size = System::Drawing::Size(134, 27);
//			this->textBox1->TabIndex = 0;
//			// 
//			// label1
//			// 
//			this->label1->AutoSize = true;
//			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
//			this->label1->Location = System::Drawing::Point(12, 55);
//			this->label1->Name = L"label1";
//			this->label1->Size = System::Drawing::Size(65, 20);
//			this->label1->TabIndex = 1;
//			this->label1->Text = L"Поиск:";
//			// 
//			// dataGridView1
//			// 
//			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
//			this->dataGridView1->Location = System::Drawing::Point(16, 163);
//			this->dataGridView1->Name = L"dataGridView1";
//			this->dataGridView1->RowHeadersWidth = 51;
//			this->dataGridView1->RowTemplate->Height = 24;
//			this->dataGridView1->Size = System::Drawing::Size(829, 556);
//			this->dataGridView1->TabIndex = 2;
//			// 
//			// comboBox1
//			// 
//			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
//			this->comboBox1->FormattingEnabled = true;
//			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Антибиотики", L"Корма", L"Мазь" });
//			this->comboBox1->Location = System::Drawing::Point(212, 52);
//			this->comboBox1->Name = L"comboBox1";
//			this->comboBox1->Size = System::Drawing::Size(121, 28);
//			this->comboBox1->TabIndex = 3;
//			this->comboBox1->Text = L"Категория";
//			// 
//			// button1
//			// 
//			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
//			this->button1->Location = System::Drawing::Point(12, 12);
//			this->button1->Name = L"button1";
//			this->button1->Size = System::Drawing::Size(115, 34);
//			this->button1->TabIndex = 4;
//			this->button1->Text = L"Добавить";
//			this->button1->UseVisualStyleBackColor = true;
//			// 
//			// comboBox3
//			// 
//			this->comboBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
//			this->comboBox3->FormattingEnabled = true;
//			this->comboBox3->Location = System::Drawing::Point(339, 51);
//			this->comboBox3->Name = L"comboBox3";
//			this->comboBox3->Size = System::Drawing::Size(121, 28);
//			this->comboBox3->TabIndex = 6;
//			this->comboBox3->Text = L"Локация";
//			// 
//			// MyForm
//			// 
//			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
//			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
//			this->ClientSize = System::Drawing::Size(857, 731);
//			this->Controls->Add(this->comboBox3);
//			this->Controls->Add(this->button1);
//			this->Controls->Add(this->comboBox1);
//			this->Controls->Add(this->dataGridView1);
//			this->Controls->Add(this->textBox1);
//			this->Controls->Add(this->label1);
//			this->Name = L"MyForm";
//			this->Text = L"MyForm";
//			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
//			this->ResumeLayout(false);
//			this->PerformLayout();
//		}
//#pragma endregion
//
//	private:
//		// ВЫНЕСЕННЫЙ КОД - теперь он в отдельном методе!
//		void InitializeDataGridView()
//		{
//			// Настраиваем DataGridView
//			dataGridView1->AllowUserToAddRows = true;
//			dataGridView1->AllowUserToDeleteRows = true;
//
//			// Добавляем колонки (если их нет)
//			if (dataGridView1->Columns->Count == 0)
//			{
//				dataGridView1->Columns->Add(L"id", L"ID");
//				dataGridView1->Columns->Add(L"name", L"Название");
//				dataGridView1->Columns->Add(L"category", L"Категория");
//				dataGridView1->Columns->Add(L"quantity", L"Количество");
//				dataGridView1->Columns->Add(L"unit", L"В упаковке");
//			}
//
//			// Тестовые данные
//			dataGridView1->Rows->Add(1, L"Амоксициллин", L"Антибиотики", 100, L"флакон");
//			dataGridView1->Rows->Add(2, L"Корм Royal Canin", L"Корма", 50, L"кг");
//			dataGridView1->Rows->Add(3, L"Ихтиоловая мазь", L"Мазь", 30, L"туба");
//		}
//	};
//}

#pragma once

namespace VetPharm {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            InitializeDataTable();
            //this->Icon = gcnew System::Drawing::Icon(L"IDI_ICON1");
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Data::DataTable^ dataTable;
        System::Windows::Forms::TextBox^ textBox1;
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::DataGridView^ dataGridView1;
        System::Windows::Forms::ComboBox^ comboBox1;
        System::Windows::Forms::Button^ button1;
        System::Windows::Forms::ComboBox^ comboBox3;
        System::Windows::Forms::Button^ button2;

        // Контролы для формы добавления
        System::Windows::Forms::Form^ addForm;
        System::Windows::Forms::TextBox^ txtName;
        System::Windows::Forms::ComboBox^ cmbCategory;
        System::Windows::Forms::NumericUpDown^ numQuantity;
        System::Windows::Forms::TextBox^ txtUnit;
        System::Windows::Forms::ComboBox^ cmbLocation;

        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
            this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
            this->button2 = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
            this->SuspendLayout();
            // 
            // textBox1
            // 
            this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
            this->textBox1->Location = System::Drawing::Point(72, 52);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(134, 27);
            this->textBox1->TabIndex = 0;
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
            this->label1->Location = System::Drawing::Point(12, 55);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(65, 20);
            this->label1->TabIndex = 1;
            this->label1->Text = L"Поиск:";
            // 
            // dataGridView1
            // 
            this->dataGridView1->AllowUserToAddRows = false;
            this->dataGridView1->AllowUserToDeleteRows = false;
            this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView1->Location = System::Drawing::Point(16, 163);
            this->dataGridView1->Name = L"dataGridView1";
            this->dataGridView1->RowHeadersWidth = 51;
            this->dataGridView1->RowTemplate->Height = 24;
            this->dataGridView1->Size = System::Drawing::Size(1306, 556);
            this->dataGridView1->TabIndex = 2;
            // 
            // comboBox1
            // 
            this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
            this->comboBox1->FormattingEnabled = true;
            this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
                L"Все", L"Антибиотики", L"Корма", L"Мазь", L"Витамины",
                    L"Антигельминтики"
            });
            this->comboBox1->Location = System::Drawing::Point(212, 52);
            this->comboBox1->Name = L"comboBox1";
            this->comboBox1->Size = System::Drawing::Size(121, 28);
            this->comboBox1->TabIndex = 3;
            this->comboBox1->Text = L"Категория";
            this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
            // 
            // button1
            // 
            this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
            this->button1->Location = System::Drawing::Point(12, 12);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(115, 34);
            this->button1->TabIndex = 4;
            this->button1->Text = L"Добавить";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
            // 
            // comboBox3
            // 
            this->comboBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
            this->comboBox3->FormattingEnabled = true;
            this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"Все", L"Склад 1", L"Склад 2", L"Аптека", L"Магазин" });
            this->comboBox3->Location = System::Drawing::Point(339, 52);
            this->comboBox3->Name = L"comboBox3";
            this->comboBox3->Size = System::Drawing::Size(121, 28);
            this->comboBox3->TabIndex = 6;
            this->comboBox3->Text = L"Локация";
            this->comboBox3->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox3_SelectedIndexChanged);
            // 
            // button2
            // 
            this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
            this->button2->Location = System::Drawing::Point(466, 49);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(102, 32);
            this->button2->TabIndex = 7;
            this->button2->Text = L"Найти";
            this->button2->UseVisualStyleBackColor = true;
            this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1334, 731);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->comboBox3);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->comboBox1);
            this->Controls->Add(this->dataGridView1);
            this->Controls->Add(this->textBox1);
            this->Controls->Add(this->label1);
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->Name = L"MyForm";
            this->Text = L"VetPharm";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
        void InitializeDataTable()
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
            dataTable->Columns->Add(L"name", System::Type::GetType(L"System.String"));
            dataTable->Columns->Add(L"category", System::Type::GetType(L"System.String"));
            dataTable->Columns->Add(L"quantity", System::Type::GetType(L"System.Int32"));
            dataTable->Columns->Add(L"unit", System::Type::GetType(L"System.String"));
            dataTable->Columns->Add(L"location", System::Type::GetType(L"System.String"));

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

        void AddTestData()
        {
            dataTable->Rows->Add(nullptr, L"Амоксициллин", L"Антибиотики", 100, L"флакон", L"Склад 1");
            dataTable->Rows->Add(nullptr, L"Корм Royal Canin", L"Корма", 50, L"кг", L"Склад 2");
            dataTable->Rows->Add(nullptr, L"Ихтиоловая мазь", L"Мазь", 30, L"туба", L"Аптека");
            dataTable->Rows->Add(nullptr, L"Гамавит", L"Витамины", 75, L"флакон", L"Склад 1");
            dataTable->Rows->Add(nullptr, L"Празицид", L"Антигельминтики", 40, L"таблетка", L"Магазин");
        }

        // ПОКАЗАТЬ ФОРМУ ДОБАВЛЕНИЯ С ВЫПАДАЮЩИМИ СПИСКАМИ
        void ShowAddDialog()
        {
            // Создаем форму для добавления
            addForm = gcnew Form();
            addForm->Text = L"Добавление товара";
            addForm->Size = System::Drawing::Size(400, 350);
            addForm->StartPosition = FormStartPosition::CenterParent;
            addForm->MaximizeBox = false;
            addForm->MinimizeBox = false;
            addForm->BackColor = System::Drawing::Color::White;

            // Поле "Название"
            Label^ lblName = gcnew Label();
            lblName->Text = L"Название товара:";
            lblName->Location = System::Drawing::Point(20, 20);
            lblName->Size = System::Drawing::Size(120, 25);
            lblName->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F);

            txtName = gcnew TextBox();
            txtName->Location = System::Drawing::Point(150, 20);
            txtName->Size = System::Drawing::Size(200, 27);
            txtName->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F);

            // Поле "Категория" - ВЫПАДАЮЩИЙ СПИСОК
            Label^ lblCategory = gcnew Label();
            lblCategory->Text = L"Категория:";
            lblCategory->Location = System::Drawing::Point(20, 60);
            lblCategory->Size = System::Drawing::Size(120, 25);
            lblCategory->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F);

            cmbCategory = gcnew ComboBox();
            cmbCategory->Location = System::Drawing::Point(150, 60);
            cmbCategory->Size = System::Drawing::Size(200, 28);
            cmbCategory->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F);
            cmbCategory->DropDownStyle = ComboBoxStyle::DropDownList;  // Только выбор из списка
            cmbCategory->Items->AddRange(gcnew cli::array<System::Object^> {
                L"Антибиотики",
                    L"Корма",
                    L"Мазь",
                    L"Витамины",
                    L"Антигельминтики",
                    L"Противовоспалительные",
                    L"Пробиотики"
            });
            cmbCategory->SelectedIndex = 0;  // Выбираем первый элемент

            // Поле "Количество"
            Label^ lblQuantity = gcnew Label();
            lblQuantity->Text = L"Количество:";
            lblQuantity->Location = System::Drawing::Point(20, 100);
            lblQuantity->Size = System::Drawing::Size(120, 25);
            lblQuantity->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F);

            numQuantity = gcnew NumericUpDown();
            numQuantity->Location = System::Drawing::Point(150, 100);
            numQuantity->Size = System::Drawing::Size(200, 27);
            numQuantity->Minimum = 0;
            numQuantity->Maximum = 10000;
            numQuantity->Value = 1;
            numQuantity->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F);

            // Поле "Упаковка"
            Label^ lblUnit = gcnew Label();
            lblUnit->Text = L"Упаковка:";
            lblUnit->Location = System::Drawing::Point(20, 140);
            lblUnit->Size = System::Drawing::Size(120, 25);
            lblUnit->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F);

            txtUnit = gcnew TextBox();
            txtUnit->Location = System::Drawing::Point(150, 140);
            txtUnit->Size = System::Drawing::Size(200, 27);
            txtUnit->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F);
            txtUnit->Text = L"флакон";

            // Поле "Локация" - ВЫПАДАЮЩИЙ СПИСОК
            Label^ lblLocation = gcnew Label();
            lblLocation->Text = L"Локация:";
            lblLocation->Location = System::Drawing::Point(20, 180);
            lblLocation->Size = System::Drawing::Size(120, 25);
            lblLocation->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F);

            cmbLocation = gcnew ComboBox();
            cmbLocation->Location = System::Drawing::Point(150, 180);
            cmbLocation->Size = System::Drawing::Size(200, 28);
            cmbLocation->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F);
            cmbLocation->DropDownStyle = ComboBoxStyle::DropDownList;  // Только выбор из списка
            cmbLocation->Items->AddRange(gcnew cli::array<System::Object^> {
                L"Склад 1",
                    L"Склад 2",
                    L"Аптека",
                    L"Магазин",
                    L"Склад 3"
            });
            cmbLocation->SelectedIndex = 0;  // Выбираем первый элемент

            // Кнопки
            Button^ btnOk = gcnew Button();
            btnOk->Text = L"Добавить";
            btnOk->Location = System::Drawing::Point(80, 240);
            btnOk->Size = System::Drawing::Size(110, 40);
            btnOk->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F);
            btnOk->BackColor = System::Drawing::Color::LightGreen;
            btnOk->FlatStyle = FlatStyle::Flat;
            btnOk->Click += gcnew System::EventHandler(this, &MyForm::btnOk_Click);

            Button^ btnCancel = gcnew Button();
            btnCancel->Text = L"Отмена";
            btnCancel->Location = System::Drawing::Point(210, 240);
            btnCancel->Size = System::Drawing::Size(110, 40);
            btnCancel->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F);
            btnCancel->BackColor = System::Drawing::Color::LightCoral;
            btnCancel->FlatStyle = FlatStyle::Flat;
            btnCancel->Click += gcnew System::EventHandler(this, &MyForm::btnCancel_Click);

            // Добавляем контролы на форму
            addForm->Controls->Add(lblName);
            addForm->Controls->Add(txtName);
            addForm->Controls->Add(lblCategory);
            addForm->Controls->Add(cmbCategory);
            addForm->Controls->Add(lblQuantity);
            addForm->Controls->Add(numQuantity);
            addForm->Controls->Add(lblUnit);
            addForm->Controls->Add(txtUnit);
            addForm->Controls->Add(lblLocation);
            addForm->Controls->Add(cmbLocation);
            addForm->Controls->Add(btnOk);
            addForm->Controls->Add(btnCancel);

            // Показываем форму
            addForm->ShowDialog();
        }

        // ОБРАБОТЧИК КНОПКИ "Добавить" НА ФОРМЕ
        System::Void btnOk_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // Проверяем заполнение обязательных полей
            if (String::IsNullOrEmpty(txtName->Text))
            {
                MessageBox::Show(L"Введите название товара!", L"Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Добавляем запись (ID сгенерируется автоматически)
            DataRow^ newRow = dataTable->NewRow();
            newRow[L"name"] = txtName->Text;
            newRow[L"category"] = cmbCategory->SelectedItem->ToString();
            newRow[L"quantity"] = safe_cast<int>(numQuantity->Value);
            newRow[L"unit"] = txtUnit->Text;
            newRow[L"location"] = cmbLocation->SelectedItem->ToString();
            dataTable->Rows->Add(newRow);

            // Прокручиваем к новой строке
            dataGridView1->FirstDisplayedScrollingRowIndex = dataGridView1->Rows->Count - 1;

            MessageBox::Show(String::Format(L"Товар успешно добавлен!\nID: {0}", newRow[L"id"]),
                L"Успешно", MessageBoxButtons::OK, MessageBoxIcon::Information);

            // Закрываем форму
            addForm->Close();
        }

        // ОБРАБОТЧИК КНОПКИ "Отмена"
        System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e)
        {
            addForm->Close();
        }

        // ДОБАВЛЕНИЕ ЗАПИСИ (основной метод)
        void AddRecord(String^ name, String^ category, int quantity, String^ unit, String^ location)
        {
            DataRow^ newRow = dataTable->NewRow();
            newRow[L"name"] = name;
            newRow[L"category"] = category;
            newRow[L"quantity"] = quantity;
            newRow[L"unit"] = unit;
            newRow[L"location"] = location;
            dataTable->Rows->Add(newRow);
        }

        // ПОИСК ПО НАЗВАНИЮ
        void Search(String^ searchText)
        {
            if (String::IsNullOrEmpty(searchText))
            {
                ApplyCombinedFilter();
            }
            else
            {
                String^ category = (comboBox1->SelectedItem != nullptr && comboBox1->SelectedItem->ToString() != L"Все")
                    ? comboBox1->SelectedItem->ToString() : nullptr;
                String^ location = (comboBox3->SelectedItem != nullptr && comboBox3->SelectedItem->ToString() != L"Все")
                    ? comboBox3->SelectedItem->ToString() : nullptr;

                System::Text::StringBuilder^ filter = gcnew System::Text::StringBuilder();
                filter->Append(String::Format(L"name LIKE '%{0}%'", searchText));

                if (!String::IsNullOrEmpty(category))
                {
                    filter->Append(String::Format(L" AND category = '{0}'", category));
                }
                if (!String::IsNullOrEmpty(location))
                {
                    filter->Append(String::Format(L" AND location = '{0}'", location));
                }

                dataTable->DefaultView->RowFilter = filter->ToString();
            }
        }

        // ФИЛЬТРАЦИЯ ПО КАТЕГОРИИ
        void FilterByCategory(String^ category)
        {
            ApplyCombinedFilter();
        }

        // ФИЛЬТРАЦИЯ ПО ЛОКАЦИИ
        void FilterByLocation(String^ location)
        {
            ApplyCombinedFilter();
        }

        // ПРИМЕНЕНИЕ КОМБИНИРОВАННОГО ФИЛЬТРА
        void ApplyCombinedFilter()
        {
            String^ searchText = textBox1->Text;
            String^ category = (comboBox1->SelectedItem != nullptr && comboBox1->SelectedItem->ToString() != L"Все")
                ? comboBox1->SelectedItem->ToString() : nullptr;
            String^ location = (comboBox3->SelectedItem != nullptr && comboBox3->SelectedItem->ToString() != L"Все")
                ? comboBox3->SelectedItem->ToString() : nullptr;

            if (String::IsNullOrEmpty(searchText) && String::IsNullOrEmpty(category) && String::IsNullOrEmpty(location))
            {
                dataTable->DefaultView->RowFilter = nullptr;
                return;
            }

            System::Text::StringBuilder^ filter = gcnew System::Text::StringBuilder();
            bool first = true;

            if (!String::IsNullOrEmpty(searchText))
            {
                filter->Append(String::Format(L"name LIKE '%{0}%'", searchText));
                first = false;
            }

            if (!String::IsNullOrEmpty(category))
            {
                if (!first) filter->Append(L" AND ");
                filter->Append(String::Format(L"category = '{0}'", category));
                first = false;
            }

            if (!String::IsNullOrEmpty(location))
            {
                if (!first) filter->Append(L" AND ");
                filter->Append(String::Format(L"location = '{0}'", location));
            }

            dataTable->DefaultView->RowFilter = filter->ToString();
        }

        void PerformSearch()
        {
            Search(textBox1->Text);
        }

    private:
        // ОБРАБОТЧИКИ СОБЫТИЙ

        System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // Показываем форму добавления с выпадающими списками
            ShowAddDialog();
        }

        System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
        {
            PerformSearch();
        }

        System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
        {
            FilterByCategory(comboBox1->SelectedItem->ToString());
        }

        System::Void comboBox3_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
        {
            FilterByLocation(comboBox3->SelectedItem->ToString());
        }
    };
}