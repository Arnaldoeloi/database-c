#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs/common.h" //Biblioteca com comandos padrões (leitura do comando)

int main(){
/*	commandVersion();
	while(1){
		char*v=input();
		if(strcmp("exit",v)==0){
			break;
		}
		execute(v);
	}
	return 0;
*/
	int x;
	char* p = input();
	x = numberOfWords(p, " ");
	printf("%d", x);

}	