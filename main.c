#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs/common.h" //Biblioteca com comandos padrões (leitura do comando)

int main(){
	commandVersion();
	char*v=input();
	
	if(strcmp("create database",v)==0){
		printf("Uhuuuuuuulll!!!!!!!!!!!!!!!!\n");
	}else{
		printf("%s", v);
	}

}	