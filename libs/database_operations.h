#include <stdlib.h>
#include "database_types.h"

Table csvToTable(char* pathToFile);
Database commandToDatabase(char* command);
int countRowsInCsv(char* pathToFile);
void selectFromTable();
void createTable(Table table);
void createDatabase(Database db);
void deleteFromTable();
void alterTableModify();
void alterTableDrop();
void insertIntoTable();
void selectFromTable();
