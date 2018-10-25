#include <stdio.h>
#include <stdlib.h>
#include "libs/common.h" //Biblioteca com comandos padrões (leitura do comando)

int main(){
	commandVersion();
	char*v=input();
	printf("%s\n", v);
}	