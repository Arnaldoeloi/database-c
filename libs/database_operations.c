#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database_types.h"
#include "strings.h"
#include "colors.h"

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
	printf("Caminho do banco: ");
	yellow();
	printf("%s/", path);
	resetColor();
	printf("\n");
	if (stat(path, &st) == -1) { //verifica a existência do arquivo
	    if(mkdir(path, 0777)==-1){ //cria o arquivo com permissão 0777
			boldRed();
			printf("Ocorreu um problema, tente criar com outro nome ou execute o programa com privilegios de administrador.");
			perror("mkdir");
			resetColor();
		}else{
			boldGreen();
			printf("Banco criado.\n\n");
			resetColor();
		}
		free(path);
	}else{
		boldRed();
		printf("Um banco com este nome já existe. Não será criada uma nova.\n\n");
		resetColor();
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

int countColsInCsv(char* pathToFile){
	int cols=0;
	char ch;
	FILE *arq;
	arq = fopen(pathToFile, "r");
	if(arq == NULL)
		return -1;
	else{
		while( (ch=fgetc(arq))!= EOF ){
			if(ch == ','){
				cols++;
			}
		}
	}
	fclose(arq);
	return cols+1;
}


Table csvToTable(char* pathToFile){
	FILE *file;
	file = fopen( pathToFile, "r" );
	char ch;
	char* wholeFile=NULL;	

	if( file == NULL ) {
		boldRed();
		printf( "Erro na abertura do arquivo!\n" );
		resetColor();
	}else{
		int count=0;
		while((ch=fgetc(file))!=EOF){ //igualar ch ao fgetc(file) até atingir EOF (fim do arquivo)
			wholeFile=realloc(wholeFile, count*sizeof(char) + sizeof(char));
			wholeFile[count]=ch;
			count++;
		}
		wholeFile=realloc(wholeFile, count*sizeof(char) + sizeof(char));
		wholeFile[count]='\0';
	}
	fclose(file);

	
	Table table;
	table.name = "TODO";
	table.database = "TODO";
	table.numRows=countRowsInCsv(pathToFile);
	table.numCols=countColsInCsv(pathToFile);
	
	int count=0;
	table.data=(char***) calloc(1, sizeof(char***));

	char *end_str=NULL;
    char *token = strtok_r(wholeFile, "\n", &end_str); //separa os dados para cada \n

	int row=0;
	int col=0;
    while (token != NULL){
		table.data[row]=(char**) calloc(1, sizeof(char**));
        char *end_token=NULL;
        printf("NOVOS DADOS = %s\n", token);
        char *token2 = strtok_r(token, ",", &end_token); //separa os dados a cada ,
        while (token2 != NULL){
			table.data[row][col]=(char*)malloc(strlen(token2)*sizeof(char));
			table.data[row][col]=token2;
            printf("table.data[%i][%i] = %s\n",row,col, table.data[row][col]);
            token2 = strtok_r(NULL, ",", &end_token);
			col++;
        }
		col=0;
		row++;
        token = strtok_r(NULL, "\n", &end_str);
		
    }
	return table;
}


/*
	Table usuarios;
	usuarios.name = "usuarios";
	usuarios.database = "escola";
	usuarios.collums = "id,nome,senha,e-mail";
	usuarios.data = (char***) calloc(1, sizeof(char***));

	usuarios.data[0]=(char**) calloc(1, sizeof(char**));
	usuarios.data[0][0] = "Arnaldo";
	usuarios.data[0][1] = "(84) 9 9381-8314";
	
	usuarios.data[1]=(char**) calloc(1, sizeof(char**));
	usuarios.data[1][0] = "Claudinho batata";
	usuarios.data[1][1] = "(42) 9 8474-0238";

	// usuarios.data[2][0] = "Nathanael DeRico";
	// usuarios.data[2][1] = "(42) 9 9374-1637";

	// usuarios.data[3][0] = "Pedro boca de batata";
	// usuarios.data[3][1] = "(42) 9 3223-4707";

	// usuarios.data[4][0] = "Marjory Marjority";
	// usuarios.data[4][1] = "(22) 8 3441-2101";

	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			printf("%3s",usuarios.data[i][j]);
		}	
		printf("\n");
	}
	return 0;
*/
