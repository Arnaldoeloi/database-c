#include <stdio.h>

/*
*	Printa a versão do
*	programa.
*/
void commandVersion();


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
*	Retorna
*	@int 
*	
*	1->sucesso;
*	0->falha;
*/
int execute(char* command);


/*
*	Responsável por encontrar
*	um subvetor em um vetor
*
*	Retorna
*	@int 
*	
*	1->encontrou;
*	0->não encontrou;
*/
int findInVector(char* command);

