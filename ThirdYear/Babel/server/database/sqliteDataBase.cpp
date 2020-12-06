/*
** EPITECH PROJECT, 2020
** Babel server sqliteDataBase
** File description:
**
*/

#include "sqliteDataBase.hpp"

Babel::Server::sqliteDataBase::sqliteDataBase()
{
    std::string accountTable("CREATE TABLE IF NOT EXISTS ACCOUNT(uuid TEXT NOT NULL, username TEXT NOT NULL, userPassword VARCHAR(64) NOT NULL); CREATE TABLE IF NOT EXISTS CONTACTS(uuidUser TEXT NOT NULL, uuidTarget TEXT NOT NULL, usernameTarget TEXT NOT NULL);");

    if (sqlite3_open("./database.db", &_db)) {
        std::cerr << "Error open database" << std::endl;
        this->_isOpen = false;
    } else {
        sqlite3_exec(this->_db, accountTable.c_str(), NULL, 0, nullptr);
        this->_isOpen = true;
        std::cout << "Database opened successfully." << std::endl;
    }
}

Babel::Server::sqliteDataBase::~sqliteDataBase()
{
    sqlite3_close(this->_db);
    std::cout << "Closing database." << std::endl;
}

/**
 * \brief Add an account to the database
 * \param string uuid
 * \param string username
 * \param string password
 * \return boolean saying if everything went right
 */
bool Babel::Server::sqliteDataBase::addAccount(const std::string& uuid, const std::string& username, const std::string& password)
{
    if (!this->_isOpen)
        return false;
    std::string add("INSERT INTO ACCOUNT (uuid, username, userPassword) VALUES ('" + uuid + "', '" + username + "', '" + password + "');");

    if (sqlite3_exec(this->_db, add.c_str(), NULL, 0, nullptr)) {
        std::cerr << "request addAccount error" << std::endl;
        return false;
    }
    return true;
}

/**
 * \brief Add user to the contact list
 * \param string uuidUser
 * \param A pair containing the uui&username of the contact
 * \return Boolean saying if everything went right
 */
bool Babel::Server::sqliteDataBase::addContact(const std::string& uuidUser, const std::pair<std::string, std::string>& contact)
{
    if (!this->_isOpen)
        return (false);
    std::string query("INSERT INTO CONTACTS (uuidUser, uuidTarget, usernameTarget) VALUES ('" + uuidUser + "', '" + contact.first + "', '" + contact.second + "');");

    if (sqlite3_exec(this->_db, query.c_str(), NULL, 0, nullptr) != SQLITE_OK) {
        std::cerr << "sqliteDataBase Error: addAccount query failed" << std::endl;
        return (false);
    }
    return (true);
}

int Babel::Server::sqliteDataBase::getContactsCallback(void* data, int argc, char** argv, char** azColName)
{
    std::vector<std::pair<std::string, std::string>>* list = reinterpret_cast<std::vector<std::pair<std::string, std::string>>*>(data);

    if (argc < 2)
        return 1;
    list->push_back(std::make_pair(std::string(argv[0]), std::string(argv[1])));
    return 0;
}

/**
 * \brief Returns the user's contacts
 * \param string uuidUser
 * \return A vector of pair of string containing all the uuid&usernames of the contacts
 */
std::vector<std::pair<std::string, std::string>> Babel::Server::sqliteDataBase::getContacts(const std::string& uuidUser) const
{
    if (!this->_isOpen)
        return {};
    std::vector<std::pair<std::string, std::string>> data;
    char* errorMessage;
    std::string query("SELECT uuidTarget, usernameTarget FROM CONTACTS WHERE uuidUser = '" + uuidUser + "';");

    if (sqlite3_exec(this->_db, query.c_str(), getContactsCallback, &data, &errorMessage) != SQLITE_OK) {
        std::cerr << "sqliteDataBase Error: getContacts query error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return {};
    }
    return { data };
}

/**
 * \brief Remove user from the database
 * \param string username
 * \return Boolean saying if everything went right
 */
bool Babel::Server::sqliteDataBase::removeAccount(const std::string& username)
{
    if (!this->_isOpen)
        return false;
    std::string del("DELETE FROM ACCOUNT WHERE username = '" + username + "';");

    if (sqlite3_exec(this->_db, del.c_str(), NULL, 0, nullptr)) {
        std::cerr << "request removeAccount error" << std::endl;
        return false;
    }
    return true;
}

static int printCallback(void* data, int argc, char** argv, char** azColName) {
    for (size_t i = 0; i < argc; i++)
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
    printf("\n"); 
    return 0;
}

/**
 * \brief Print the database
 */
void Babel::Server::sqliteDataBase::print()
{
    if (!this->_isOpen)
        return;
    std::string disp("SELECT * FROM ACCOUNT;");
    sqlite3_exec(this->_db, disp.c_str(), printCallback, NULL, NULL);
}

int Babel::Server::sqliteDataBase::getAccountCallback(void* data, int argc, char** argv, char** azColName)
{
    datas *dataPointer = (datas*)data;

    if (argc <= 0) {
        dataPointer->error = true;
        return 1;
    }
    dataPointer->uuid = std::string(argv[0]);
    dataPointer->username = std::string(argv[1]);
    dataPointer->password = std::string(argv[2]);
    dataPointer->error = false;
    return 0;
}

/**
 * \brief Get account matching the given username from the database
 * \param string username
 * \return Vector of string containing user's info
 */
std::vector<std::string> Babel::Server::sqliteDataBase::getAccount(const std::string& username)
{
    if (!this->_isOpen)
        return {};
    datas data;
    char* errorMessage;
    std::string account("SELECT * FROM ACCOUNT WHERE username = '" + username + "';");

    if (sqlite3_exec(this->_db, account.c_str(), getAccountCallback, (void*)(&data), &errorMessage) != SQLITE_OK) {
        std::cerr << "request getAccount error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return {};
    }
    if (data.error)
        return {};
    return {data.uuid, data.username, data.password};
}

