#include "SqliteDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

int SqliteDatabase::open()
{
    _DB = nullptr;
    char* zErrMsg = 0;
    int rc;
    char* sql;
    bool fileExist;

    fileExist = isFile("users.db");
    if (fileExist)
    {
        rc = sqlite3_open("users.db", &_DB);
        if (rc)
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(_DB));
            return rc;
        }
        else
        {
            fprintf(stdout, "Opened database successfully\n");
        }
    }
    else
    {
        rc = sqlite3_open("users.db", &_DB);
        if (rc)
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(_DB));
            return rc;
        }
        /* Create SQL statement */
        sql = "CREATE TABLE USERS("  \
            "NAME TEXT PRIMARY KEY NOT NULL," \
            "PASSWORD INT NOT NULL," \
            "MAIL CHAR(50) NOT NULL);";

        /* Execute SQL statement */
        rc = sqlite3_exec(_DB, sql, nullptr, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return rc;
        }
        else
        {
            fprintf(stdout, "Table created successfully\n");
        }
    }
    return SQLITE_OK;
}


void SqliteDatabase::close()
{
    if (_DB) 
    {
        sqlite3_close(_DB);
        _DB = nullptr;
    }
}

bool SqliteDatabase::doesUserExist(std::string& username)
{
    std::string sql = "SELECT COUNT(*) FROM USERS WHERE NAME = ";
    sql += "'";
    sql += username;
    sql += "'";
    sqlite3_stmt* stmt;
    int rc;

    rc = sqlite3_prepare_v2(_DB, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(_DB) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0); 
        sqlite3_finalize(stmt); 
        return count > 0; 
    }
    sqlite3_finalize(stmt);
    return false; 
}

bool SqliteDatabase::doesPasswordMatch(std::string& username, std::string& password)
{

    std::string sql = "SELECT COUNT(*) FROM USERS WHERE NAME = '";
    sql += username + "'" + "AND PASSWORD = '";
    sql += password + "';";
    sqlite3_stmt* stmt;

        int rc = sqlite3_prepare_v2(_DB, sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(_DB) << std::endl;
            return false;
        }

        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW)
        {
            int count = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            return count > 0;
        }
        sqlite3_finalize(stmt);
        return false;
}

int SqliteDatabase::addNewUser(std::string& username, std::string& password, std::string mail)
{
    sqlite3_stmt* stmt;
    if (!doesUserExist(username))
    {
        std::cout << "User already Exist";
        return 0;
    }
    else
    {
        std::string sql = "INSERT INTO USERS (NAME,PASSWORD,MAIL) " \
        "VALUES ('" + username + "'," + "'" + password + "'," + mail + "'" + ")";
        sqlite3_prepare(_DB, sql.c_str(), -1, &stmt, NULL);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        return 1;
    }
        
}

//int SqliteDatabase::callback(void* NotUsed, int argc, char** argv, char** azColName)
//{
//    int i;
//    for (i = 0; i < argc; i++) {
//        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//    }
//    printf("\n");
//    return 0;
//}

bool SqliteDatabase::isFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    return file.good();
}   