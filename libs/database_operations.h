#include <stdlib.h>
#include "database_types.h"

/*
*   Recebe um caminho para um arquivo .csv depois
*    retorna um struct do tipo Table
*
*   Recebe
*   @string
*/
Table csvToTable(char* pathToFile);
/*
*   | INSERIR COMENTÁRIO AQUI | INSERIR COMENTÁRIO AQUI | INSERIR COMENTÁRIO AQUI |
*/
Database commandToDatabase(char* command);
/*
*   | INSERIR COMENTÁRIO AQUI | INSERIR COMENTÁRIO AQUI | INSERIR COMENTÁRIO AQUI |
*/
int countRowsInCsv(char* pathToFile);
void selectFromTable();
/*
*   | INSERIR COMENTÁRIO AQUI | INSERIR COMENTÁRIO AQUI | INSERIR COMENTÁRIO AQUI |
*/
void createTable(Table table);
/*
*   | INSERIR COMENTÁRIO AQUI | INSERIR COMENTÁRIO AQUI | INSERIR COMENTÁRIO AQUI |
*/
void createDatabase(Database db);
void deleteFromTable();
void alterTableModify();
void alterTableDrop();
void insertIntoTable(Table table);
void selectFromTable();
/*
*   | INSERIR COMENTÁRIO AQUI | INSERIR COMENTÁRIO AQUI | INSERIR COMENTÁRIO AQUI |
*/
char* concat(char *string1, char *string2);
void listAllTables();
/*
*   Remove a existência de um banco de dados por
*   meio de um comando
*
*   Recebe
*   @string
*/
void dropDatabase(Database database);
/*
*   Remove a existência de uma tabela por meio de
*   um comando
*
*   Recebe
*   @string
*/
void dropTable(Table table);
/*
*   Reescreve uma table existênte por outra criada
*
*   Recebe
*   @Table
*/
void replaceTable(Table table);