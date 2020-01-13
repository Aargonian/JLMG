#include <iostream>
#include <sqlite3.h>

int main()
{
    sqlite3 *db;
    char *errMsg = 0;
    int code;

    code = sqlite3_open_v2("wordbank.db", &db, SQLITE_OPEN_READWRITE, NULL);

    if(code)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return code;
    }
    else
    {
        fprintf(stdout, "Opened database successfully!\n");
    }
    sqlite3_close(db);
    return 0;
}
