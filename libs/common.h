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
*	Responsável por quebrar um string
*	em um vetor a cada caractere encontrado
*
*	Recebe
*	@char* string
*	@char caractere
*	
*	Retorna
*	@char**
*	
*/
char** split(char* string, char caractere);
