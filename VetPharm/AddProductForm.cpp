#include "MainForm.h"
#include "AddProductForm.h"

namespace VetPharm {
    System::Void AddProductForm::exit_button_Click(System::Object^ sender, System::EventArgs^ e) {
        Close();
    }

    System::Void AddProductForm::add_button_Click(System::Object^ sender, System::EventArgs^ e) {
        if (String::IsNullOrEmpty(name_text_box->Text))
        {
            MessageBox::Show(L"Введите название товара!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Добавляем запись (ID сгенерируется автоматически)
        DataRow^ newRow = dataTable->NewRow();
        newRow[L"Название"] = name_text_box->Text;
        newRow[L"Категория"] = category_combo_box->SelectedItem->ToString();
        newRow[L"Фасовка"] = (int)packaging_size_numericUpDown->Value;
        newRow[L"Количество"] = (int)quantity_numericUpDown->Value;
        newRow[L"Единица"] = unit_combo_box->Text;
        newRow[L"Цена"] = price_numericUpDown->Value;
        newRow[L"Локация"] = location_combo_box->SelectedItem->ToString();

        dataTable->Rows->Add(newRow);
        MessageBox::Show(
            String::Format(L"Товар успешно добавлен!\nID: {0}\n", 
                newRow[L"id"]),
            L"Успешно", MessageBoxButtons::OK, MessageBoxIcon::Information);
        Close();
    }
}