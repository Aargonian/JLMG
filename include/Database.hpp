/*
 * Created by Aaron Gorodetzky on 1/12/20.
 */

#ifndef JLMG_DATABASE_HPP
#define JLMG_DATABASE_HPP

#include <sqlite3.h>

class WordDatabase
{
public:
    WordDatabase(std::string path, bool create);
    WordDatabase(WordDatabase &copy) = delete;
    WordDatabase(WordDatabase &&move) = delete;
    virtual ~WordDatabase();

    WordDatabase& operator=(WordDatabase &copy) = delete;
    WordDatabase& operator=(WordDatabase &&move) = delete;

protected:
    void _create_tables();
    void _setup_version_table();

private:
    std::string db_path;
    sqlite3 *db;

    static const char _CREATE_TABLE_STATEMENTS[];
    static const std::string __WORD_TABLE_NAME;
    static const std::string __CREATE_WORD_TABLE_STMT;
    static const std::string __VERSION_TABLE_NAME;
    static const std::string __CREATE_VERSION_INFO_STMT;
    static const std::string __VERSION_INSERT_STMT;
};

#endif //JLMG_DATABASE_HPP
