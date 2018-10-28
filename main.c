#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs/common.h" //Biblioteca com comandos padrões (leitura do comando)
#include "libs/database_types.h"

int main(){
	commandVersion();
	while(1){
		char*v=input();
		if(strcmp("exit",v)==0){
			break;
		}
		execute(v);
	}
	return 0;

	return 0;
}	