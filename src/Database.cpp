/*
 * Created by Aaron Gorodetzky on 1/12/20.
 */
#include <iostream>

#include <Database.hpp>
#include <utility>

const std::string WordDatabase::__WORD_TABLE_NAME = "words";
const std::string WordDatabase::__CREATE_WORD_TABLE_STMT =
        "CREATE TABLE IF NOT EXISTS words"
        "("
        "    id integer PRIMARY KEY"
        "    english text NOT NULL"
        "    romaji text NOT NULL"
        "    kanji text NOT NULL"
        "    chapter integer NOT NULL"
        "    grammar_types text NOT NULL"
        "    note text"
        "    user_added integer NOT NULL"
        ");";

const std::string WordDatabase::__VERSION_TABLE_NAME = "version_info";
const std::string WordDatabase::__CREATE_VERSION_INFO_STMT =
        "CREATE TABLE IF NOT EXISTS version_info"
        "("
        "    id integer PRIMARY KEY"
        "    version_major integer NOT NULL"
        "    version_minor integer NOT NULL"
        "    version_patch integer NOT NULL"
        ")";

const std::string WordDatabase::__VERSION_INSERT_STMT =
        "INSERT INTO version_info(version_major, version_minor, version_patch)"
        "VALUES (0, 1, 0);";

WordDatabase::WordDatabase(std::string path, bool create)
{
    this->db = nullptr;
    this->db_path = std::move(path);

    int rc = 0;
    if(create)
    {
        rc = sqlite3_open(this->db_path.c_str(), &this->db);
        try
        {
            this->_create_tables();
            this->_setup_version_table();
        }
        catch(std::runtime_error &error)
        {
            sqlite3_close(this->db);
            this->db = nullptr;
            throw error;
        }
    }
    else
    {
        rc = sqlite3_open_v2(this->db_path.c_str(), &this->db,
                             SQLITE_OPEN_READWRITE, nullptr);
    }

    if(rc)
    {
        std::cerr << "There was an error opening the Database: "
                  << sqlite3_errmsg(this->db) << std::endl;
        sqlite3_close(this->db);
        this->db = nullptr;
        throw std::runtime_error("Unable to open database.");
    }
}

WordDatabase::~WordDatabase()
{
    if(this->db)
    {
        sqlite3_close(this->db);
        this->db = nullptr;
    }
}

void WordDatabase::_create_tables()
{
    char *errorMsg = nullptr;
    if(this->db)
    {
        /* Create the Words table */
        int rc = sqlite3_exec(this->db, this->__CREATE_WORD_TABLE_STMT.c_str(),
                              nullptr, nullptr, &errorMsg);
        if(rc || errorMsg)
        {
            std::cerr << "There was an error creating the words table."
                      << std::endl;
            std::cerr << "Error Message: " << errorMsg << std::endl;
            if(errorMsg)
            {
                sqlite3_free(errorMsg);
                errorMsg = nullptr;
            }
            throw std::runtime_error("Unable to create tables");
        }

        /* Create the Version table */
        rc = sqlite3_exec(this->db, this->__CREATE_WORD_TABLE_STMT.c_str(),
                          nullptr, nullptr, &errorMsg);
        if(rc || errorMsg)
        {
            std::cerr << "There was an error creating the version table."
                      << std::endl;
            std::cerr << "Error Message: " << errorMsg << std::endl;
            if(errorMsg)
            {
                sqlite3_free(errorMsg);
                errorMsg = nullptr;
            }
            throw std::runtime_error("Unable to create tables");
        }
    }
    else
    {
        throw std::runtime_error("Can't create tables with no DB!");
    }
}

void WordDatabase::_setup_version_table()
{
    if(this->db)
    {
        char *errorMsg = nullptr;
        int rc = sqlite3_exec(this->db,
                              this->__VERSION_INSERT_STMT.c_str(), nullptr,
                              nullptr, &errorMsg);
        if(rc || errorMsg)
        {
            std::cerr << "There was an error creating the version table."
                      << std::endl;
            std::cerr << "Error Message: " << errorMsg << std::endl;
            if(errorMsg)
            {
                sqlite3_free(errorMsg);
                errorMsg = nullptr;
            }
            throw std::runtime_error("Unable to create tables");
        }
    }
    else
    {
        throw std::runtime_error("Can't create version info with no DB!");
    }
}