#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database_operations.h"
#include "strings.h"
#include "colors.h"


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
void printTable(Table table){
	// printf("table.numRows=%i\n", table.numRows);
	// printf("table.numCols=%i\n", table.numCols);
	for(int i=0; i < table.numRows; i++){

		int* biggestStringOfCols = (int*)calloc(strlen(table.data[i][0]),sizeof(int*));

		for(int j=0; j < table.numCols; j++){

			for (int k=0; k < table.numRows; k++){

				if ((int)strlen(table.data[k][j]) < biggestStringOfCols[j]){
					continue;
				} else{
					biggestStringOfCols[j] = (int)strlen(table.data[k][j]);
				}
			}
		}
		
		if(i==0){
			for(int j=0; j < table.numCols+1; j++){
				resetColor();
				printf("|");
				if (j == table.numCols){
					continue;
				} else{
					int z = biggestStringOfCols[j];
					for (int k=0; k < z ;k++){
						printf("=");
					}
			    }

			}
			printf("\n");
			for(int j=0; j < table.numCols; j++){
				int z = biggestStringOfCols[j];
				resetColor();
				printf("|");
				magenta();
				printf("%s", table.data[0][j]);
				if (j == table.numCols-1){
					continue;
				} else{
					for (int k=0; k < z - (int)strlen(table.data[i][j]);k++){
						printf(" ");
					}
			    }
			}
			printf("\n");
			for(int j=0; j < table.numCols+1; j++){
				resetColor();
				printf("|");
				if (j == table.numCols){
					continue;
				} else{
					int z = biggestStringOfCols[j];
					for (int k=0; k < z ;k++){
						printf("=");
					}
			    }

			}
		}else{
			for(int j=0; j < table.numCols; j++){
				resetColor();
				printf("|");
				yellow();
				printf("%s", table.data[i][j]);
				int z = biggestStringOfCols[j];
				if (j == table.numCols-1){
					continue;
				} else{
					for (int k=0; k < z - (int)strlen(table.data[i][j]);k++){
						printf(" ");
					}
			    }
			
			}
		}
		if(i==0){
			resetColor();
		}
		printf("\n");
	}
	resetColor();
}

void validateCreateTable(char* command){
	char* nameTable=(char*) calloc(strlen(command)+1,sizeof(char));
	strcpy(nameTable, command);
	
	Table table;
	table.name=NULL;
	table.database = NULL;
	table.numRows=1;
	table.numCols=0;
	
	int count=0;
	char *end_str=NULL;
    char *token = strtok_r(nameTable, " .(", &end_str); 

	/*
	*	DEFINE O NOME DO BANCO E DA TABELA
	*/
	while (count < 3){
		char *end_token=NULL;
        token = strtok_r(NULL, " .(", &end_str);
		//printf("Token: %s\n", token);
		if(count==1){
			table.database=(char*) realloc(table.database, (sizeof(char)*strlen(token)+sizeof(char)));
			table.database=token;	
			//printf("Database: %s\n", table.database);	
		}
		count++;
	}

	table.name=(char*) realloc(table.name, (sizeof(char)*strlen(token)+sizeof(char)));
	table.name=token;


	//valida o que há entre os parênteses
	char* string=betweenParenthesis(command);
	char* data = removeSpacesAfterCommas(string);

	//Aqui, a função strstr() verifica se há uma chave primária na tabela, caso não haja, não será criada.
	char *pk = " pk";
	char *pch = strstr(data, pk);
	if(pch){
		/*
		*	DEFINE TODOS OS DADOS DA PRIMEIRA LINHA
		*/
		table.data=(char***) calloc(1, sizeof(char***));
		table.data[0]=(char**) calloc(1, sizeof(char**));

		end_str=NULL;
		token = strtok_r(data, ",", &end_str); //separa os dados para cada \n
		
		
		table.data=(char***) calloc(1, sizeof(char***));
		table.data[0]=(char**) calloc(1, sizeof(char**));

		count=0;
		while (token != NULL){
			table.data[0][count]=(char*)malloc(strlen(token)*sizeof(char));
			char *end_token=NULL;
			table.data[0][count]=token;
			table.numCols++;
			token = strtok_r(NULL, ",\n", &end_str);
			count++;
		}

		//print com os dados
		yellow();
		printf("Nome: %s\n", table.name);
		printf("Database: %s\n", table.database);
		printf("Numero de linhas: %i\n", table.numRows);
		printf("Numero de Colunas: %i\n", table.numCols);
		resetColor();


		//Criará o arquivo
		createTable(table);
	}else{
		boldRed();
		printf("Não foi possível criar a tabela.\n");
		printf("Não há nenhuma chave primária.\n");
		resetColor();
	}

}

/*
*	Irá receber só as colunas que irá printar,
*	a tabela filtrada e
*	os filtros
*/
void filterTable(char* collumns, Table table, char* filters){
	printf("collums: %s\n", collumns);
	printf("filter: %s\n", filters);
}
void validateSelect(char* command){

	char* commandTemp=(char*)calloc(strlen(command)+1, sizeof(char)); 
	strcpy(commandTemp, command);
	printf("CommandTemp: %s\n", commandTemp);
	printf("Command: %s\n", command);
	
	char *end_str=NULL;
    char *token = strtok_r(command, " ", &end_str);

	char** commands=(char**) calloc(10, sizeof(char**));
	int cont=0;
	while (token != NULL){
		char *end_token=NULL;
		printf("token: %s\n", token);
		commands[cont]=token;
		token = strtok_r(NULL, " ", &end_str);
		cont++;
	}
	printf("commands[1]=%s\n", commands[1]);
	if(strcmp(commands[1], "*")==0){
		printf("SELECT ALL\n");
		char* pathToFile="dbs/";
		char* stringTemp=concat(pathToFile, wordInPositionAfterSeparations(commandTemp, " ", 3));
		for(int i=0; i<(int)strlen(stringTemp);i++){
			if(stringTemp[i]=='.'){
				stringTemp[i]='/';
			}
		}

		pathToFile=concat(stringTemp, ".csv");
		printf("PathToFile:%s\n", pathToFile);
		Table t=csvToTable(pathToFile);

		if(t.database!=NULL){
			printf("PathToFile:%s\n", pathToFile);
			printTable(t);
		}
	}else{
		//esse for eliminará a primeira ocorrência de parenteseses.
		//caso o comando tenha where
		if(isSubstringInString(commandTemp, "where")){
			int findOpenningP=0;
			int findClosingP=0;
			for(int i=0; i<(int)strlen(commandTemp); i++){
				if(commandTemp[i]=='('){
					commandTemp[i]='-';
					findOpenningP=1;
				}else if(commandTemp[i]==')'){
					commandTemp[i]='-';
					findClosingP=1;
				}
			}
		}else{
			char* collumns = betweenParenthesis(commandTemp);
			collumns=removeSpacesAfterCommas(collumns);
			char* filters=NULL;
			printf("collumns: %s\n", collumns);
		}
	}
	printf("CommandTemp: %s\n", commandTemp);
	printf("Command: %s\n", command);
	
	
}

void validateInsertIntoTable(char* command){

	if(isSubstringInString(command, "into") == 1){
		if(isInString(command, '(') == 1 && isInString(command, ')') == 1){
			//assina o valor da Table a ser criada;
			Table table;
			table.name=NULL;
			table.database = NULL;
			table.numRows=1;
			table.numCols=1;

			// Põe valor igual ao do comando na table.name
			char* nameAndDatabase = getSubstringAfterSubstringInString(command, "into");
			wordInPositionAfterSeparations(nameAndDatabase,".", 1);
			table.name = realloc(table.name, (int)strlen(nameAndDatabase));
			table.name = nameAndDatabase;
			free(nameAndDatabase);

			// põe valor igual ao do comando na table.data
			nameAndDatabase = getSubstringAfterSubstringInString(command, "into");
			wordInPositionAfterSeparations(nameAndDatabase,".", 2);
			table.database = realloc(table.name, (int)strlen(nameAndDatabase));
			table.database = nameAndDatabase;
			free(nameAndDatabase);

			// Escreve os itens digitados entre parênteses no vetor de caracteres "string"

			if (isInString(command,'|') == 0){
				char* string = NULL;
				if (isInString(command, '\"') == 1){
					//TEMPORÁRIO//
					char* string = switchCommaToVerticalBarWithQMarks(betweenParenthesis(removeSpacesAfterCommas(command)));
				} else{
					char* string = switchCommaToVerticalBarWithQMarks(betweenParenthesis(removeSpacesAfterCommas(command)));
				}
				for(int i=0;i < (int)strlen(string);i++){
					if (string[i] == '|'){
						table.numCols++;
					}
				}
				table.data  = (char***)calloc(1,sizeof(char**));
				table.data[0] = (char**)calloc(table.numCols,sizeof(char*));

				char *end_token=NULL;
				char *token2 = strtok_r(string, "|", &end_token); //separa os dados a cada ,

				for (int i; i < table.numCols; i++){
					table.data[1][i] = token2;
					token2 = strtok_r(NULL, "|", &end_token);
				}
				insertIntoTable(table);

			}else {
				boldRed();
				printf("Erro: Caractere especial '|' nao suportado\n");
				resetColor();
			}
		} else{
			boldRed();
			printf("Erro: Nao ha parenteses separando os itens inseridos no comando digitado\n");
			resetColor();
		}
	} else{
		boldRed();
		printf("Erro: Nao ha \"Into\" no comando digitado\n");
		resetColor();
	}
}

Table commandCreateTabletoTable(char* command){
	Table table;
	table.name;
	table.database = "TODO";
	table.numRows=1;
	table.numCols=0;
	int count=0;

	char *end_str=NULL;
    char *token = strtok_r(command, " ", &end_str); 
	while (count < 2){
		char *end_token=NULL;
        token = strtok_r(NULL, " ", &end_str);
		count++;
	}
	table.name=token;
	
	char* row = betweenParenthesis(command);
	
	end_str=NULL;
    token = strtok_r(row, "|", &end_str); //separa os dados para cada \n
	
	
	table.data=(char***) calloc(1, sizeof(char***));
	table.data[0]=(char**) calloc(1, sizeof(char**));

    count=0;
	while (token != NULL){
		table.data[0][count]=(char*)malloc(strlen(token)*sizeof(char));
		char *end_token=NULL;
		table.data[0][count]=token;
        //printf("NOVOS DADOS = %s\n", token);
		table.numCols++;
        token = strtok_r(NULL, "|\n", &end_str);
		count++;
	}

	//print com os dados
	for(int i=0; i < table.numCols; i++){
		printf("%s\n",table.data[0][i]);
	}
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
		yellow();
		printf("\nCreating database\n");
		resetColor();
		command=lowerCase(command);
		Database db=commandToDatabase(command);
		createDatabase(db);


	}else if(findInVector("create table", command)){
		yellow();
		printf("Creating table\n");
		resetColor();
		validateCreateTable(command);
		//commandCreateTabletoTable(command);


	}else if(findInVector("alter table ", command)){
		printf("Altering table\n");

		
	}else if(findInVector("insert into ", command)){
		printf("Inserting into table\n");
		printf("\n StringFunction : |%s|\n", getSubstringAfterSubstringInString("insert (asdsadadsa) into db.table" , "into"));


	}else if(findInVector("delete from ", command)){
		printf("Deleting table\n");


	}else if(findInVector("drop database ", command)){
		printf("Drop table\n");


	}else if(findInVector("select ", command)){


		printf("Selecting data from table\n");
		validateSelect(command);
		//Table t = csvToTable("dbs/minecraft/asd.csv");
		//printTable(t);
		

	}else if(findInVector("list tables", command)){
		listAllTables();
	}
	else{
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