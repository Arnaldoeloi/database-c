#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Bibliotecas de arquivos
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//fim bibliotecas de tratamento de arquivos


void selectFromTable();
void createTable();

void createDatabase(char* name){
	struct stat st = {0};
	//strcat("dbs/", name);
	if (stat(name, &st) == -1) {
		printf("Deu certo\n");
	    mkdir(name, 0777);
	}else{
		printf("A pasta já existe.\n");
	}

}

void deleteFromTable();
void alterTableModify();
void alterTableDrop();
void insertIntoTable();
void selectFromTable();
