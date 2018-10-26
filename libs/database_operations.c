#include <stdio.h>
#include <stdlib.h>

//Bibliotecas de arquivos
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//fim bibliotecas de tratamento de arquivos


void select();
void create();

void createDatabase(){
	struct stat st = {0};

	if (stat("/some/directory", &st) == -1) {
		printf("Deu certo\n");
	    mkdir("/some/directory", 0700);
	}

}

void deleteFromTable();
void alterTableModify();
void alterTableDrop();
void insertIntoTable();
void selectFromTable();
