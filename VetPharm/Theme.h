#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Windows::Forms;

namespace VetPharm
{
    public ref class Theme abstract sealed
    {
    public:
        static initonly Color Background = Color::FromArgb(242, 248, 246);
        static initonly Color Surface = Color::White;
        static initonly Color SurfaceAlt = Color::FromArgb(231, 242, 239);
        static initonly Color Primary = Color::FromArgb(31, 122, 108);
        static initonly Color PrimaryDark = Color::FromArgb(18, 87, 76);
        static initonly Color Accent = Color::FromArgb(58, 170, 132);
        static initonly Color Danger = Color::FromArgb(192, 62, 84);
        static initonly Color TextMain = Color::FromArgb(30, 41, 45);
        static initonly Color TextMuted = Color::FromArgb(102, 118, 124);
        static initonly Color Border = Color::FromArgb(207, 223, 219);

        static Icon^ LoadApplicationIcon()
        {
            array<String^>^ candidates = gcnew array<String^>
            {
                Path::Combine(Application::StartupPath, L"free-icon-medicine-1839856.ico"),
                Path::GetFullPath(Path::Combine(Application::StartupPath, L"..\\free-icon-medicine-1839856.ico")),
                Path::GetFullPath(Path::Combine(Application::StartupPath, L"..\\..\\free-icon-medicine-1839856.ico")),
                Path::GetFullPath(Path::Combine(Application::StartupPath, L"..\\..\\VetPharm\\free-icon-medicine-1839856.ico")),
                Path::GetFullPath(Path::Combine(Application::StartupPath, L"..\\..\\..\\VetPharm\\free-icon-medicine-1839856.ico")),
                Path::GetFullPath(Path::Combine(Application::StartupPath, L"..\\..\\..\\x64\\Debug\\free-icon-medicine-1839856.ico")),
                Path::GetFullPath(Path::Combine(Application::StartupPath, L"..\\..\\..\\..\\x64\\Debug\\free-icon-medicine-1839856.ico")),
                Path::GetFullPath(Path::Combine(Application::StartupPath, L"..\\..\\..\\x64\\Release\\free-icon-medicine-1839856.ico")),
                Path::GetFullPath(Path::Combine(Application::StartupPath, L"..\\..\\..\\..\\x64\\Release\\free-icon-medicine-1839856.ico"))
            };

            for each (String ^ candidate in candidates)
            {
                if (File::Exists(candidate))
                {
                    return gcnew Icon(candidate);
                }
            }

            return nullptr;
        }

        static void ApplyForm(Form^ form, String^ title)
        {
            form->BackColor = Background;
            form->ForeColor = TextMain;
            form->Font = gcnew Drawing::Font(L"Segoe UI", 10.0f, FontStyle::Regular);
            form->Text = title;
            form->StartPosition = FormStartPosition::CenterScreen;
            Icon^ appIcon = LoadApplicationIcon();
            if (appIcon != nullptr)
            {
                form->Icon = appIcon;
            }
        }

        static void StylePrimaryButton(Button^ button)
        {
            button->FlatStyle = FlatStyle::Flat;
            button->FlatAppearance->BorderSize = 0;
            button->BackColor = Primary;
            button->ForeColor = Color::White;
            button->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.0f);
            button->Cursor = Cursors::Hand;
        }

        static void StyleSecondaryButton(Button^ button)
        {
            button->FlatStyle = FlatStyle::Flat;
            button->FlatAppearance->BorderColor = Border;
            button->FlatAppearance->BorderSize = 1;
            button->BackColor = Surface;
            button->ForeColor = TextMain;
            button->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.0f);
            button->Cursor = Cursors::Hand;
        }

        static void StyleDangerButton(Button^ button)
        {
            button->FlatStyle = FlatStyle::Flat;
            button->FlatAppearance->BorderSize = 0;
            button->BackColor = Danger;
            button->ForeColor = Color::White;
            button->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.0f);
            button->Cursor = Cursors::Hand;
        }

        static void StyleInput(Control^ control)
        {
            control->BackColor = Surface;
            control->ForeColor = TextMain;
            control->Font = gcnew Drawing::Font(L"Segoe UI", 10.0f);
        }

        static void StyleGrid(DataGridView^ grid)
        {
            grid->BackgroundColor = Surface;
            grid->BorderStyle = BorderStyle::None;
            grid->EnableHeadersVisualStyles = false;
            grid->ColumnHeadersDefaultCellStyle->BackColor = Primary;
            grid->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
            grid->ColumnHeadersDefaultCellStyle->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10.0f);
            grid->DefaultCellStyle->SelectionBackColor = Color::FromArgb(219, 239, 233);
            grid->DefaultCellStyle->SelectionForeColor = TextMain;
            grid->DefaultCellStyle->BackColor = Surface;
            grid->DefaultCellStyle->ForeColor = TextMain;
            grid->AlternatingRowsDefaultCellStyle->BackColor = SurfaceAlt;
            grid->RowHeadersVisible = false;
            grid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            grid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            grid->MultiSelect = false;
            grid->AllowUserToAddRows = false;
            grid->AllowUserToDeleteRows = false;
            grid->ReadOnly = true;
        }

        static Panel^ CreateSectionPanel(int x, int y, int width, int height)
        {
            Panel^ panel = gcnew Panel();
            panel->Location = Point(x, y);
            panel->Size = Drawing::Size(width, height);
            panel->BackColor = Surface;
            panel->BorderStyle = BorderStyle::FixedSingle;
            return panel;
        }
    };
}
