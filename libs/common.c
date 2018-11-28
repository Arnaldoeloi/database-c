#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database_operations.h"
#include "strings.h"
#include "colors.h"


void commandVersion(){
	
	printf("\n");
	printf("\t  ____         _   _                     \n");
	printf("\t / ___| ___   | | | | ___  _ __ ___  ___ \n");
	printf("\t| |  _ / _ \\  | |_| |/ _ \\| '__/ __|/ _ \\\n");
	printf("\t| |_| | (_) | |  _  | (_) | |  \\__ \\  __/\n");
	printf("\t \\____|\\___/  |_| |_|\\___/|_|  |___/\\___| SGBD\n\n");
											

	printf("Beta 3.0.0 All rights reserved to Go Horse enterprise LTDA (The Original One).\n");
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
	printf("## Criar um novo ");
	printf("banco de dados ");
	printf("(disponivel na pasta 'dbs/'):\n\n");

	green();
	printf("\tcreate database ");
	magenta();
	printf("nome_do_banco\n");
	resetColor();

	printf("\n\n");

	printf("## Criar uma nova ");
	printf("tabela ");
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

	printf("## Selecionar os dados de uma ");
	yellow();
	printf("tabela \n");
	printf("\n*Obs: o where e seus parametros são opcionais; existem para filtragem.");
	resetColor();
	green();
	printf("\n\n\tselect ");
	
	cyan();
	printf("[");
	resetColor;

	magenta();
	printf("*");
	
	cyan();
	printf(" ou ");
	resetColor;
	
	magenta();
	printf("(nome_coluna, nome_coluna2, nome_coluna3...)");

	cyan();
	printf("] ");
	resetColor;
	
	yellow();
	printf("where (");
	resetColor();
	
	magenta();
	printf("nome_coluna >= valor, nome_coluna2 like '%%string%%', ...");

	yellow();
	printf(")\n\n");
	resetColor();

	printf("##Listar ");
	printf("todas as tabelas:\n\n ");
	green();
	printf("\tlist tables\n\n");
	resetColor();
	
	printf("##Deletar ");
	printf("um banco de dados:\n\n ");
	green();
	printf("\tdelete database ");
	yellow();
	printf("nome_do_banco\n\n");
	resetColor();

	printf("##Deletar ");
	printf("uma tabela:\n\n ");
	green();
	printf("\tdelete table ");
	yellow();
	printf("nome_do_banco.nome_da_tabela\n\n");
	resetColor();
	
	printf("##Deletar ");
	printf("um (ou mais) dado(s) de uma tabela:\n\n ");
	green();
	printf("\tdelete from ");
	yellow();
	printf("nome_do_banco.nome_da_tabela ");
	green();
	printf("where (id == 4)\n\n");
	resetColor();

	printf("Digite ");
	boldRed();
	printf("exit ");
	resetColor();
	printf("para sair do programa.\n");
}

void printTable(Table table){
	cyan();
	printf("Selecting table ");
	resetColor();
	yellow();
	printf("%s ", table.name);
	resetColor();
	cyan();
	printf("from database ");
	resetColor();
	yellow();
	printf("%s", table.database);
	resetColor();
	cyan();
	printf(".\n");
	resetColor();
	/*
	*	O laço de repetição serve para printar da primeira até a última linha
	*/
	for(int i=0; i < table.numRows; i++){

		/*
		*	O laço a seguir encontra a maior string presente em uma coluna, e a armazena
		* 	em um vetor de strings.
		*/
		int* biggestStringOfACol = (int*)calloc(strlen(table.data[i][0]),sizeof(int*));
		for(int j=0; j < table.numCols; j++){

			for (int k=0; k < table.numRows; k++){

				if ((int)strlen(table.data[k][j]) < biggestStringOfACol[j]){
					continue;
				} else{
					biggestStringOfACol[j] = (int)strlen(table.data[k][j]);
				}
			}
		}
		/*
		*	se for o primeiro laço (i = 0) será printado duas linha para separar
		*	os itens de suas declaracões de tipos, uma em cima e outra em baixo,
		*	deixando mais fácil ao usuário de visualizar. Depois será printado as
		*	declarações do tipos das colunas.
		*/
		if(i==0){
			//	Printa uma linha sem valores
			for(int j=0; j < table.numCols+1; j++){
				resetColor();
				printf("|");
				if (j == table.numCols){
					continue;
				} else{
					int z = biggestStringOfACol[j];
					for (int k=0; k < z ;k++){	//Adiciona '=' até atingir o número da maior linha de uma coluna
						printf("=");
					}
			    }

			}
			//	Printa uma linha com a declaração dos tipos da coluna
			printf("\n");
			for(int j=0; j < table.numCols; j++){
				int z = biggestStringOfACol[j];
				resetColor();
				printf("|");
				magenta();
				printf("%s", table.data[0][j]);
				if (j == table.numCols-1){
					continue;
				} else{
					//Adiciona espaços até atingir o número da maior linha de uma coluna
					for (int k=0; k < z - (int)strlen(table.data[i][j]);k++){
						printf(" ");
					}
			    }
			}
			//	Printa uma linha sem valores
			printf("\n");
			for(int j=0; j < table.numCols+1; j++){
				resetColor();
				printf("|");
				if (j == table.numCols){
					continue;
				} else{
					int z = biggestStringOfACol[j];
					for (int k=0; k < z ;k++){
						printf("=");
					}
			    }

			}
		/*
		*	Caso não seja a primeira interação do laço, apenas as linhas, onde
		*	terão seus espaços, após sua escrita, adicionados baseados no tamannho
		*	da maior string de sua coluna.
		*/
		}else{
			for(int j=0; j < table.numCols; j++){
				resetColor();
				printf("|");
				yellow();
				printf("%s", table.data[i][j]);
				int z = biggestStringOfACol[j];
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
	if(findInVector("date ", data))return 1;
	
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
	/*
	*	commandCpy será uma variável do tipo string que copia o valor contido
	*	na posição da memória de command, pois a função strtok_r altera o valor
	*	contino na posição da memória da string que é recebida
	*/
	memcpy(commandCpy, command, strlen(command) + 1);
	commandCpy[strlen(command)+1]='\0';
	/*
	*	O laço de repetição checa se há um ponto antes do parêntesis, se sim
	*	a condição boleana isPointBeforeParenthesis será verdadeira. Se existir
	*	 um ponto antes do parêntesis, o endtoken e token vai cortar
	* 	o comando para depois dos parênteses garantindo que pontos dentro do 
	*	parênteses não sejam reconhecidos como nomes de bancos e tabelas.
	*/
	int isPointBeforeParenthesis=0;
	for(int i=0; i < (int)strlen(commandCpy);i++){
		if(commandCpy[i] == '.'){
			isPointBeforeParenthesis = 1;
			break;
		}
		if(commandCpy[i] == '('){
			break;
		}
	}
	char* endtoken = NULL;
	char* token = "";
	if (isPointBeforeParenthesis == 0){
		char* token2 = strtok_r(commandCpy, ")", &endtoken);
		token = concat(token, token2);
		token = strtok_r(NULL, ")", &endtoken);
	} else{
		token = concat(token, commandCpy);
	}
	/*
	*	O laço de estrutura vai ler o token até encontrar um ponto
	*/
	int pointFound=0;
	for(int i=0; i < (int)strlen(token); i++){
		if(token[i]=='.'){
			pointFound=1;
			//for regressivo até achar o espaço, irá printar ao contrário
			int cont=0;
			for(int j=i-1; token[j]!=' '; j--){
				database=(char*) realloc(database, cont*sizeof(char)+sizeof(char));
				database[cont]=token[j];
				cont++;
			}
			database=(char*) realloc(database, cont*sizeof(char)+sizeof(char));
			database[cont]='\0';
			cont=0;


			//for progressivo até achar o espaço
			for(int j=i+1; (token[j]!=' ' && token[j]!='\0'); j++){
				table=(char*) realloc(table, cont*sizeof(char)+sizeof(char));
				table[cont]=token[j];
				cont++;
			}
			table=(char*) realloc(table, cont*sizeof(char)+sizeof(char));
			table[cont]='\0';
			break;
		}
	}
	boldRed();
	resetColor();
	/*
	*	Caso um ponto não tenha sido encontrado, será retornado uma tabela 
	*	com nome da database e table = NULL
	*/
	if(!pointFound){
		boldGreen();
		resetColor();

		Table nullable;
		nullable.name=NULL;
		nullable.database=NULL;
		free(commandCpy);
		return nullable;
	/*
	*	Caso um ponto tenha sido encontrado, será retornado uma tabela com
	*	os valores do nome da database e table iguais aos encontrados pela
	*	função
	*/
	} else{
		int cont=0;
		database=invertString(database);
		
		t.name=(char*) malloc((int)strlen(table)*sizeof(char)+sizeof(char));
		t.database=(char*) malloc((int)strlen(database)*sizeof(char)+sizeof(char));
		t.name=table;
		t.database=database;
		free(commandCpy);
		return t;
	}
}	

/*
*	Irá receber só as colunas que irá printar,
*	a tabela filtrada e
*	os filtros
*/
void filterTable(char* columns, Table table, char* filters){

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

	/*
	*	Armazenam que linhas serão selecionadas (FILTROS)
	*
	*/
	if(filters!=NULL){
		Filter* filtersObj=calloc (1,sizeof(Filter));

		char *end_token1=NULL;
		int numberOfFilters=0;
		char *token1 = strtok_r(filters, ",", &end_token1);


		/*
		*	Irá popular todas as estruturas de filtro com os valores corretos
		*
		*/
		while(token1!=NULL){
			char *end_token2=NULL;			
			char *token2 = strtok_r(token1, " ", &end_token2);
			
			
			int contAux=0;
			while(token2!=NULL){
				/*
					contAux==0:
						filter.column
					contAux==1:
						filter.typeOfFilter
					contAux==2:
						filter.value
				*/
				if(contAux==0){
					filtersObj[numberOfFilters].column=(char*) calloc(strlen(token2)+1, sizeof(char));
					filtersObj[numberOfFilters].column=token2;
				}
				else if(contAux==1){
					filtersObj[numberOfFilters].typeOfFilter=(char*) calloc(strlen(token2)+1, sizeof(char));
					filtersObj[numberOfFilters].typeOfFilter=token2;
				}
				else if(contAux==2){
					filtersObj[numberOfFilters].value=(char*) calloc(strlen(token2)+1, sizeof(char));
					filtersObj[numberOfFilters].value=token2;
				}
				token2 = strtok_r(NULL, " ", &end_token2);
				contAux++;
			}

			token1 = strtok_r(NULL, ",", &end_token1);
			numberOfFilters++;
		}

		/*
		*	Valida se as colunas do filtro existem e popula o dado
		*	filteredColumn na estrutura de filtro
		*/
		int contAux=0;
		for(int i=0; i < numberOfFilters; i++){
			int hasValidType=0;
			for(int j=0; j<table.numCols; j++ ){
				if(strstr(table.data[0][j],filtersObj[i].column)){
					filtersObj[i].filteredColumn=j;
					hasValidType=1;
					contAux++;
				}
			}
			if(!hasValidType){
				hasInvalidType=1;
				break;
			}
		}

		/*
		*	Se não há nenhuma coluna inválida nos filtros
		*	populados acima
		*/
		if(!hasInvalidType){
			int rawRowsToPrint[99];
			int nLinesToVerify=0;
			/*
			*	Para cada linha da tabela original, passará o número de filtros por coluna
			*
			*/
			for(int i=1; i < table.numRows; i++){
				/*
				*	O próximo for populará um vetor de inteiros com todas as linhas que devem ser avaliadas
				*	
				*/
				for(int j=0; j < numberOfFilters; j++){
					/*
					*	Caso a coluna seja do tipo inteiro
					*
					*/
					if(strcmp(stringTillChar(table.data[0][filtersObj[j].filteredColumn], ' '), "int")==0){
						if(strcmp(filtersObj[j].typeOfFilter,">")==0){
							if(stringToInt(table.data[i][filtersObj[j].filteredColumn]) > stringToInt(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"<")==0){
							if(stringToInt(table.data[i][filtersObj[j].filteredColumn]) < stringToInt(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,">=")==0){
							if(stringToInt(table.data[i][filtersObj[j].filteredColumn]) >= stringToInt(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"<=")==0){
							if(stringToInt(table.data[i][filtersObj[j].filteredColumn]) <= stringToInt(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"==")==0){
							if(stringToInt(table.data[i][filtersObj[j].filteredColumn]) == stringToInt(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else{
							continue;
						}
					}

					/*
					*	Caso a coluna seja do tipo double
					*
					*/
					else if(strcmp(stringTillChar(table.data[0][filtersObj[j].filteredColumn], ' '), "double")==0){
						if(strcmp(filtersObj[j].typeOfFilter,">")==0){
							if(stringToDouble(table.data[i][filtersObj[j].filteredColumn]) > stringToDouble(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"<")==0){
							if(stringToDouble(table.data[i][filtersObj[j].filteredColumn]) < stringToDouble(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,">=")==0){
							if(stringToDouble(table.data[i][filtersObj[j].filteredColumn]) >= stringToDouble(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"<=")==0){
							if(stringToDouble(table.data[i][filtersObj[j].filteredColumn]) <= stringToDouble(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"==")==0){
							if(stringToDouble(table.data[i][filtersObj[j].filteredColumn]) == stringToDouble(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else{
							continue;
						}
					}

					/*
					*	Caso a coluna seja do tipo float
					*
					*/
					else if(strcmp(stringTillChar(table.data[0][filtersObj[j].filteredColumn], ' '), "float")==0){
						if(strcmp(filtersObj[j].typeOfFilter,">")==0){
							if(stringToFloat(table.data[i][filtersObj[j].filteredColumn]) > stringToFloat(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"<")==0){
							if(stringToFloat(table.data[i][filtersObj[j].filteredColumn]) < stringToFloat(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,">=")==0){
							if(stringToFloat(table.data[i][filtersObj[j].filteredColumn]) >= stringToFloat(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"<=")==0){
							if(stringToFloat(table.data[i][filtersObj[j].filteredColumn]) <= stringToFloat(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"==")==0){
							if(stringToFloat(table.data[i][filtersObj[j].filteredColumn]) == stringToFloat(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else{
							continue;
						}
					}

					/*
					*	Caso a coluna seja do tipo char
					*
					*/
					else if(strcmp(stringTillChar(table.data[0][filtersObj[j].filteredColumn], ' '), "char")==0){
						if(strcmp(filtersObj[j].typeOfFilter,">")==0){
							if(stringToChar(table.data[i][filtersObj[j].filteredColumn]) > stringToChar(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"<")==0){
							if(stringToChar(table.data[i][filtersObj[j].filteredColumn]) < stringToChar(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,">=")==0){
							if(stringToChar(table.data[i][filtersObj[j].filteredColumn]) >= stringToChar(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"<=")==0){
							if(stringToChar(table.data[i][filtersObj[j].filteredColumn]) <= stringToChar(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"==")==0){
							if(stringToChar(table.data[i][filtersObj[j].filteredColumn]) == stringToChar(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else{
							continue;
						}
					}

					/*
					*	Caso a coluna seja do tipo string
					*
					*/
					else if(strcmp(stringTillChar(table.data[0][filtersObj[j].filteredColumn], ' '), "string")==0){
						/*
						*	Busca por caseSensitive
						*/
						if(strcmp(filtersObj[j].typeOfFilter,"like")==0){
							char* auxString = betweenSymbols(filtersObj[j].value,'\'','\'');
							if(auxString[0]=='%' && auxString[strlen(auxString)-1]=='%'){
								auxString=removeCharsFromString(auxString, '%');
								if(strstr(table.data[i][filtersObj[j].filteredColumn], auxString)){
									rawRowsToPrint[nLinesToVerify]=i;
									nLinesToVerify++;
								}
							}else if(auxString[strlen(auxString)-1]=='%'){
								auxString=removeCharsFromString(auxString, '%');
								if(findInVector(auxString,table.data[i][filtersObj[j].filteredColumn])){
									rawRowsToPrint[nLinesToVerify]=i;
									nLinesToVerify++;
								}
							}else if(auxString[0]=='%' && auxString[strlen(auxString)]=='\0'){
								auxString=removeCharsFromString(auxString, '%');
								findInVectorReverse(auxString,table.data[i][filtersObj[j].filteredColumn]);
								if(findInVectorReverse(auxString,table.data[i][filtersObj[j].filteredColumn])){
									rawRowsToPrint[nLinesToVerify]=i;
									nLinesToVerify++;
								}
							}else if(auxString[0]!='%' && auxString[strlen(auxString)]=='\0'){
								auxString=removeCharsFromString(auxString, '%');
								findInVectorReverse(auxString,table.data[i][filtersObj[j].filteredColumn]);
								if(findInVectorReverse(auxString,table.data[i][filtersObj[j].filteredColumn])){
									rawRowsToPrint[nLinesToVerify]=i;
									nLinesToVerify++;
								}
							}else{
								continue;
							}
						/*
						*	Busca sem caseSensitive
						*/
						}else if(strcmp(filtersObj[j].typeOfFilter,"$like")==0){
							char* auxString = betweenSymbols(filtersObj[j].value,'\'','\'');
							auxString=lowerCase(auxString);
							if(auxString[0]=='%' && auxString[strlen(auxString)-1]=='%'){
								auxString=removeCharsFromString(auxString, '%');
								if(strstr(lowerCase(table.data[i][filtersObj[j].filteredColumn]), auxString)){
									rawRowsToPrint[nLinesToVerify]=i;
									nLinesToVerify++;
								}
							}else if(auxString[strlen(auxString)-1]=='%'){
								auxString=removeCharsFromString(auxString, '%');
								if(findInVector(auxString,lowerCase(table.data[i][filtersObj[j].filteredColumn]))){
									rawRowsToPrint[nLinesToVerify]=i;
									nLinesToVerify++;
								}
							}else if(auxString[0]=='%' && auxString[strlen(auxString)]=='\0'){
								auxString=removeCharsFromString(auxString, '%');
								findInVectorReverse(auxString,table.data[i][filtersObj[j].filteredColumn]);
								if(findInVectorReverse(auxString,lowerCase(table.data[i][filtersObj[j].filteredColumn]))){
									rawRowsToPrint[nLinesToVerify]=i;
									nLinesToVerify++;
								}
							}else if(auxString[0]!='%' && auxString[strlen(auxString)]=='\0'){
								auxString=removeCharsFromString(auxString, '%');
								findInVectorReverse(auxString,table.data[i][filtersObj[j].filteredColumn]);
								if(findInVectorReverse(auxString,lowerCase(table.data[i][filtersObj[j].filteredColumn]))){
									rawRowsToPrint[nLinesToVerify]=i;
									nLinesToVerify++;
								}
							}else{
								continue;
							}
																						
						}
					}
				}
			}
			int cont=0;
			contAux=0;
			filteredTable.numRows=0;

			/*
			*	Se tiver mais que uma linha para verificar, irá ver as ocorrências que se repetirem o 'numero de filtros' vezes,
			*	encontrando assim a interseção entre as linhas encontradas
			*/
			if(nLinesToVerify!=1){
				for(int i=1; i < nLinesToVerify + 1; i++){
					/*
					*	cont==numberOfFilters-1 
					*	pois desconsideramos a primeira ocorrência de um valor que se repetirá 
					*	(já que ainda não sabemos que ele irá se repetir o numero de vezes do filtro)
					*/
					if(cont==numberOfFilters-1){
						printableRows[contAux]=rawRowsToPrint[i-1];
						cyan();
						resetColor();
						cont=0;
						contAux++;
					}
					if(i!=0 && i!=nLinesToVerify){
						if(rawRowsToPrint[i]==rawRowsToPrint[i-1]){
							cont++;
						}else{
							cont=0;
						}
					}
				}
				filteredTable.numRows = contAux+1; //numero de linhas da tabela filtrada é igual ao numero de linhas filtradas + a assinatura
			}else{
				printableRows[0]=rawRowsToPrint[0];
				filteredTable.numRows=2;
			}
		}else{
			boldRed();
			printf("Algumas colunas de filtro são inválidas!\n");
			resetColor();
		}
	}else{
		filteredTable.numRows=table.numRows;
	}
	/**/


	/*
	*	Popula uma tabela com quais linhas e colunas serão mostradas
	*
	*/
	if(strcmp(columns, "*")==0){ //==0 significa que são iguais
		/*
		* 	Caso o usuário tenha escolhido todas as colunas
		*
		*/
		filteredTable.numCols = table.numCols;
		if(filteredTable.numRows != table.numRows){
			for(int i=0; i < filteredTable.numRows; i++){ 
				filteredTable.data[i]=(char**) calloc(filteredTable.numCols, sizeof(char**));

				for(int j=0; j < filteredTable.numCols; j++){
					if(i==0){
						filteredTable.data[i][j] = table.data[i][j];
					}else{
						filteredTable.data[i][j] = table.data[printableRows[i-1]][j];
					}
				}
			}
		}else{
			filteredTable=table;
		}
	}else{
		char *end_token=NULL;
		char *token = strtok_r(columns, ",", &end_token);

		/*
		*	Verifica quais colunas devem ser printadas, populando um vetor de inteiro com esses endereços
		*
		*/
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
			}
			if(!columnFound){
				columnNotFound=1;
			}
			token = strtok_r(NULL, ",", &end_token); 
		}
		

		/*
		*	Se tudo foi corretamente validado para as colunas, então populará uma tabela com as colunas corretas
		*
		*/
		if(!columnNotFound){
			if(filteredTable.numRows != table.numRows){
				for(int i=0; i < filteredTable.numRows; i++){
					printf("880\n"); 
					filteredTable.data[i]=(char**) calloc(filteredTable.numCols, sizeof(char**));

					for(int j=0; j < filteredTable.numCols; j++){
						if(i==0){
							filteredTable.data[i][j] = table.data[i][j];
						}else{
							filteredTable.data[i][j] = table.data[printableRows[i-1]][j];
						}
					}
				}
			}else{
				printf("893\n"); 
				for(int i=0; i<filteredTable.numRows; i++){
					int cont=0;
					filteredTable.data[i]=(char**) calloc(filteredTable.numCols, sizeof(char**));
					for(int j=0; j<filteredTable.numCols; j++){
						filteredTable.data[i][cont] = table.data[i][printableCollums[j]];
						cont++;
					}
				}
			}
		}else{
			boldRed();
			printf("Não é possível fazer a seleção da tabela. Alguma das colunas passadas por parâmetro não existem.\n");
			resetColor();
		}
	}
	/**/

	boldCyan();

	if(!columnNotFound && !hasInvalidType){
		printTable(filteredTable);
	}
}

void deleteFromTable(char* columns, Table table, char* filters){

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

	/*Armazenam que linhas serão selecionadas (FILTRO)*/
	if(filters!=NULL){
		printf("Filters!=NULL\n");
		Filter* filtersObj=calloc (1,sizeof(Filter));

		char *end_token1=NULL;
		int numberOfFilters=0;
		char *token1 = strtok_r(filters, ",", &end_token1);



		while(token1!=NULL){
			char *end_token2=NULL;			
			char *token2 = strtok_r(token1, " ", &end_token2);
			
			
			int contAux=0;
			while(token2!=NULL){
				/*
					contAux==0:
						filter.column
					contAux==1:
						filter.typeOfFilter
					contAux==2:
						filter.value
				*/

				if(contAux==0){
					filtersObj[numberOfFilters].column=(char*) calloc(strlen(token2)+1, sizeof(char));
					filtersObj[numberOfFilters].column=token2;
				}
				else if(contAux==1){
					filtersObj[numberOfFilters].typeOfFilter=(char*) calloc(strlen(token2)+1, sizeof(char));
					filtersObj[numberOfFilters].typeOfFilter=token2;
				}
				else if(contAux==2){
					filtersObj[numberOfFilters].value=(char*) calloc(strlen(token2)+1, sizeof(char));
					filtersObj[numberOfFilters].value=token2;
				}
				token2 = strtok_r(NULL, " ", &end_token2);
				contAux++;
			}

			token1 = strtok_r(NULL, ",", &end_token1);
			numberOfFilters++;
		}

		/*
			Valida se as colunas do filtro existem
		*/
		int contAux=0;
		for(int i=0; i < numberOfFilters; i++){
			int hasValidType=0;
			for(int j=0; j<table.numCols; j++ ){
				if(strstr(table.data[0][j],filtersObj[i].column)){
					filtersObj[i].filteredColumn=j;
					hasValidType=1;
					contAux++;
				}
			}
			if(!hasValidType){
				hasInvalidType=1;
				break;
			}
		}

		if(!hasInvalidType){


			//empilhará todas as linhas que se enquadram com cada filtro (deverá ainda ter uma interseção para as operações)
			int rawRowsToPrint[99];
			int nLinesToVerify=0;
			for(int i=1; i < table.numRows; i++){
				for(int j=0; j < numberOfFilters; j++){
					if(strcmp(stringTillChar(table.data[0][filtersObj[j].filteredColumn], ' '), "int")==0){
						if(strcmp(filtersObj[j].typeOfFilter,">")==0){
							if(stringToInt(table.data[i][filtersObj[j].filteredColumn]) > stringToInt(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"<")==0){
							if(stringToInt(table.data[i][filtersObj[j].filteredColumn]) < stringToInt(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,">=")==0){
							if(stringToInt(table.data[i][filtersObj[j].filteredColumn]) >= stringToInt(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"<=")==0){
							if(stringToInt(table.data[i][filtersObj[j].filteredColumn]) <= stringToInt(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"==")==0){
							if(stringToInt(table.data[i][filtersObj[j].filteredColumn]) == stringToInt(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else{
							continue;
						}
					}

					else if(strcmp(stringTillChar(table.data[0][filtersObj[j].filteredColumn], ' '), "double")==0){
						if(strcmp(filtersObj[j].typeOfFilter,">")==0){
							if(stringToDouble(table.data[i][filtersObj[j].filteredColumn]) > stringToDouble(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"<")==0){
							if(stringToDouble(table.data[i][filtersObj[j].filteredColumn]) < stringToDouble(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,">=")==0){
							if(stringToDouble(table.data[i][filtersObj[j].filteredColumn]) >= stringToDouble(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"<=")==0){
							if(stringToDouble(table.data[i][filtersObj[j].filteredColumn]) <= stringToDouble(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"==")==0){
							if(stringToDouble(table.data[i][filtersObj[j].filteredColumn]) == stringToDouble(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else{
							continue;
						}
					}

					else if(strcmp(stringTillChar(table.data[0][filtersObj[j].filteredColumn], ' '), "float")==0){
						if(strcmp(filtersObj[j].typeOfFilter,">")==0){
							if(stringToFloat(table.data[i][filtersObj[j].filteredColumn]) > stringToFloat(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"<")==0){
							if(stringToFloat(table.data[i][filtersObj[j].filteredColumn]) < stringToFloat(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,">=")==0){
							if(stringToFloat(table.data[i][filtersObj[j].filteredColumn]) >= stringToFloat(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"<=")==0){
							if(stringToFloat(table.data[i][filtersObj[j].filteredColumn]) <= stringToFloat(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"==")==0){
							if(stringToFloat(table.data[i][filtersObj[j].filteredColumn]) == stringToFloat(filtersObj[j].value)){
								rawRowsToPrint[nLinesToVerify]=i;
								nLinesToVerify++;
							}
						}else{
							continue;
						}
					}

					else if(strcmp(stringTillChar(table.data[0][filtersObj[j].filteredColumn], ' '), "string")==0){
						if(strcmp(filtersObj[j].typeOfFilter,"like")==0){
							char* auxString = betweenSymbols(filtersObj[j].value,'\'','\'');
							if(auxString[0]=='%' && auxString[strlen(auxString)-1]=='%'){
								auxString=removeCharsFromString(auxString, '%');
								if(strstr(table.data[i][filtersObj[j].filteredColumn], auxString)){
									rawRowsToPrint[nLinesToVerify]=i;
									nLinesToVerify++;
								}
							}else if(auxString[strlen(auxString)-1]=='%'){
								auxString=removeCharsFromString(auxString, '%');
								if(findInVector(auxString,table.data[i][filtersObj[j].filteredColumn])){
									rawRowsToPrint[nLinesToVerify]=i;
									nLinesToVerify++;
								}
							}else if(auxString[0]=='%' && auxString[strlen(auxString)]=='\0'){
								auxString=removeCharsFromString(auxString, '%');
								findInVectorReverse(auxString,table.data[i][filtersObj[j].filteredColumn]);
								if(findInVectorReverse(auxString,table.data[i][filtersObj[j].filteredColumn])){
									rawRowsToPrint[nLinesToVerify]=i;
									nLinesToVerify++;
								}
							}else if(auxString[0]!='%' && auxString[strlen(auxString)]=='\0'){
								auxString=removeCharsFromString(auxString, '%');
								findInVectorReverse(auxString,table.data[i][filtersObj[j].filteredColumn]);
								if(findInVectorReverse(auxString,table.data[i][filtersObj[j].filteredColumn])){
									rawRowsToPrint[nLinesToVerify]=i;
									nLinesToVerify++;
								}
							}else{
								continue;
							}
						}else if(strcmp(filtersObj[j].typeOfFilter,"&like")==0){
							char* auxString = betweenSymbols(filtersObj[j].value,'\'','\'');
							auxString=lowerCase(auxString);
							if(auxString[0]=='%' && auxString[strlen(auxString)-1]=='%'){
								auxString=removeCharsFromString(auxString, '%');
								if(strstr(lowerCase(table.data[i][filtersObj[j].filteredColumn]), auxString)){
									rawRowsToPrint[nLinesToVerify]=i;
									nLinesToVerify++;
								}
							}else if(auxString[strlen(auxString)-1]=='%'){
								auxString=removeCharsFromString(auxString, '%');
								if(findInVector(auxString,lowerCase(table.data[i][filtersObj[j].filteredColumn]))){
									rawRowsToPrint[nLinesToVerify]=i;
									nLinesToVerify++;
								}
							}else if(auxString[0]=='%' && auxString[strlen(auxString)]=='\0'){
								auxString=removeCharsFromString(auxString, '%');
								findInVectorReverse(auxString,table.data[i][filtersObj[j].filteredColumn]);
								if(findInVectorReverse(auxString,lowerCase(table.data[i][filtersObj[j].filteredColumn]))){
									rawRowsToPrint[nLinesToVerify]=i;
									nLinesToVerify++;
								}
							}else if(auxString[0]!='%' && auxString[strlen(auxString)]=='\0'){
								auxString=removeCharsFromString(auxString, '%');
								findInVectorReverse(auxString,table.data[i][filtersObj[j].filteredColumn]);
								if(findInVectorReverse(auxString,lowerCase(table.data[i][filtersObj[j].filteredColumn]))){
									rawRowsToPrint[nLinesToVerify]=i;
									nLinesToVerify++;
								}
							}else{
								continue;
							}
																						
						}
					}
				}
			}
			int cont=0;
			contAux=0;
			filteredTable.numRows=0;
			if(nLinesToVerify!=1){
				for(int i=1; i < nLinesToVerify + 1; i++){
					/*
						cont==numberOfFilters-1 
						pois desconsideramos a primeira ocorrência de um valor que se repetirá 
						(já que ainda não sabemos que ele irá se repetir o numero de vezes do filtro)
					*/
					if(cont==numberOfFilters-1){
						printableRows[contAux]=rawRowsToPrint[i-1];
						cyan();
						resetColor();
						cont=0;
						contAux++;
					}
					if(i!=0 && i!=nLinesToVerify){
						if(rawRowsToPrint[i]==rawRowsToPrint[i-1]){
							cont++;
						}else{
							cont=0;
						}
					}
				}
				filteredTable.numRows = contAux+1; //numero de linhas da tabela filtrada é igual ao numero de linhas filtradas
			}else{
				printableRows[0]=rawRowsToPrint[0];
				filteredTable.numRows=2;
			}
		}else{
			boldRed();
			printf("Algumas colunas de filtro são inválidas!\n");
			resetColor();
		}
	}else{
		filteredTable.numRows=table.numRows;
	}
	/**/


	/*Popula uma tabela com quais linhas e colunas serão mostradas*/
	filteredTable.numCols = table.numCols;
	int cont=0;
	int lastLineChecked=0;
	if(filteredTable.numRows != table.numRows){
		for(int i=0; i < table.numRows; i++){
			if(i==0){
				filteredTable.data[cont]=(char**) calloc(filteredTable.numCols, sizeof(char**));
				for(int j=0; j < filteredTable.numCols; j++){
					filteredTable.data[cont][j]=table.data[i][j];
				}
				cont++;
			}else{
				int shouldPrint=1;
				for(int j=0; j< filteredTable.numRows; j++){
					if(i==printableRows[j]){
						shouldPrint=0;
					}
				}
				if(shouldPrint){
					filteredTable.data[cont]=(char**) calloc(filteredTable.numCols, sizeof(char**));
					for(int j=0; j < filteredTable.numCols; j++){
						filteredTable.data[cont][j]=table.data[i][j];
					}
					cont++;
				}
			}
		}
		filteredTable.numRows=table.numRows-(filteredTable.numRows-1);
	}else{
		filteredTable=table;
	}

	boldCyan();

	if(!columnNotFound && !hasInvalidType){
		replaceTable(filteredTable);
		printTable(filteredTable);
	}
}

void validateSelect(char* command){
	char* commandTemp=(char*) calloc (strlen(command)+1, sizeof(char)); 
	memcpy(commandTemp, command, strlen(command)+1);
	
	char *end_str=NULL;
    char *token = strtok_r(command, " ", &end_str);

	char** commands=(char**) calloc(20, sizeof(char**));
	int cont=0;
	while (token != NULL){
		char *end_token=NULL;
		commands[cont]=token;
		token = strtok_r(NULL, " ", &end_str);
		cont++;
	}
	char* collumns=NULL;
	char* filters=NULL;

	/*
	*	Caso todas as colunas sejam desejadas
	*
	*/
	if(strcmp(commands[1], "*")==0){
		collumns=(char*) calloc (2, sizeof(char));
		collumns="*";

		/*
		*	Caso tenham sido passados filtros no comando
		*
		*/
		if(strstr(commandTemp, " where ")){
			filters = malloc( strlen(betweenParenthesis(commandTemp))*sizeof(char)+sizeof(char));
			filters = betweenParenthesis(commandTemp);
			filters = removeSpacesAfterCommas(filters);
		}
	}else{

		collumns = malloc( strlen(betweenParenthesis(commandTemp))*sizeof(char)+sizeof(char));
		collumns = betweenParenthesis(commandTemp);
		collumns =  removeSpacesAfterCommas(collumns);

		/*
		*	Tira os primeiros parênteses do select e usa os últimos como
		*	filtro select -()- where *()* 
		*/
		if(strstr(commandTemp, " where ")){
			int findOpenningP=0;
			int findClosingP=0;
			for(int i=0; i<(int)strlen(commandTemp); i++){
				if(commandTemp[i]=='('){
					commandTemp[i]='-';
					findOpenningP=1;
				}else if(commandTemp[i]==')'){
					commandTemp[i]='-';
					findClosingP=1;
				}else if(findOpenningP && findClosingP){
					break;
				}
			}
			filters = malloc( strlen(betweenParenthesis(commandTemp))*sizeof(char)+sizeof(char));
			filters = betweenParenthesis(commandTemp);
			filters = removeSpacesAfterCommas(filters);
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

	/*
	*	Se o banco é válido com os dados passados por parâmetro
	*/
	if(t.database!=NULL){
		filterTable(collumns, t, filters);
	}else{
		boldRed();
		printf("Você não selecionou nenhum banco de dados válido. Reescreva o comando. \n");
		resetColor();
	}
	
}

void validateDeleteFrom(char* command){
	boldCyan();
	resetColor();
	char* commandTemp=(char*) calloc (strlen(command)+1, sizeof(char)); 
	memcpy(commandTemp, command, strlen(command)+1);
	boldCyan();
	resetColor();
	
	char *end_str=NULL;
    char *token = strtok_r(command, " ", &end_str);

	boldCyan();
	resetColor();

	char** commands=(char**) calloc(20, sizeof(char**));
	int cont=0;
	while (token != NULL){
		char *end_token=NULL;
		commands[cont]=token;
		token = strtok_r(NULL, " ", &end_str);
		cont++;
	}
	boldCyan();
	resetColor();
	char* collumns=NULL;
	char* filters=NULL;
	collumns=(char*) calloc (2, sizeof(char));
	collumns="*";
	if(strstr(commandTemp, "where")){
		filters = malloc( strlen(betweenParenthesis(commandTemp))*sizeof(char)+sizeof(char));
		filters = betweenParenthesis(commandTemp);
		filters = removeSpacesAfterCommas(filters);
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
		deleteFromTable(collumns, t, filters);
	}else{
		boldRed();
		printf("Você não selecionou nenhum banco de dados válido. Reescreva o comando. \n");
		resetColor();
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
				//	Conta o número de colunas que há na string
				for(int i=0;i < (int)strlen(string) ;i++){
					if (string[i] == '|'){
						table.numCols++;
					}
				}
				//	Define o valor para table.data[0][x], onde x é a posição na coluna;
				table.data  = (char***)calloc(1,sizeof(char**));
				table.data[0] = (char**)calloc(table.numCols,sizeof(char*));

				//	Define o valor do token e a sua quebra que será usado pela função strok_r;
				char *end_token=NULL;
				char *token = strtok_r(string, "|", &end_token);
				
				//	Transforma o valor de table.data[0][i] no valor do token
				for (int i=0; i < table.numCols; i++){;
					table.data[0][i] = token;
					token = strtok_r(NULL, "|", &end_token); // Define token como o valor após '|'
				}
				//	free(token);
				//	Chama a função void insertIntoTable mandando a table criada.
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

void validateDropDatabase(char* string){

	Database database;
	database.name = wordInPositionAfterSeparations(string, " ", 2);

	dropDatabase(database);
}

void validateDropTable(char* string){
	if (isInString(string, '.') == 1){
		Table table;
		/*
		*	findTableInCommand, retorna o nome e o banco de dados 
		*	de uma table por meio de um comando
		*/
		table = findTableInCommand(string);

		dropTable(table);
	} else{
		boldRed();
		printf("Erro na abertura, a tabela nao foi especificada");
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
// | INSERIR COMENTÁRIO | INSERIR COMENTÁRIO | INSERIR COMENTÁRIO |
int execute(char* command);

void externalInstructions(char* command){
	char* pathToFile=NULL;

	int spaces=0;
	int cont=0;
	for(int i=0; i< (int)strlen(command); i++){
		if(command[i]==' ' && !spaces){
			spaces++;
		}

		if(spaces == 1 && command[i]!=' '){
			pathToFile = (char*) realloc (pathToFile, cont*sizeof(char) + sizeof(char));
			pathToFile[cont]=command[i];
			cont++;
		}
	}
	pathToFile = (char*) realloc (pathToFile, cont*sizeof(char) + sizeof(char));
	pathToFile[cont]='\0';
	
	FILE *file;
	file = fopen( pathToFile, "r" );
	char ch;

	int fileOpen=0;

	char* tempCommand= malloc(255*sizeof(char));
	if( file == NULL ) {
		boldRed();
		printf( "Erro na abertura do arquivo! Você digitou corretamente?\n" );
		resetColor();
	}else{
		int count=0;
		while( fgets(tempCommand, 255, file) ){ 
			magenta();
			printf("Executanto o comando:\n");
			resetColor();
			boldCyan();
			printf("%s",tempCommand);
			resetColor();
			execute(tempCommand);
			count++;
		}
		fileOpen=1;
	}
	if(fileOpen==1){
		fclose(file);
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

	}else if(findInVector("test", command)){
		
	}else if(findInVector("insert ", command)){
		printf("Inserting into table\n");
		validateInsertIntoTable(command);


	}else if(findInVector("drop table ", command)){
		validateDropTable(command);

	}else if(findInVector("drop database ", command)){
		validateDropDatabase(command);

	}else if(findInVector("delete from ", command)){
		validateDeleteFrom(command);

	}else if(findInVector("select ", command)){
		validateSelect(command);


	}else if(findInVector("list tables", command)){
		listAllTables();

	}else if(findInVector("import ", command)){
		externalInstructions(command);
	}else if(findInVector("clear", command)){
		system("clear");
		commandVersion();
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

	for(int i=(int)strlen(db.name); i > (int) strlen(db.name); i--){
		if(db.name[i]==' '){
			db.name[i]='\0';
		}
	}
	return db;
}
