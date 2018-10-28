#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database_types.h"

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

void createDatabase(Database db){
	struct stat st = {0};
	char* path= NULL;
	path = concat("dbs/", db.name); //concatena o nome do banco com a pasta onde ele será armazenado
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
void createTable(Table table);


void deleteFromTable();
void alterTableModify();
void alterTableDrop();
void insertIntoTable();
void selectFromTable();

int countRowsInCsv(char* pathToFile){
	int rows=0;
	char ch;
	FILE *arq;
	arq = fopen(pathToFile, "r");
	if(arq == NULL)
		return -1;
	else{
		while( (ch=fgetc(arq))!= EOF ){
			if(ch == '\n'){
				rows++;
			}
		}
	}
	fclose(arq);
	return rows;
}


Table csvToTable(char* pathToFile){
	FILE *file;
	file = fopen( pathToFile, "r" );
	//FILE *file = fopen( pathToFile, "r" );
	if( file == NULL ) {
		printf( "Erro na abertura do arquivo!\n" );
	}else{
		while((ch=fgetc(file))!=EOF){
			printf("%c",ch);
		}
	}
	fclose(file);
	Table tb=NULL;
	return tb;
}


	// int questao, resposta, acertos, i;
	// char letra;
	// int gabarito[10] = {3, 4, 2, 1, 3, 1, 1, 2, 4, 4};
	// FILE *arquivo = fopen( "respostas.txt", "r" );
	// if( arquivo == NULL ){
	// 	printf( "Erro na abertura do arquivo" );
	// }
	// else{
	// 	acertos = 0;
	// 	fscanf(arquivo, "Aluno: %c\n", &letra);
	// 	for(i=0; i<10; i++){
	// 		fscanf(arquivo, "Resposta %d: %d\n", &questao, &resposta);
	// 		if(gabarito[questao-1] == resposta)
	// 			acertos++;
	// 		printf("Nota de %c\n", letra);
	// 		printf("%.2f\n", (float)acertos/10.0);
	// 		fclose( arquivo );
	// 	}
	// } 
 
