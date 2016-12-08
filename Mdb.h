#ifndef MDB_H
#define MDB_H
#include <sqlite3.h>
#include <Defines.h>
#include<sstream>
#include<map>
#include<list>
#include<iostream>

class Mdb
{
public:
    Mdb();
    ~Mdb();
    std::string getCardNumber(std::string name, std::string expansion);
    std::multimap<std::string,std::string> getExpansionNumber(std::string name);
    std::multimap<std::string,std::string> getCardnameNumber(std::string expansion);
    std::list<std::string> getExpansionList();
    
private:
    sqlite3 *db;
};

#endif // MDB_H
