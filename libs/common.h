#include <stdio.h>
#include "database_types.h"

/*
*	Printa a versão do
*	programa.
*/
void commandVersion();

/*
*   Printa os comandos utilizados no sistema.
*
*/
void printHelp();

/*
*   Recebe uma string e verifica se nela há presença dos tipos reservados pelo sistema.
*
*   Recebe
*   @char* data
*
*   Retorna
*   @int Se tem ou não um tipo válido
*/
int hasValidType(char* data);

/*
*   Recebe uma string e valida se deve ou não executar o comando
*   de criar um arquivo de tabela.
*
*   Recebe
*   @char* command
*
*   Retorna
*   @int Se pôde ou não criar um arquivo de tabela
*/
int validateCreateTable(char* command);

/*
*   Recebe uma string e encontra uma tabela nela (com o banco e nome, apenas).
*
*   Recebe
*   @char* command
*
*   Retorna
*   @Table com apenas o database e o name preenchidos
*/
Table findTableInCommand(char* command);

/*
*   Recebe duas strings e uma tabela e printa uma tabela com os filtros
*   aplicados. 
*
*   Recebe
*   @char* columns
*   @char* filteres
*   @Table table
*/
void filterTable(char* columns, Table table, char* filters);

/*
*   Recebe duas strings e uma tabela e deleta uma tabela com os filtros
*   aplicados. 
*
*   Recebe
*   @char* columns
*   @char* filteres
*   @Table table
*/
void deleteFromTable(char* columns, Table table, char* filters);

/*
*   Valida o comando de selecionar uma tabela e chama a filterTable()
*   caso o comando esteja de acordo com o esperado.
*
*   Recebe
*   @char* command
*/
void validateSelect(char* command);

/*
*   Altera a coluna de uma tabela (remove, adiciona ou muda seu tipo)
*
*   Recebe
*   @Table table
*   @char* typeOfAlter
*   @char* newColumn
*   @char* typeOfColumn
*/
void alterTable(Table table, char* typeOfAlter, char* newColumn, char* typeOfColumn);

/*
*   Valida o comando de alterar uma coluna de uma tabela e chama a alterTable()
*   caso o comando esteja de acordo com o esperado.
*
*   Recebe
*   @char* command
*/
void validateAlterTable(char* command);

/*
*   Valida o comando de deletar uma tabela e chama a deleteFromTable()
*   caso o comando esteja de acordo com o esperado.
*
*   Recebe
*   @char* command
*/
void validateDeleteFrom(char* command);

/*
*   Valida o comando de inserir dado em uma tabela e chama
*   a função de escrita em arquivo para inserir um novo dado em uma
*   tabela.
*
*   Recebe
*   @char* command
*/
void validateInsertIntoTable(char* command);

/*
*   Valida o comando de excluir um banco de dados chama
*   a função de delete recursivo de arquivos.
*
*   Recebe
*   @char* command
*/
void validateDropDatabase(char* command);

/*
*   Valida o comando de excluir uma tabela e chama
*   a função de delete de arquivo.
*
*   Recebe
*   @char* command
*/
void validateDropTable(char* command);

/*
*   Printa todos dados de uma tabela em formato de uma tabela.
*
*   Recebe
*   @Table table
*/
void printTable(Table table);

/*
*	Responsável por ler
*	da entrada padrão.
*	
*	Retorna
*	@char* string lida
*/
char* input();

/*
*	Responsável por executar o
*	comando de banco de dados
*	passado por parametro
*
*	Recebe
*	@char* comando_para_execução_no_banco
*
*	Retorna
*	@int 
*	
*	1->sucesso;
*	0->falha;
*/
int execute(char* command);

/*
*	Responsável por ler uma string e encontrar e ler, linha à linha,
*   um arquivo e executar as funções desse arquivo dentro do sistema.
*
*	Recebe
*	@char* command
*/
void externalInstructions(char* command);

/*
*	Responsável por ler uma string e encontrar a struct
*   de um banco na string.
*
*	Recebe
*	@char* command
*
*   Retorna
*   @Database 
*/
Database commandToDatabase(char* command);

/*
*   Responsável por retornar uma tabela de um comando de criação de tabela
*
*   Recebe
*   @char* commmand 
*
*   Retorna
*   @Table
*/
Table commandCreateTabletoTable(char* command);