#include <stdio.h>
#include "database_types.h"

/*
*	Printa a versão do
*	programa.
*/
void commandVersion();

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
*	Responsável por descobrir se
*	um vetor está contido no outro
*
*	Recebe
*	@char* subvector	
*	@char* vector
*	
*	Retorna
*	@int 
*	
*	1->encontrou;
*	0->não encontrou;
*/
int findInVector(char* subvector, char* vector);
/*
*	Responsável por ler uma string e trata-la de forma
*   que essa fique escrita em uma Table com seu nome.
*   Depois a struct Table é posta na função dropDatabase
*
*	Recebe
*	@char* string
*	
*/
void validateDropDatabase(char* string);
/*
*	Responsável por ler uma string e trata-la de forma
*   que essa fique escrita em uma Table com seu nome e 
*   banco que está contida.
*   Depois a struct Table é posta na função dropDatabase
*
*	Recebe
*	@char* string
*/
void validateDropTable(char* string);
