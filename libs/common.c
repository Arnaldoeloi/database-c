#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database_operations.h"
#include "strings.h"
#include "colors.h"

void PrintTable(Table table);

void commandVersion(){
	printf("0.0.3 All rights reserved to Go Horse interprise LTDA.\n");
	printf("Digite ");
	yellow();
	printf("help ");
	resetColor();
	printf("ou ");
	yellow(); 
	printf("man ");
	resetColor();
	printf("para ver os comandos.\n");
}

void printHelp(){
	printf("-----------------\\-------//----------------------------------\\-------//-----------------\n");
	printf("Criar um novo ");
	yellow();
	printf("banco de dados ");
	resetColor();
	printf("(disponivel na pasta 'dbs/'):\n\n");
	green();
	printf("\tcreate database ");
	magenta();
	printf("nome_do_banco\n");
	resetColor();

	printf("\n\n");

	printf("Criar uma nova ");
	yellow();
	printf("tabela ");
	resetColor();
	printf("(disponivel na pasta 'dbs/");
	yellow();
	printf("nome_do_banco ");
	resetColor();
	printf("'):\n\n");
	green();
	printf("\tcreate ");
	magenta();
	printf("nome_da_tabela\n");
	resetColor();

	printf("\n\n");

	printf("Digite ");
	boldRed();
	printf("exit ");
	resetColor();
	printf("para sair do programa.\n");
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



int execute(char* command){
	if((strcmp("help", command)==0) || (strcmp("man", command)==0) || (strcmp("h", command)==0)){ 
		printHelp();
	}else if(findInVector("create database ", command) || findInVector("CREATE DATABASE ", command)){
		//char* name = wordInPositionAfterSeparations(command, " ", 2);
		yellow();
		printf("\nCreating database\n");
		resetColor();
		
		command=lowerCase(command);
		Database db=commandToDatabase(command);
		createDatabase(db);
	}else if(findInVector("create ", command)){
		yellow();
		printf("Creating table\n");
		resetColor();

		betweenParenthesis(command);
	}else if(findInVector("alter table ", command)){
		printf("Altering table\n");
	}else if(findInVector("insert into ", command)){
		printf("Inserting into table\n");
	}else if(findInVector("delete from ", command)){
		printf("Deleting table\n");
	}else if(findInVector("drop database ", command)){
		printf("Drop table\n");
	}else if(findInVector("select ", command)){
		printf("Selecting data from table\n");
		int rows=countRowsInCsv("dbs/escola/planilha.csv");
		//printf("Rows: %f",rows);
		csvToTable("dbs/escola/planilha.csv");

	}else{
		boldRed();
		printf("Comando não encontrado.\n");
		resetColor();
		printf("Você não quis dizer ");
		boldGreen();
		printf("help ");
		printf("?\n");
		resetColor();
	}
}



Database commandToDatabase(char* command){
	Database db;
	db.name = wordInPositionAfterSeparations(command, " ", 2);
	return db;
}

Table commandCreateTabletoTable(char* command){

}



void printTable(Table table){
	//bigOne é um vetor string que armazenará a maior variável do tipo string em uma coluna;
	char** biggestStringInCols = (char**)calloc(table.numCols,sizeof(char**));

	for (int i=0; i < table.numCols; i++){
		biggestStringInCols[i] = (char*)calloc(strlen(table.data[i][0]),sizeof(char*));
		for (int j=0; j < table.numRows; j++){
			if (strcmp(biggestStringInCols[i],table.data[j][0]) == 0 || strcmp(biggestStringInCols[i],table.data[j][0])> 0){
				continue;
			} else{
				biggestStringInCols[i] = table.data[i][0];
			}
		}
	}

	for (int i=0; i < table.numRows; i++){

		for(int j=0; j < table.numCols; j++){
			printf ("||%s", table.data[i][j]);
			for(int k=0; k < (int)strlen(biggestStringInCols[i]) - (int)strlen(table.data[i][j]);k++){
				printf(" ");
			}
			printf("||");
		}
		
		if (i == 0){
			for(int j=0; j < table.numCols; j++){
			printf ("||");
			for(int k=0; k < (int)strlen(biggestStringInCols[i]) - (int)strlen("");k++){
				printf("-");
			}
			printf("||");
			}
		}
	}
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