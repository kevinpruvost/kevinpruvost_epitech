/*
** EPITECH PROJECT, 2020
** Babel server sqliteDataBase
** File description:
**
*/

#include <iostream> 
#include <sqlite3.h>
#include <cstring>
#include <string> 
#include <vector>

namespace Babel {
    namespace Server {
        /**
         * \brief SQLite implementation
         */
        class sqliteDataBase {
        public:
            /**
             * \brief Used to return data from the SQLite3 callback function
             */
            struct datas {
                std::string username;
                std::string password;
                std::string uuid;
                bool error;
            };
        public:
            sqliteDataBase();
            ~sqliteDataBase();
            bool addAccount(const std::string& uuid, const std::string& username, const std::string& password);
            bool removeAccount(const std::string& username);
            void print();
            std::vector<std::string> getAccount(const std::string& username);
            //contacts
            bool addContact(const std::string& uuidUser, const std::pair<std::string, std::string>& contact);
            std::vector<std::pair<std::string, std::string>> getContacts(const std::string& uuidUser) const;
        private:
            static int getAccountCallback(void* data, int argc, char** argv, char** azColName);
            static int getContactsCallback(void* data, int argc, char** argv, char** azColName);
            sqlite3 *_db;
            bool _isOpen;
        };
    }
}