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
#include <dirent.h>

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
		printf("Um banco com este nome já existe. Não será criada um novo.\n\n");
		resetColor();
	}
}

void selectFromTable();

void createTable(Table table){
	struct stat st = {0};
	char* path= NULL;
	path = concat("dbs/", table.database); //concatena o nome do banco com a pasta onde ele será armazenado
	printf("Caminho do banco: ");
	yellow();
	printf("%s/", path);
	resetColor();
	printf("\n");
	if (stat(path, &st) == -1) { //verifica a existência do arquivo
	    boldRed();
		printf("Não há um banco com esse nome. A tabela não será criada!\n");
		resetColor();
		free(path);
	}else{
		yellow();
		printf("Um banco com este nome existe. Inserindo em ");
		green();
		printf("%s.\n", table.database);
		resetColor();

		char* fileName= concat(concat(path,"/"),concat(table.name, ".csv"));
		printf("filename:  %s\n", fileName);
		FILE *fptr;
		fptr = fopen(fileName, "rb+");
		if (stat(fileName, &st) == -1){
			printf("Uma tabela com o nome ");
			boldGreen();
			printf("%s", table.name);
			resetColor();
			printf(" será criada.\n");
		}else{
			boldRed();
			printf("Uma tabela com o nome ");
			yellow();
			printf("%s", table.name);
			boldRed();
			printf(" já existe.\nNão será criada uma nova.\n");
			resetColor();
		}
		if(fptr == NULL){ //if file does not exist, create it
			fptr = fopen(fileName, "w+");
			for(int i=0; i<table.numCols; i++){
				fprintf(fptr, "%s", table.data[0][i]);
				if(i<table.numCols-1){
					fprintf(fptr, "|");
				}
			}
			fprintf(fptr,"\n");
			fclose( fptr );
		}

	}
}

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
			if(ch == '|'){
				cols++;
			}else if(ch == '\n'){
				break;
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

	int fileOpen=0;

	if( file == NULL ) {
		boldRed();
		printf( "Erro na abertura do arquivo! Você digitou corretamente?\n" );
		Table table;
		table.database=NULL;
		resetColor();
		return table;
	}else{
		int count=0;
		while((ch=fgetc(file))!=EOF){ //igualar ch ao fgetc(file) até atingir EOF (fim do arquivo)
			wholeFile=realloc(wholeFile, count*sizeof(char) + sizeof(char));
			wholeFile[count]=ch;
			count++;
		}
		wholeFile=realloc(wholeFile, count*sizeof(char) + sizeof(char));
		wholeFile[count]='\0';
		fileOpen=1;
	}
	if(fileOpen==1){
		fclose(file);
	}

	if(fileOpen){
		Table table;
		table.name = "TODO";
		table.database = "TODO";
		table.numRows=countRowsInCsv(pathToFile);
		table.numCols=countColsInCsv(pathToFile);
		
		int count=0;
		table.data=(char***) calloc(table.numRows, sizeof(char***));

		char *end_str=NULL;
		char *token = strtok_r(wholeFile, "\n", &end_str); //separa os dados para cada \n

		int row=0;
		int col=0;

		while (token != NULL){

			table.data[row]=(char**) calloc(table.numCols, sizeof(char**));
			char *end_token=NULL;
			char *token2 = strtok_r(token, "|", &end_token); //separa os dados a cada ,

			while (token2 != NULL){

				table.data[row][col] = token2;

				token2 = strtok_r(NULL, "|", &end_token);

				col++;
				
			// printf("table.data[%i][%i] = %s\n",row,col,table.data[row][col]);

			}
			col=0;
			row++;
			token = strtok_r(NULL, "\n", &end_str);	
		}
		return table;
	}
}

int isRegularFile(const char *path){
	struct stat buffer;
   	if (stat(path, &buffer) != 0)
    	return 0;
   	return S_ISREG(buffer.st_mode);
}

int isDirectory(const char *path){
	struct stat buffer;
   	if (stat(path, &buffer) != 0)
    	return 0;
   	return S_ISDIR(buffer.st_mode);
}

void listFilesInFolder(char* pathToFolder){
	DIR *dir;
    struct dirent *dp;
    char * file_name;
    dir = opendir(pathToFolder);
    while ((dp=readdir(dir)) != NULL) {
        //printf("debug: %s\n", dp->d_name);
        if ( !strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..") ){
            // do nothing (straight logic)
        } else {
			green();
            file_name = dp->d_name; 
            printf("├──%s\n",file_name);
			resetColor();
        }
    }
    closedir(dir);
}

void listAllTables(){
	cyan();
	printf("\n======|Bancos e suas tabelas|======\n\n");
    resetColor();
	DIR *dir;
    struct dirent *dp;
    char * file_name;
	char* pathToFile;
    dir = opendir("dbs");
    while ((dp=readdir(dir)) != NULL) {
        //printf("debug: %s\n", dp->d_name);
        if ( !(!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) ){
            file_name = dp->d_name; 
			pathToFile = "dbs/";
			pathToFile = concat(pathToFile, file_name);
			magenta();
			printf("%s\n", dp->d_name );
			resetColor();
			if(isDirectory(pathToFile)){
				listFilesInFolder(pathToFile);
			}
			printf("\n");
			resetColor();
        }
    }
    closedir(dir);
}

void insertIntoTable(Table table){
	FILE *file;
	char* path = "/";
	concat(path, table.database);
	file = fopen(path, "r");
	if( file == NULL ) {
		boldRed();
		printf( "Erro: biblioteca não existente\n" );
		resetColor();
	} else{
		fclose(file);
		concat(path, "/");
		concat(path, table.name);
		concat(path, ".csv");
		file = fopen(path, "wr");
		printf("ABRIU O ARQUIVO EM: %s", path);
		if(file == NULL){
			boldRed();
			printf( "Erro na abertura do arquivo! Você digitou corretamente?\n" );
			resetColor();
		} else{
			Table csvTable = csvToTable(path);

		}
	}

}
    // if (isInString(string,'|') == 0){
	//     char* stringNew = (char*)calloc((int)strlen(string),sizeof(char));
	// 	int stringNewCols = 0;
	// 	if (isInString(string,'"') == 1){
	// 		stringNew = switchCommaToVerticalBarWithQMarks(string);
	// 		for(int i=0; i <= (int)strlen(stringNew); i++){
	// 			if(stringNew[i] == '|'){
	// 			stringNewCols++;
	// 			}
	// 	    }
	// 	} else{
	// 		stringNew = switchCommaToVerticalBar(string);
	// 		for(int i=0; i <= (int)strlen(stringNew); i++){
	// 			if(stringNew[i] == '|'){
	// 			stringNewCols++;
	// 			}
	// 	    }

	// 	}
	// 	if(stringNewCols == (int)countColsInCsv(pathToFile)){
	// 		fwrite (stringNew, 1, sizeof(stringNew), file);
	// 		fclose(file);
	// 	} else{
	// 		boldRed();
	// 		printf("Erro: O numero de itens esperado era: %d, voce digitou: %d\n", (int)countColsInCsv(pathToFile), stringNewCols);
	// 		resetColor();
	// 	}
	// 	free(stringNew);
	// }else {
	// 	boldRed();
	// 	printf("Erro: Caractere especial '|' nao suportado\n");
	// 	resetColor();
	// }