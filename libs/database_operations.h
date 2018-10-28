#include <stdlib.h>
#include "database_types.h"

Database commandToDatabase(char* command);
int countRowsInCsv(char* pathToFile);
void selectFromTable();
void createTable();
void createDatabase(Database db);
void deleteFromTable();
void alterTableModify();
void alterTableDrop();
void insertIntoTable();
void selectFromTable();
