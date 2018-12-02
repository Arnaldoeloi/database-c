#include <stdlib.h>
#include "database_types.h"

/*
*   Recebe um caminho para um arquivo .csv depois
*   retorna um struct do tipo Table
*
*   Recebe
*   @char*
*/
Table csvToTable(char* pathToFile);
/*
*
*/
Database commandToDatabase(char* command);
/*
*   Recebe um caminho para um arquivo .cs, depois
*   retorna um inteiro com a quantidade de linhas
*   na tabela do banco.
*
*   Recebe
*   @char* pathToFile
*
*   Retorna
*   @int   
*/
int countRowsInCsv(char* pathToFile);
void selectFromTable();
/*
*   Recebe uma tabela e cria um arquivo .csv dentro
*   de um banco
*   
*   Recebe
*   @Table table
*/
void createTable(Table table);
/*
*   Recebe uma struct Database e cria uma pasta que
*   funciona como um banco
*
*   Recebe
*   @Database db
*/
void createDatabase(Database db);
/*
*   Recebe uma struct do tipo Table e insere o dado
*   contido em uma tabela .csv
*   
*   Recebe
*   @Table table
*/
void insertIntoTable(Table table);
/*
*   Concatena duas strings, colocando a segunda logo
*   após o final da primeira. Também realoca o espaço
*   na memória da primeira string
*   
*   Recebe
*   @char* string1
*   @char* string2
*/
char* concat(char *string1, char *string2);
/*
*   Lista todas as tabelas e seus respectivos bancos
*   onde estão inseridas
*/
void listAllTables();
/*
*   Recebe uma struct do tipo Database e deleta um
*   banco de dados contindo no caminho especificado.
*
*   Recebe
*   @Database database
*/
void dropDatabase(Database database);
/*
*   Recebe uma struct do tipo Table e deleta um
*   arquivo .csv contindo no caminho especificado.
*
*   Recebe
*   @Table table
*/
void dropTable(Table table);
/*
*   Recebe uma table e Reescreve um arquivo .csv 
*   existênte por outra criada a partir dessa table
*
*   Recebe
*   @Table table
*/
void replaceTable(Table table);