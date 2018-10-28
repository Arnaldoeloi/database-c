#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database_operations.h"
#include "database_types.h"

void commandVersion(){
	printf("0.0.3 All rights reserved to Go Horse interprise LTDA.\n");
}

void printHelp(){
	printf("Aqui digitaremos todos os comandos\n");
}

char* input(){
	char*string = malloc(sizeof(char));

	int i=0;
	while(string[i-1]!='\n'){
		string=realloc(string, (sizeof(char)*i+sizeof(char)));
		string[i]=getchar();
		i++;
	}
	string[i-1]='\0';
	return string;
}


int findInVector(char* subvector, char* vector){
	if (strlen(subvector) > strlen(vector)){
		return 0;
	}else{
		for (int i=0; subvector[i] != '\0'; i++){
			if(subvector[i] ==  vector[i]){
				if (i == (int)strlen(subvector)-1) return 1;
			}else{
				return 0;
			} 
		}
	}
}


char* wordInPositionAfterSeparations(char* string, char* caracteres, int pos){
	char m[100][100];
	char *token;
	token = strtok(string, caracteres);

	for(int i=0; token != NULL; i++) {
		for(int j=0; j < (int)strlen(token); j++){
			m[i][j] = token[j];
		}
		token = strtok(NULL, caracteres);
	}

	char* word=NULL;
	for (int i = 0; i < (int)strlen(m[pos]); i++){
		word=realloc(word, i*sizeof(char)+sizeof(char));
		word[i]=m[pos][i];
	}
	return word;
}


int execute(char* command){
	if((strcmp("help", command)==0) || (strcmp("man", command)==0)){
		printHelp();
	}else if(findInVector("create database ", command)){
		char* name = wordInPositionAfterSeparations(command, " ", 2);
		printf("Creating database\n");
		createDatabase(name);
	}else if(findInVector("create ", command)){
		printf("Creating table\n");
	}else if(findInVector("alter table ", command)){
		printf("Altering table\n");
	}else if(findInVector("insert into ", command)){
		printf("Inserting into table\n");
	}else if(findInVector("delete from ", command)){
		printf("Deleting table\n");
	}else if(findInVector("drop database ", command)){
		printf("Drop table\n");
	}else if(findInVector("select ", command)){
		printf("Select table\n");
	}
}



Database commandToDatabase(char* command){
	Database db;
	db.name = wordInPositionAfterSeparations(command, " ", 2);
	return db;
}


void PrintTable(Table table){
/*Passo 1 - Comparar todos os valores de uma table e printa-los
*\

}

/*Table usuarios;
	usuarios.name = "usuarios";
	usuarios.database = "escola";
	usuarios.collums = "id,nome,senha,e-mail";
	usuarios.data = "0,pedro,corinthinas,pedro@gmail.com";

	Database minecraft;
	minecraft.name = "minecraft";
	minecraft.tables = (Table*)calloc(1,sizeof(Table));

	minecraft.tables[0] = usuarios;

	printf("nome: %s\n",minecraft.tables[0].name);
	printf("database: %s\n",minecraft.tables[0].database);
	printf("colunas: %s\n",minecraft.tables[0].collums);
	printf("data: %s\n",minecraft.tables[0].data);

	return 0;
*/