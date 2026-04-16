#pragma once

#include <sqlite3.h>
#include <string>
#include <cstring>
#include <vcclr.h>

using namespace System;
using namespace System::Data;
using namespace System::IO;
using namespace System::Text;

namespace VetPharm
{
    namespace DbHelpers
    {
        inline std::string ToUtf8String(String^ value)
        {
            if (value == nullptr)
            {
                return std::string();
            }

            array<Byte>^ bytes = Encoding::UTF8->GetBytes(value);
            std::string result(bytes->Length, '\0');
            if (bytes->Length > 0)
            {
                pin_ptr<Byte> pinnedBytes = &bytes[0];
                memcpy(&result[0], pinnedBytes, bytes->Length);
            }

            return result;
        }

        inline String^ FromUtf8(const unsigned char* value, int length)
        {
            if (value == nullptr)
            {
                return String::Empty;
            }

            return gcnew String(reinterpret_cast<const char*>(value), 0, length, Encoding::UTF8);
        }

        inline String^ FromUtf8Column(sqlite3_stmt* stmt, int index)
        {
            return FromUtf8(sqlite3_column_text(stmt, index), sqlite3_column_bytes(stmt, index));
        }

        inline String^ ResolveDatabasePath()
        {
            array<String^>^ candidates = gcnew array<String^>
            {
                Path::Combine(System::Windows::Forms::Application::StartupPath, L"VetPharmDB.db"),
                Path::GetFullPath(Path::Combine(System::Windows::Forms::Application::StartupPath, L"..\\..\\VetPharm\\VetPharmDB.db")),
                Path::GetFullPath(Path::Combine(System::Windows::Forms::Application::StartupPath, L"..\\..\\..\\VetPharm\\VetPharmDB.db")),
                Path::GetFullPath(Path::Combine(System::Windows::Forms::Application::StartupPath, L"..\\..\\..\\..\\VetPharm\\VetPharmDB.db"))
            };

            for each (String ^ candidate in candidates)
            {
                if (File::Exists(candidate))
                {
                    return candidate;
                }
            }

            return Path::Combine(System::Windows::Forms::Application::StartupPath, L"VetPharmDB.db");
        }

        inline String^ EscapeRowFilterValue(String^ value)
        {
            if (String::IsNullOrEmpty(value))
            {
                return String::Empty;
            }

            return value->Replace(L"'", L"''")->Replace(L"[", L"[[]")->Replace(L"%", L"[%]")->Replace(L"*", L"[*]");
        }

        inline sqlite3* OpenDatabase(String^ databasePath)
        {
            sqlite3* db = nullptr;
            if (sqlite3_open(ToUtf8String(databasePath).c_str(), &db) != SQLITE_OK)
            {
                if (db != nullptr)
                {
                    sqlite3_close(db);
                }
                return nullptr;
            }

            sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);
            return db;
        }

        inline bool ExecuteNonQuery(String^ databasePath, const char* sql)
        {
            sqlite3* db = OpenDatabase(databasePath);
            if (db == nullptr)
            {
                return false;
            }

            char* errMsg = nullptr;
            const int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
            if (errMsg != nullptr)
            {
                sqlite3_free(errMsg);
            }
            sqlite3_close(db);
            return rc == SQLITE_OK;
        }

        inline bool TableHasColumn(String^ databasePath, String^ tableName, String^ columnName)
        {
            sqlite3* db = OpenDatabase(databasePath);
            if (db == nullptr)
            {
                return false;
            }

            const std::string sql = "PRAGMA table_info(" + ToUtf8String(tableName) + ")";
            sqlite3_stmt* stmt = nullptr;
            bool hasColumn = false;

            if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
            {
                while (sqlite3_step(stmt) == SQLITE_ROW)
                {
                    String^ currentColumn = FromUtf8Column(stmt, 1);
                    if (String::Equals(currentColumn, columnName, StringComparison::OrdinalIgnoreCase))
                    {
                        hasColumn = true;
                        break;
                    }
                }
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return hasColumn;
        }

        inline bool EnsurePasswordConfig(String^ databasePath)
        {
            const char* createSql =
                "CREATE TABLE IF NOT EXISTS AppConfig ("
                "key TEXT PRIMARY KEY,"
                "value TEXT NOT NULL"
                ");"
                "INSERT OR IGNORE INTO AppConfig(key, value) VALUES('app_password', 'vetpharm');";
            return ExecuteNonQuery(databasePath, createSql);
        }

        inline String^ LoadAppPassword(String^ databasePath)
        {
            sqlite3* db = OpenDatabase(databasePath);
            if (db == nullptr)
            {
                return L"vetpharm";
            }

            const char* sql = "SELECT value FROM AppConfig WHERE key = 'app_password' LIMIT 1";
            sqlite3_stmt* stmt = nullptr;
            String^ password = L"vetpharm";

            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK && sqlite3_step(stmt) == SQLITE_ROW)
            {
                password = FromUtf8Column(stmt, 0);
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return password;
        }

        inline bool ValidateUserCredentials(String^ databasePath, String^ username, String^ password)
        {
            sqlite3* db = OpenDatabase(databasePath);
            if (db == nullptr)
            {
                return false;
            }

            const char* sql = "SELECT 1 FROM Users WHERE username = ? AND password = ? LIMIT 1";
            sqlite3_stmt* stmt = nullptr;
            bool isValid = false;

            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
            {
                std::string userUtf8 = ToUtf8String(username == nullptr ? String::Empty : username->Trim());
                std::string passUtf8 = ToUtf8String(password == nullptr ? String::Empty : password);
                sqlite3_bind_text(stmt, 1, userUtf8.c_str(), static_cast<int>(userUtf8.size()), SQLITE_TRANSIENT);
                sqlite3_bind_text(stmt, 2, passUtf8.c_str(), static_cast<int>(passUtf8.size()), SQLITE_TRANSIENT);
                isValid = sqlite3_step(stmt) == SQLITE_ROW;
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return isValid;
        }

        inline DataTable^ LoadLookupTable(String^ databasePath, String^ tableName)
        {
            DataTable^ table = gcnew DataTable(tableName);
            table->Columns->Add(L"id", Int32::typeid);
            table->Columns->Add(L"name", String::typeid);

            sqlite3* db = OpenDatabase(databasePath);
            if (db == nullptr)
            {
                return table;
            }

            std::string sql = "SELECT id, name FROM " + ToUtf8String(tableName) + " ORDER BY name";
            sqlite3_stmt* stmt = nullptr;

            if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
            {
                while (sqlite3_step(stmt) == SQLITE_ROW)
                {
                    DataRow^ row = table->NewRow();
                    row[L"id"] = sqlite3_column_int(stmt, 0);
                    row[L"name"] = FromUtf8Column(stmt, 1);
                    table->Rows->Add(row);
                }
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return table;
        }

        inline int EnsureOwner(String^ databasePath, String^ fullName, String^ phone)
        {
            sqlite3* db = OpenDatabase(databasePath);
            if (db == nullptr)
            {
                return 0;
            }

            const std::string ownerName = ToUtf8String(fullName->Trim());
            const std::string ownerPhone = ToUtf8String(phone == nullptr ? String::Empty : phone->Trim());

            const char* selectSql = "SELECT id FROM Owners WHERE full_name = ? LIMIT 1";
            sqlite3_stmt* selectStmt = nullptr;
            int ownerId = 0;

            if (sqlite3_prepare_v2(db, selectSql, -1, &selectStmt, nullptr) == SQLITE_OK)
            {
                sqlite3_bind_text(selectStmt, 1, ownerName.c_str(), static_cast<int>(ownerName.size()), SQLITE_TRANSIENT);
                if (sqlite3_step(selectStmt) == SQLITE_ROW)
                {
                    ownerId = sqlite3_column_int(selectStmt, 0);
                }
            }
            sqlite3_finalize(selectStmt);

            if (ownerId == 0)
            {
                const char* insertSql = "INSERT INTO Owners(full_name, phone) VALUES(?, ?)";
                sqlite3_stmt* insertStmt = nullptr;
                if (sqlite3_prepare_v2(db, insertSql, -1, &insertStmt, nullptr) == SQLITE_OK)
                {
                    sqlite3_bind_text(insertStmt, 1, ownerName.c_str(), static_cast<int>(ownerName.size()), SQLITE_TRANSIENT);
                    sqlite3_bind_text(insertStmt, 2, ownerPhone.c_str(), static_cast<int>(ownerPhone.size()), SQLITE_TRANSIENT);
                    if (sqlite3_step(insertStmt) == SQLITE_DONE)
                    {
                        ownerId = static_cast<int>(sqlite3_last_insert_rowid(db));
                    }
                }
                sqlite3_finalize(insertStmt);
            }
            else
            {
                const char* updateSql = "UPDATE Owners SET phone = ? WHERE id = ?";
                sqlite3_stmt* updateStmt = nullptr;
                if (sqlite3_prepare_v2(db, updateSql, -1, &updateStmt, nullptr) == SQLITE_OK)
                {
                    sqlite3_bind_text(updateStmt, 1, ownerPhone.c_str(), static_cast<int>(ownerPhone.size()), SQLITE_TRANSIENT);
                    sqlite3_bind_int(updateStmt, 2, ownerId);
                    sqlite3_step(updateStmt);
                }
                sqlite3_finalize(updateStmt);
            }

            sqlite3_close(db);
            return ownerId;
        }

        inline String^ ToLowerInvariant(String^ value)
        {
            return value == nullptr ? String::Empty : value->ToLowerInvariant();
        }
    }
}
