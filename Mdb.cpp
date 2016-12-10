#include "Mdb.h"

// Constructor
Mdb::Mdb()
{
	if (sqlite3_open(DATABASEDIRECTORY,&(this->db)) != SQLITE_OK)
		std::cerr << "ERROR: Database '" << DATABASEDIRECTORY << "' could not be opened!\n";
}

// Destructor
Mdb::~Mdb()
{
    sqlite3_close(this->db);
}

std::string Mdb::getCardNumber(std::string name, std::string expansion)
{
    std::string number;
    sqlite3_stmt *stmt;
    std::stringstream ss;
    
    ss << "SELECT Number FROM CARDS WHERE Name = \"" << name << "\" AND Expansion = \"" << expansion <<"\"";
    const std::string& tmp = ss.str();
    sqlite3_prepare_v2(db,tmp.c_str(), -1, &stmt, 0);
    sqlite3_step(stmt);
    number = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt,0)));
    sqlite3_finalize(stmt);
    return number;
}
std::multimap<std::string,std::string> Mdb::getExpansionNumber(std::string name)
{
    std::multimap<std::string,std::string> mmap;
    sqlite3_stmt *stmt;
    std::stringstream ss;
    
    ss << "SELECT Expansion,Number FROM CARDS WHERE Name = \"" << name << "\"";
    const std::string& tmp = ss.str();
    sqlite3_prepare_v2(db,tmp.c_str(), -1, &stmt, 0);
    
    while (sqlite3_step(stmt) == SQLITE_ROW) mmap.insert(std::pair<std::string,std::string>(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt,0))),
                                                                                            std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt,1)))));
    
    sqlite3_finalize(stmt);
    return mmap;
}
std::multimap<std::string,std::string> Mdb::getCardnameNumber(std::string expansion)
{
    std::multimap<std::string,std::string> mmap;
    sqlite3_stmt *stmt;
    std::stringstream ss;
    
    ss << "SELECT Name,Number FROM CARDS WHERE Expansion = \"" << expansion << "\"";
    const std::string& tmp = ss.str();
    sqlite3_prepare_v2(db,tmp.c_str(), -1, &stmt, 0);
    
    while (sqlite3_step(stmt) == SQLITE_ROW) mmap.insert(std::pair<std::string,std::string>(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt,0))),
                                                                                            std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt,1)))));
    sqlite3_finalize(stmt);
    return mmap;    
}
std::list<std::string> Mdb::getExpansionList()
{
    std::list<std::string> expList;
    sqlite3_stmt *stmt;
    
    sqlite3_prepare_v2(db,"SELECT DISTINCT Expansion FROM CARDS", -1, &stmt, 0);
    while (sqlite3_step(stmt) == SQLITE_ROW) expList.push_back(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt,0))));
    
    sqlite3_finalize(stmt);
    return expList;
}
