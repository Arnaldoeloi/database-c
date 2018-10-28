#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Bibliotecas de arquivos
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//fim bibliotecas de tratamento de arquivos

char* concat(char *string1, char *string2){
    char *result = malloc(strlen(string1) + strlen(string2) + sizeof(char)); 
    strcpy(result, string1);
    strcat(result, string2);
    return result;
}

void createDatabase(char* name){
	struct stat st = {0};
	char* path= NULL;
	path = concat("dbs/", name); //concatena o nome do banco com a pasta onde ele será armazenado
	printf("Caminho do banco: %s\n", path);
	if (stat(path, &st) == -1) { //verifica a existência do arquivo
		printf("O arquivo não existe, criando...\n");
	    if(mkdir(path, 0777)==-1){ //cria o arquivo com permissão 0777
			printf("Ocorreu um problema, tente criar com outro nome ou execute o programa com privilegios de administrador.");
			perror("mkdir");
		}else{
			printf("Banco criado.\n");
		}
		free(path);
	}else{
		printf("A pasta já existe. Não será criada uma nova.\n");
	}

}

void selectFromTable();
void createTable();


void deleteFromTable();
void alterTableModify();
void alterTableDrop();
void insertIntoTable();
void selectFromTable();
