#pragma once

namespace VetPharm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for AddProductForm
	/// </summary>
	public ref class AddProductForm : public System::Windows::Forms::Form
	{
	private:
		DataTable^ dataTable;
	public:
		AddProductForm(System::Data::DataTable^ dt)
		{
			this->dataTable = dt;
			InitializeComponent();
			this->category_combo_box->Items->AddRange(gcnew cli::array<System::Object^> {
				L"Антибиотики",
				L"Корма",
				L"Мазь",
				L"Витамины",
				L"Антигельминтики",
				L"Противовоспалительные",
				L"Пробиотики"
			});
			this->category_combo_box->SelectedIndex = 0;

			this->unit_combo_box->Items->AddRange(gcnew cli::array<System::Object^> {
				L"миллилитры",
				L"граммы",
				L"таблетки",
				L"штуки",
			});
			this->unit_combo_box->SelectedIndex = 0;

			this->location_combo_box->Items->Clear();
			this->location_combo_box->Items->AddRange(gcnew cli::array<System::Object^> {
				L"Стенд 1",
				L"Стенд 2",
				L"Стенд 3",
				L"Стенд 4",
				L"Склад"
			});
			this->location_combo_box->SelectedIndex = 0;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AddProductForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ name_label;
	protected:
	private: System::Windows::Forms::TextBox^ name_text_box;
	private: System::Windows::Forms::Label^ category_label;
	private: System::Windows::Forms::ComboBox^ category_combo_box;
	private: System::Windows::Forms::Label^ quantity_label;
	private: System::Windows::Forms::NumericUpDown^ quantity_numericUpDown;








	private: System::Windows::Forms::Label^ unit_label;
	private: System::Windows::Forms::ComboBox^ location_combo_box;


	private: System::Windows::Forms::Label^ location_label;
	private: System::Windows::Forms::Button^ add_button;
	private: System::Windows::Forms::Button^ exit_button;
	private: System::Windows::Forms::Label^ add_product_label;
	private: System::Windows::Forms::ComboBox^ unit_combo_box;
	private: System::Windows::Forms::NumericUpDown^ packaging_size_numericUpDown;

	private: System::Windows::Forms::Label^ packaging_size_label;
	private: System::Windows::Forms::NumericUpDown^ price_numericUpDown;
	private: System::Windows::Forms::Label^ price_label;






	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->name_label = (gcnew System::Windows::Forms::Label());
			this->name_text_box = (gcnew System::Windows::Forms::TextBox());
			this->category_label = (gcnew System::Windows::Forms::Label());
			this->category_combo_box = (gcnew System::Windows::Forms::ComboBox());
			this->quantity_label = (gcnew System::Windows::Forms::Label());
			this->quantity_numericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->unit_label = (gcnew System::Windows::Forms::Label());
			this->location_combo_box = (gcnew System::Windows::Forms::ComboBox());
			this->location_label = (gcnew System::Windows::Forms::Label());
			this->add_button = (gcnew System::Windows::Forms::Button());
			this->exit_button = (gcnew System::Windows::Forms::Button());
			this->add_product_label = (gcnew System::Windows::Forms::Label());
			this->unit_combo_box = (gcnew System::Windows::Forms::ComboBox());
			this->packaging_size_numericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->packaging_size_label = (gcnew System::Windows::Forms::Label());
			this->price_numericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->price_label = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->quantity_numericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->packaging_size_numericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->price_numericUpDown))->BeginInit();
			this->SuspendLayout();
			// 
			// name_label
			// 
			this->name_label->AutoSize = true;
			this->name_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->name_label->Location = System::Drawing::Point(66, 88);
			this->name_label->Name = L"name_label";
			this->name_label->Size = System::Drawing::Size(99, 25);
			this->name_label->TabIndex = 0;
			this->name_label->Text = L"Название";
			// 
			// name_text_box
			// 
			this->name_text_box->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->name_text_box->Location = System::Drawing::Point(222, 85);
			this->name_text_box->Name = L"name_text_box";
			this->name_text_box->Size = System::Drawing::Size(277, 30);
			this->name_text_box->TabIndex = 1;
			// 
			// category_label
			// 
			this->category_label->AutoSize = true;
			this->category_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->category_label->Location = System::Drawing::Point(66, 140);
			this->category_label->Name = L"category_label";
			this->category_label->Size = System::Drawing::Size(109, 25);
			this->category_label->TabIndex = 2;
			this->category_label->Text = L"Категория";
			// 
			// category_combo_box
			// 
			this->category_combo_box->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->category_combo_box->FormattingEnabled = true;
			this->category_combo_box->Location = System::Drawing::Point(222, 137);
			this->category_combo_box->Name = L"category_combo_box";
			this->category_combo_box->Size = System::Drawing::Size(277, 33);
			this->category_combo_box->TabIndex = 3;
			// 
			// quantity_label
			// 
			this->quantity_label->AutoSize = true;
			this->quantity_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->quantity_label->Location = System::Drawing::Point(66, 195);
			this->quantity_label->Name = L"quantity_label";
			this->quantity_label->Size = System::Drawing::Size(123, 25);
			this->quantity_label->TabIndex = 4;
			this->quantity_label->Text = L"Количество";
			// 
			// quantity_numericUpDown
			// 
			this->quantity_numericUpDown->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->quantity_numericUpDown->Location = System::Drawing::Point(222, 193);
			this->quantity_numericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1874919424, 2328306, 0, 0 });
			this->quantity_numericUpDown->Name = L"quantity_numericUpDown";
			this->quantity_numericUpDown->Size = System::Drawing::Size(277, 30);
			this->quantity_numericUpDown->TabIndex = 5;
			// 
			// unit_label
			// 
			this->unit_label->AutoSize = true;
			this->unit_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->unit_label->Location = System::Drawing::Point(66, 248);
			this->unit_label->Name = L"unit_label";
			this->unit_label->Size = System::Drawing::Size(92, 25);
			this->unit_label->TabIndex = 6;
			this->unit_label->Text = L"Единица";
			// 
			// location_combo_box
			// 
			this->location_combo_box->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->location_combo_box->FormattingEnabled = true;
			this->location_combo_box->Location = System::Drawing::Point(222, 298);
			this->location_combo_box->Name = L"location_combo_box";
			this->location_combo_box->Size = System::Drawing::Size(277, 33);
			this->location_combo_box->TabIndex = 9;
			// 
			// location_label
			// 
			this->location_label->AutoSize = true;
			this->location_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->location_label->Location = System::Drawing::Point(66, 301);
			this->location_label->Name = L"location_label";
			this->location_label->Size = System::Drawing::Size(92, 25);
			this->location_label->TabIndex = 8;
			this->location_label->Text = L"Локация";
			// 
			// add_button
			// 
			this->add_button->BackColor = System::Drawing::Color::Lime;
			this->add_button->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->add_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->add_button->ForeColor = System::Drawing::Color::Black;
			this->add_button->Location = System::Drawing::Point(117, 459);
			this->add_button->Name = L"add_button";
			this->add_button->Size = System::Drawing::Size(137, 62);
			this->add_button->TabIndex = 10;
			this->add_button->Text = L"Добавить";
			this->add_button->UseVisualStyleBackColor = false;
			this->add_button->Click += gcnew System::EventHandler(this, &AddProductForm::add_button_Click);
			// 
			// exit_button
			// 
			this->exit_button->BackColor = System::Drawing::Color::Red;
			this->exit_button->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->exit_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->exit_button->ForeColor = System::Drawing::SystemColors::ControlText;
			this->exit_button->Location = System::Drawing::Point(334, 459);
			this->exit_button->Name = L"exit_button";
			this->exit_button->Size = System::Drawing::Size(137, 62);
			this->exit_button->TabIndex = 11;
			this->exit_button->Text = L"Отмена";
			this->exit_button->UseVisualStyleBackColor = false;
			this->exit_button->Click += gcnew System::EventHandler(this, &AddProductForm::exit_button_Click);
			// 
			// add_product_label
			// 
			this->add_product_label->AutoSize = true;
			this->add_product_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->add_product_label->Location = System::Drawing::Point(166, 9);
			this->add_product_label->Name = L"add_product_label";
			this->add_product_label->Size = System::Drawing::Size(240, 29);
			this->add_product_label->TabIndex = 12;
			this->add_product_label->Text = L"Добавление товара";
			// 
			// unit_combo_box
			// 
			this->unit_combo_box->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->unit_combo_box->FormattingEnabled = true;
			this->unit_combo_box->Location = System::Drawing::Point(222, 245);
			this->unit_combo_box->Name = L"unit_combo_box";
			this->unit_combo_box->Size = System::Drawing::Size(277, 33);
			this->unit_combo_box->TabIndex = 13;
			// 
			// packaging_size_numericUpDown
			// 
			this->packaging_size_numericUpDown->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->packaging_size_numericUpDown->Location = System::Drawing::Point(222, 351);
			this->packaging_size_numericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {
				-1530494976, 232830,
					0, 0
			});
			this->packaging_size_numericUpDown->Name = L"packaging_size_numericUpDown";
			this->packaging_size_numericUpDown->Size = System::Drawing::Size(277, 30);
			this->packaging_size_numericUpDown->TabIndex = 15;
			// 
			// packaging_size_label
			// 
			this->packaging_size_label->AutoSize = true;
			this->packaging_size_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->packaging_size_label->Location = System::Drawing::Point(66, 353);
			this->packaging_size_label->Name = L"packaging_size_label";
			this->packaging_size_label->Size = System::Drawing::Size(92, 25);
			this->packaging_size_label->TabIndex = 14;
			this->packaging_size_label->Text = L"Фасовка";
			// 
			// price_numericUpDown
			// 
			this->price_numericUpDown->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->price_numericUpDown->Location = System::Drawing::Point(222, 401);
			this->price_numericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { -1981284352, -1966660860, 0, 0 });
			this->price_numericUpDown->Name = L"price_numericUpDown";
			this->price_numericUpDown->Size = System::Drawing::Size(277, 30);
			this->price_numericUpDown->TabIndex = 17;
			// 
			// price_label
			// 
			this->price_label->AutoSize = true;
			this->price_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->price_label->Location = System::Drawing::Point(66, 403);
			this->price_label->Name = L"price_label";
			this->price_label->Size = System::Drawing::Size(58, 25);
			this->price_label->TabIndex = 16;
			this->price_label->Text = L"Цена";
			// 
			// AddProductForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(566, 591);
			this->Controls->Add(this->price_numericUpDown);
			this->Controls->Add(this->price_label);
			this->Controls->Add(this->packaging_size_numericUpDown);
			this->Controls->Add(this->packaging_size_label);
			this->Controls->Add(this->unit_combo_box);
			this->Controls->Add(this->add_product_label);
			this->Controls->Add(this->exit_button);
			this->Controls->Add(this->add_button);
			this->Controls->Add(this->location_combo_box);
			this->Controls->Add(this->location_label);
			this->Controls->Add(this->unit_label);
			this->Controls->Add(this->quantity_numericUpDown);
			this->Controls->Add(this->quantity_label);
			this->Controls->Add(this->category_combo_box);
			this->Controls->Add(this->category_label);
			this->Controls->Add(this->name_text_box);
			this->Controls->Add(this->name_label);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"AddProductForm";
			this->Text = L"Добавление товара";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->quantity_numericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->packaging_size_numericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->price_numericUpDown))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	private: System::Void exit_button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void add_button_Click(System::Object^ sender, System::EventArgs^ e);
};
}
