#include <stdio.h>
#include <stdlib.h>

//Bibliotecas de arquivos
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//fim bibliotecas de tratamento de arquivos


void select();
void create();

void createDatabase(char* name){
	struct stat st = {0};

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
