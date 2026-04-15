#pragma once

namespace VetPharm {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm(void)
        {
            InitializeComponent();
            InitializeDataTable();
        }

    protected:
        ~MainForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Data::DataTable^ dataTable;
    private: System::Windows::Forms::TextBox^ search_text_box;
    private: System::Windows::Forms::Label^ search_label;


        System::Windows::Forms::DataGridView^ dataGridView1;
    private: System::Windows::Forms::ComboBox^ category_combo_box;

    private: System::Windows::Forms::Button^ add_button;
    private: System::Windows::Forms::ComboBox^ location_combo_box;


    private: System::Windows::Forms::Button^ search_button;


        System::Windows::Forms::Form^ addForm;
        System::Windows::Forms::TextBox^ txtName;
        System::Windows::Forms::ComboBox^ cmbCategory;
        System::Windows::Forms::NumericUpDown^ numQuantity;
        System::Windows::Forms::TextBox^ txtUnit;
        System::Windows::Forms::ComboBox^ cmbLocation;
    private: System::Windows::Forms::Button^ clients_button;


        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
            this->search_text_box = (gcnew System::Windows::Forms::TextBox());
            this->search_label = (gcnew System::Windows::Forms::Label());
            this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
            this->category_combo_box = (gcnew System::Windows::Forms::ComboBox());
            this->add_button = (gcnew System::Windows::Forms::Button());
            this->location_combo_box = (gcnew System::Windows::Forms::ComboBox());
            this->search_button = (gcnew System::Windows::Forms::Button());
            this->clients_button = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
            this->SuspendLayout();
            // 
            // search_text_box
            // 
            this->search_text_box->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
            this->search_text_box->Location = System::Drawing::Point(72, 52);
            this->search_text_box->Name = L"search_text_box";
            this->search_text_box->Size = System::Drawing::Size(134, 27);
            this->search_text_box->TabIndex = 0;
            // 
            // search_label
            // 
            this->search_label->AutoSize = true;
            this->search_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
            this->search_label->Location = System::Drawing::Point(12, 55);
            this->search_label->Name = L"search_label";
            this->search_label->Size = System::Drawing::Size(65, 20);
            this->search_label->TabIndex = 1;
            this->search_label->Text = L"Поиск:";
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
            // category_combo_box
            // 
            this->category_combo_box->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
            this->category_combo_box->FormattingEnabled = true;
            this->category_combo_box->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
                L"Все", L"Антибиотики", L"Корма", L"Мазь",
                    L"Витамины", L"Антигельминтики"
            });
            this->category_combo_box->Location = System::Drawing::Point(212, 52);
            this->category_combo_box->Name = L"category_combo_box";
            this->category_combo_box->Size = System::Drawing::Size(121, 28);
            this->category_combo_box->TabIndex = 3;
            this->category_combo_box->Text = L"Категория";
            this->category_combo_box->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::category_combo_box_SelectedIndexChanged);
            // 
            // add_button
            // 
            this->add_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
            this->add_button->Location = System::Drawing::Point(12, 12);
            this->add_button->Name = L"add_button";
            this->add_button->Size = System::Drawing::Size(115, 34);
            this->add_button->TabIndex = 4;
            this->add_button->Text = L"Добавить";
            this->add_button->UseVisualStyleBackColor = true;
            this->add_button->Click += gcnew System::EventHandler(this, &MainForm::add_button_Click);
            // 
            // location_combo_box
            // 
            this->location_combo_box->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
            this->location_combo_box->FormattingEnabled = true;
            this->location_combo_box->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
                L"Все", L"Склад 1", L"Склад 2", L"Аптека",
                    L"Магазин"
            });
            this->location_combo_box->Location = System::Drawing::Point(339, 52);
            this->location_combo_box->Name = L"location_combo_box";
            this->location_combo_box->Size = System::Drawing::Size(121, 28);
            this->location_combo_box->TabIndex = 6;
            this->location_combo_box->Text = L"Локация";
            this->location_combo_box->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::location_combo_box_SelectedIndexChanged);
            // 
            // search_button
            // 
            this->search_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
            this->search_button->Location = System::Drawing::Point(466, 49);
            this->search_button->Name = L"search_button";
            this->search_button->Size = System::Drawing::Size(102, 32);
            this->search_button->TabIndex = 7;
            this->search_button->Text = L"Найти";
            this->search_button->UseVisualStyleBackColor = true;
            this->search_button->Click += gcnew System::EventHandler(this, &MainForm::search_button_Click);
            // 
            // clients_button
            // 
            this->clients_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F));
            this->clients_button->Location = System::Drawing::Point(133, 12);
            this->clients_button->Name = L"clients_button";
            this->clients_button->Size = System::Drawing::Size(115, 34);
            this->clients_button->TabIndex = 8;
            this->clients_button->Text = L"Клиенты";
            this->clients_button->UseVisualStyleBackColor = true;
            // 
            // MainForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1334, 731);
            this->Controls->Add(this->clients_button);
            this->Controls->Add(this->search_button);
            this->Controls->Add(this->location_combo_box);
            this->Controls->Add(this->add_button);
            this->Controls->Add(this->category_combo_box);
            this->Controls->Add(this->dataGridView1);
            this->Controls->Add(this->search_text_box);
            this->Controls->Add(this->search_label);
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->Name = L"MainForm";
            this->Text = L"VetPharm";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
        void InitializeDataTable();
        void AddTestData();
        void ShowAddDialog();
        void AddRecord(String^ name, String^ category, int packaging_size, int quantity, String^ unit, Decimal price, String^ location);
        void Search(String^ searchText);
        void FilterByCategory(String^ category);
        void FilterByLocation(String^ location);
        void ApplyCombinedFilter();
        void PerformSearch();

        System::Void add_button_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void search_button_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void category_combo_box_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void location_combo_box_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
    };
}