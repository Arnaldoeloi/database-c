#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database_operations.h"
#include "strings.h"
#include "colors.h"


void commandVersion(){
	printf("Alpha 1.0.0 All rights reserved to Go Horse enterprise LTDA (The Original One).\n");
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
	printf("\tcreate table ");
	magenta();
	printf("nome_do_banco.nome_da_tabela");
	boldGreen();
	printf(" (");
	blue();
	printf("int ");
	yellow();
	printf("nome_Primary_Key ");
	red();
	printf("pk");
	boldGreen();
	printf(", ");

	blue();
	printf("tipo2 ");
	yellow();
	printf("nome_da_coluna ");
	red();	
	printf("...");
	boldGreen();
	printf(")");
	resetColor();

	printf("\n\n");

	yellow();
	printf("Listar ");
	resetColor();
	printf("todas as tabelas:\n\n ");
	green();
	printf("\tlist tables\n\n");

	resetColor();
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

//a função receberá uma string e retornará 1 se é um tipo válido ou 0, caso não seja
int hasValidType(char* data){
	//os tipos de dados para as colunas poderão ser os tipos primitivos em C
	//(char, int, float e double) e strings
	//Os espaços da comparação garantem que o tipo sempre venha primeiro e que não faz parte do nome 
	if(findInVector("char ", data))return 1;
	if(findInVector("int ", data))return 1;
	if(findInVector("float ", data))return 1;
	if(findInVector("double ", data))return 1;
	if(findInVector("string ", data))return 1;
	
	return 0;
}

void validateCreateTable(char* command){
	/*
	verifica se o comando possui .(), garantindo que segue o padrão de escrita correto para evitar erros
	de segmentação causados por problemas na sintaxe
	*/
	if(!(strstr(command, ".") && strstr(command, "(") && strstr(command,")"))){
		boldRed();
		printf("O comando foi digitado incorretamente. Digite help para ver a sintaxe dos comandos.\n");
		resetColor();
	}else{
		char* nameTable=(char*) calloc(strlen(command)+1,sizeof(char));
		strcpy(nameTable, command);
		
		Table table;
		table.name=NULL; 		//será definido no escopo da função
		table.database = NULL; 	//será definido no escopo da função
		table.numRows=1;		//como a tabela está sendo criada, será criada com apenas uma linha (a de definição das colunas)
		table.numCols=0;		//será definido no escopo da função, começa com zero pois será acrescida para cada dado
		
		int count=0;
		char *end_str=NULL; //até que posição da memória será quebrada
		char *token = strtok_r(nameTable, " .(", &end_str); //quebra a string e retorna a primeira ocorrência de quebra para espaços, pontos ou abertura de parênteses 

		/*
		*	DEFINE O NOME DO BANCO E DA TABELA
		*/
		while (count < 3){ //quebrará 3 vezes (count<3, com count começando em 0) pois o nome do banco é o primeiro e o tabela o imediatamente próximo
			/*
			cont==0:
				table
			cont==1:
				nome_do_banco
			cont==2:
				nome_da_tabela
			*/
			
			char *end_token=NULL;
			token = strtok_r(NULL, " .(", &end_str); //continuará quebrando a string. NULL é passado por parâmetro para que seja a próxima ocorrência válida
			if(count==1){
				//caso seja a segunda vez no laço (count==1), a string quebrada é justamente o nome do banco
				table.database=(char*) realloc(table.database, (sizeof(char)*strlen(token)+sizeof(char)));
				table.database=token;	
			}
			count++;
		}
		table.name=(char*) realloc(table.name, (sizeof(char)*strlen(token)+sizeof(char)));
		table.name=token;
		/*
		*/

		//valida o que há entre os parênteses e remove as vírgulas entre os dados

		char* string=betweenParenthesis(command); 		//retorna as colunas entre os parênteses
		char* data = removeSpacesAfterCommas(string);	//retorna a string sem os espaços após as vírgulas

		//Aqui, a função strstr() verifica se há uma chave primária na tabela, caso não haja, não será criada.
		char *pk = " pk";
		char *pch = strstr(data, pk); //se há presença de chave primária (equivalente a um booleano)
		int pksCount=0; 		//conta quantas pks há, evitando que ocorra mais de uma ocorrência. A chave primária deve ser única
		int pkNotInt=0; 		//variavel de erro para Pk não inteira
		int hasInvalidType=0; 	//caso ocorra de algum dado não possuir tipo válido

		//Se não encontrar a palavra pk nas colunas, já é sabido que não há primary key
		if(pch){
			/*
			*	DEFINE TODOS OS DADOS DA PRIMEIRA LINHA
			*/
			table.data=(char***) calloc(1, sizeof(char***));
			table.data[0]=(char**) calloc(1, sizeof(char**));

			end_str=NULL;
			token = strtok_r(data, ",", &end_str); //separa os dados para cada vírgula, pois cada coluna está entre as vírgulas
			
			
			table.data=(char***) calloc(1, sizeof(char***));
			table.data[0]=(char**) calloc(1, sizeof(char**));

			count=0;
			while (token != NULL){
				table.data[0][count]=(char*)malloc(strlen(token)*sizeof(char));
				char *end_token=NULL;
				table.data[0][count]=token;

				if(strstr(table.data[0][count]," pk ") || strstr(table.data[0][count]," pk")){
					pksCount++;
					if(!findInVector("int ", table.data[0][count])){
						pkNotInt=1;
					}
				}
				if(!hasValidType(table.data[0][count])){
					hasInvalidType=1;
					break;
				}
				table.numCols++; //para cada dado armazenado, uma nova coluna é contada
				token = strtok_r(NULL, ",\n", &end_str);
				count++;
			}

			//print com os dados
			yellow();
			printf("Nome: %s\n", table.name);
			printf("Banco: %s\n", table.database);
			// printf("Numero de linhas: %i\n", table.numRows);
			// printf("Numero de Colunas: %i\n", table.numCols);
			resetColor();


			//Criará o arquivo se o comando foi escrito corretamente
			if(!hasInvalidType && pksCount==1 && !pkNotInt){
				createTable(table);
			}else{
				boldRed();
				printf("Não foi possível criar a tabela.\n");
				if(pksCount>1){
					printf("Há mais de uma chave primária. Apenas uma é permitida.\n");
				}
				if(pkNotInt){
					printf("A chave primária não é inteira.\n");
				}
				if(hasInvalidType){
					printf("Os únicos tipos permitidos são ");
					boldCyan();
					printf("int, float, double, char e string.\n");
				}
				resetColor();
			}
		}else{
			boldRed();
			printf("Não foi possível criar a tabela.\n");
			printf("Não há nenhuma chave primária.\n");
			resetColor();
		}

	}
}

Table findTableInCommand(char* command){
	
	Table t;
	char* database=NULL;
	char* table=NULL;
	char* commandCpy=malloc(sizeof(char)*strlen(command)+sizeof(char));

	memcpy(commandCpy, command, strlen(command) + 1);
	commandCpy[strlen(command)+1]='\0';
	int pointFound=0;
	for(int i=0; i < (int)strlen(commandCpy); i++){
		if(commandCpy[i]=='.'){
			pointFound=1;
			//for regressivo até achar o espaço, irá printar ao contrário
			int cont=0;
			for(int j=i-1; commandCpy[j]!=' '; j--){
				database=(char*) realloc(database, cont*sizeof(char)+sizeof(char));
				database[cont]=commandCpy[j];
				cont++;
			}
			database=(char*) realloc(database, cont*sizeof(char)+sizeof(char));
			database[cont]='\0';
			cont=0;


			//for progressivo até achar o espaço
			for(int j=i+1; (commandCpy[j]!=' ' && commandCpy[j]!='\0'); j++){
				table=(char*) realloc(table, cont*sizeof(char)+sizeof(char));
				table[cont]=commandCpy[j];
				cont++;
			}
			table=(char*) realloc(table, cont*sizeof(char)+sizeof(char));
			table[cont]='\0';
			break;
		}
	}
	boldRed();
	resetColor();
	//Se o comando estiver inválido, retornará uma tabela com campos database e table = NULL
	if(!pointFound){
		boldGreen();
		resetColor();

		Table nullable;
		nullable.name=NULL;
		nullable.database=NULL;
		return nullable;
	}
	int cont=0;
	database=invertString(database);

	t.name=(char*) malloc((int)strlen(table)*sizeof(char)+sizeof(char));
	t.database=(char*) malloc((int)strlen(database)*sizeof(char)+sizeof(char));
	t.name=table;
	t.database=database;
	return t;
}	
/*
*	Irá receber só as colunas que irá printar,
*	a tabela filtrada e
*	os filtros
*/
void filterTable(char* columns, Table table, char* filters){
	printf("collums: %s\n", columns);
	printf("filter: %s\n", filters);

	Table filteredTable;
	filteredTable.database	=	table.database;
	filteredTable.name		=	table.name;
	filteredTable.data		=	(char***) calloc(table.numRows, sizeof(char***));

	int columnNotFound=0; 	//se alguma coluna passado por parâmetro não for encontrada, não deve selecionar a tabela, default=false
	int hasInvalidType=0;	//se alguma coluna de filtro (Ex: where coluna >= 5) for inválida

	filteredTable.numCols=0;
	
	int printableCollums[99];
	int printableRows[99];

	int filterColumns[10]; //guarda a posição das colunas utilizadas na validação dos dados de filtro

	// if(filters!=NULL){
	// 	Filter* filtersObj=calloc (1,sizeof(Filter));

	// 	char *end_token1=NULL;
	// 	int numberOfFilters=0;
	// 	char *token1 = strtok_r(filters, ",", &end_token1);



	// 	while(token1!=NULL){
	// 		char *end_token2=NULL;			
	// 		char *token2 = strtok_r(token1, " ", &end_token2);
			
			
	// 		int contAux=0;
	// 		while(token2!=NULL){
	// 			/*
	// 				contAux==0:
	// 					filter.column
	// 				contAux==1:
	// 					filter.typeOfFilter
	// 				contAux==2:
	// 					filter.value
	// 			*/

	// 			printf("token2:%s\n", token2);
	// 			if(contAux==0){
	// 				filtersObj[numberOfFilters].column=(char*) calloc(strlen(token2)+1, sizeof(char));
	// 				filtersObj[numberOfFilters].column=token2;
	// 			}
	// 			else if(contAux==1){
	// 				filtersObj[numberOfFilters].typeOfFilter=(char*) calloc(strlen(token2)+1, sizeof(char));
	// 				filtersObj[numberOfFilters].typeOfFilter=token2;
	// 			}
	// 			else if(contAux==2){
	// 				filtersObj[numberOfFilters].value=(char*) calloc(strlen(token2)+1, sizeof(char));
	// 				filtersObj[numberOfFilters].value=token2;
	// 			}
	// 			token2 = strtok_r(NULL, " ", &end_token2);
	// 			contAux++;
	// 		}

	// 		token1 = strtok_r(NULL, ",", &end_token1);
	// 		numberOfFilters++;
	// 	}

	// 	numberOfFilters--; //pois na ultima iteração do while um filtro a mais foi levado em consideração (numberOfFilters++)

	// 	/*
	// 		Valida se as colunas do filtro existem existem
	// 	*/

	// 	int contAux=0;
	// 	for(int i=0; i<numberOfFilters; i++){
	// 		int hasValidType=0;
	// 		for(int j=0; j<table.numCols; j++ ){
	// 			if(strstr(table.data[0][j],filtersObj[i].column)==0){
	// 				filterColumns[contAux]=j;
	// 				hasValidType=1;
	// 				contAux++;
	// 			}
	// 		}
	// 		if(!hasValidType){
	// 			hasInvalidType=1;
	// 		}
	// 	}

	// 	if(!hasInvalidType){
	// 		for(int i=0; i < table.numRows; i++){
	// 			for(int j=0; j < contAux; j++){
	// 				//filterColumns
	// 			}
	// 		}
	// 	}
	// }

	printf("416\n");
	if(strcmp(columns, "*")==0){ //==0 significa que são iguais
		filteredTable.numCols=table.numCols;
		filteredTable=table;
	}else{
		char *end_token=NULL;
		char *token = strtok_r(columns, ",", &end_token);
		
		while(token!=NULL){
			int columnFound=0;
			for (int i=0; i < table.numCols; i++){
				if(strstr(table.data[0][i], token)){
					boldGreen();
					resetColor();
					columnFound=1;
					printableCollums[filteredTable.numCols]=i;
					filteredTable.numCols++;
				}
				//table.data[0][i] = token;
			}
			if(!columnFound){
				columnNotFound=1;
			}
			token = strtok_r(NULL, ",", &end_token); 
		}
		//free(token);

		if(!columnNotFound){
			for(int i=0; i<table.numRows; i++){
				int cont=0;
				filteredTable.data[i]=(char**) calloc(filteredTable.numCols, sizeof(char**));
				//printf("444\n");
				for(int j=0; j<filteredTable.numCols; j++){
					//printf("446\n");
					//printf("table.data[%i][%i]=%s\n", i, printableCollums[j], table.data[i][printableCollums[j]]);
					//printf("table.data[0][0]=%s\n", table.data[0][0]);
					filteredTable.data[i][cont]=table.data[i][printableCollums[j]];
					//printf("448: %s\n",filteredTable.data[i][cont]);
					cont++;
				}
			}
		}else{
			boldRed();
			printf("Não é possível fazer a seleção da tabela. Alguma das colunas passadas por parâmetro não existem.\n");
			resetColor();
		}
	}

	boldCyan();
	printf("545 !columnNotFound=%i | !hasInvalidType=%i,\n",!columnNotFound, !hasInvalidType);

	if(!columnNotFound && !hasInvalidType){
		printTable(filteredTable);
	}
}

void validateSelect(char* command){
	boldCyan();
	printf("318\n");
	resetColor();
	char* commandTemp=(char*)calloc(strlen(command)+1, sizeof(char)); 
	strcpy(commandTemp, command);

	boldCyan();
	printf("324\n");
	resetColor();
	
	char *end_str=NULL;
    char *token = strtok_r(command, " ", &end_str);

	boldCyan();
	printf("331\n");
	resetColor();

	char** commands=(char**) calloc(10, sizeof(char**));
	int cont=0;
	while (token != NULL){
		char *end_token=NULL;
		commands[cont]=token;
		token = strtok_r(NULL, " ", &end_str);
		cont++;
	}
	boldCyan();
	printf("343\n");
	resetColor();
	char* collumns=NULL;
	char* filters=NULL;
	if(strcmp(commands[1], "*")==0){
		collumns=(char*) calloc (2, sizeof(char));
		collumns="*";
		if(isSubstringInString(commandTemp, "where")){
			filters = malloc( strlen(betweenParenthesis(commandTemp))*sizeof(char)+sizeof(char));
			filters = betweenParenthesis(commandTemp);
			filters = removeSpacesAfterCommas(filters);
		}
	}else{
		boldCyan();
		printf("357\n");
		resetColor();

		//esse for eliminará a primeira ocorrência de parenteseses.
		//caso o comando tenha where
		collumns = malloc( strlen(betweenParenthesis(commandTemp))*sizeof(char)+sizeof(char));
		
		boldCyan();
		printf("365\n");
		resetColor();
		
		/*
		*	A LINHA 371 ESTÁ LANÇANDO ERRO FATAL, TODO: ENTENDER O MOTIVO E CORRIGIR
		*/
		collumns = betweenParenthesis(commandTemp);

		boldCyan();
		printf("371\n");
		resetColor();

		collumns =  removeSpacesAfterCommas(collumns);

		printf("365: %s\n", commandTemp);

		//limpa os primeiros parenteses para que haja apenas os parenteses dos filtros (após o where)
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
			char* filters=NULL;
		}
	}
	Table t = findTableInCommand(commandTemp);
	char* pathToFile="dbs/";
	if(t.database!=NULL){
		//"dbs/ nomeDoBanco / nomeDaTabela .csv"
		char* stringTemp=concat(pathToFile, concat(concat(t.database,"/"),t.name));
		pathToFile=concat(stringTemp, ".csv");
		t=csvToTable(pathToFile);
	}


	if(t.database!=NULL){
		printf("PathToFile:%s\n", pathToFile);
		filterTable(collumns, t, filters);
	}else{
		printf("Você não selecionou nenhum banco de dados válido. Reescreva o comando. \n");
	}
	
}

void validateInsertIntoTable(char* command){

	if(isSubstringInString(command, "into") == 1){
		if(isInString(command, '(') == 1 && isInString(command, ')') == 1){
			//assina o valor da Table a ser criada;
			Table table;
			table = findTableInCommand(command); //Retorna o nome da table e a database que essa está inserida;
			table.numCols = 1; // numCols=1 pois o número de colunas iniciais é sempre igual a 1;
			table.numRows = 1;

			if (isInString(command,'|') == 0){
				char* string = NULL;
				/* 
					Define a string com a série de passos a seguir:
					1-Remove todos os espaços depois das vírgulas
					2-Pega somente o que está entre dos parénteses
					3-Troca as vírgulas por barras verticais;
				*/
				if (isInString(command, '\"') == 1){
					string = switchCommaToVerticalBarWithQMarks(betweenParenthesis(removeSpacesAfterCommas(command)));
				} else{
					string = switchCommaToVerticalBarWithQMarks(betweenParenthesis(removeSpacesAfterCommas(command)));
				}
				//Conta o número de colunas que há na string
				for(int i=0;i < (int)strlen(string) ;i++){
					if (string[i] == '|'){
						table.numCols++;
					}
				}
				//Define o valor para table.data[0][x], onde x é a posição na coluna;
				table.data  = (char***)calloc(1,sizeof(char**));
				table.data[0] = (char**)calloc(table.numCols,sizeof(char*));

				//Define o valor do token e a sua quebra que será usado pela função strok_r;
				char *end_token=NULL;
				char *token = strtok_r(string, "|", &end_token);
				
				//Transforma o valor de table.data[0][i] no valor do token
				for (int i=0; i < table.numCols; i++){;
					table.data[0][i] = token;
					token = strtok_r(NULL, "|", &end_token); // Define token como o valor após '|'
				}
				//free(token);
				//Chama a função void insertIntoTable mandando a table criada.
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

	}else if(findInVector("alter table ", command)){
		printf("Altering table\n");

		
	}else if(findInVector("insert ", command)){
		printf("Inserting into table\n");
		validateInsertIntoTable(command);

	}else if(findInVector("delete from ", command)){
		printf("Deleting table\n");


	}else if(findInVector("drop database ", command)){
		printf("Drop table\n");


	}else if(findInVector("select ", command)){
		printf("Selecting data from table\n");
		validateSelect(command);

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