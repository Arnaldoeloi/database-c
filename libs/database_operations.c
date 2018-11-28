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

void createTable(Table table){
	struct stat st = {0}; //buffer do stat
	char* path= NULL;
	path = concat("dbs/", table.database); //concatena o nome do banco com a pasta onde ele será armazenado
	printf("Caminho do banco: ");
	yellow();
	printf("%s/", path);
	resetColor();
	printf("\n");
	if (stat(path, &st) == -1) { //verifica a existência da pasta com o nome do banco
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
		printf("Nome do arquivo da tabela:  %s\n", fileName);
		FILE *fptr;
		fptr = fopen(fileName, "rw"); //abrirá o arquivo com permissão de leitura e escrita
		if (stat(fileName, &st) == -1){ //stat(caminho_do_arquivo, buffer) retorna -1 se o arquivo não existir no diretório, é o que queremos
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
		if(fptr == NULL){ //fptr será nulo se não existir nenhum arquivo com esse nome no diretório
			fptr = fopen(fileName, "w+");
			for(int i=0; i<table.numCols; i++){
				fprintf(fptr, "%s", table.data[0][i]); //para cada dado da matrix de strings, printa o dado no arquivo
				if(i<table.numCols-1){
					fprintf(fptr, "|"); //adicionado o separador
				}
			}
			fprintf(fptr,"\n"); //adiciona o \n, indicando que a linha acabou
			fclose( fptr );	//fecha o arquivo
		}

	}
}

void deleteFromTable();
void alterTableModify();
void alterTableDrop();
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
		table.database = betweenSymbols(pathToFile,'/','/');
		table.name = betweenSymbols(betweenSymbols(pathToFile,'/','.'), '/','\0');
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

int isRegularFile(char *path){
	struct stat buffer;
   	if (stat(path, &buffer) != 0) //caso dê erro de leitura, retornará que não se trata de um arquivo 
    	return 0;
	//garante que, se não der erro, retornará se é arquivo ou não
   	return S_ISREG(buffer.st_mode); //st_mode retorna a permissão de acesso ao arquivo
}

int isDirectory(char *path){
	struct stat buffer;
   	if (stat(path, &buffer) != 0) //caso dê erro de leitura, retornará que não se trata de um diretório 
    	return 0;
	//garante que, se não der erro, retornará se é diretório ou não
   	return S_ISDIR(buffer.st_mode); 
}

void listFilesInFolder(char* pathToFolder){
	DIR *dir; //ponteiro do to tipo DIR (diretório)
    struct dirent *dp; //struct do tipo dirent (diretório), traz a possibilidade de verificar alguns dados do arquivo, como nome e extensão
    char * file_name;
    dir = opendir(pathToFolder);

	//enquanto não tentar ler um diretório/arquivo nulo, listará os arquivos
    while ((dp=readdir(dir)) != NULL) { 
		/*
			o if garante que não serão printados os caminhos de volta (.) 
			e nem de duas voltas (..). Caso não houvesse o IF, seriam printados
			todos as pastas para cada saída do caminho de um banco 
		*/
        if ( !(!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) ){
			green();
            file_name = dp->d_name;  
            printf("├──%s\n",file_name); //printa o nome do arquivo em formato de árvore
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
		/*
			o if garante que não serão printados os caminhos de volta (.) 
			e nem de duas voltas (..). Caso não houvesse o IF, seriam printados
			todos as pastas para cada saída do caminho de um banco 
		*/ 
        if ( !(!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) ){
            file_name = dp->d_name; 
			pathToFile = "dbs/";
			pathToFile = concat(pathToFile, file_name);
			magenta();
			printf("%s\n", dp->d_name );
			resetColor();

			/*
				caso seja um diretório (aqui tratado como banco), chama a função
				listFilesInFolder, pois printará os arquivos e pastas deste diretório
			*/
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
	char* path = (char*)calloc(255,sizeof(char));
	
	path = "dbs/";
	path = concat(path, table.database);
	path = concat(path, "/");
	path = concat(path, table.name);
	path = concat(path, ".csv");
	FILE *file = fopen(path, "a+");

	if(file == NULL){
		fclose(file);
		boldRed();
		printf( "Erro na abertura do arquivo! Voce digitou corretamente?\n");
		resetColor();
	} else{
		Table csvTable = csvToTable(path);
		int isAlreadyAPrimaryKey = 0;
		for(int i=0; i < csvTable.numRows; i++){
			if (strcmp(csvTable.data[i][0], table.data[0][0]) == 0){
				isAlreadyAPrimaryKey = 1;
			}
		}
		if(isAlreadyAPrimaryKey == 0){
			if(table.numCols == csvTable.numCols){
				int isTypesCorresponding = 0;
				for(int i=0; i < csvTable.numCols; i++){
					char* endToken = NULL;
					char* token = strtok_r(csvTable.data[0][i], " ", &endToken);
					if (isInFormat(token, table.data[0][i]) == 1){
						isTypesCorresponding = 1;
						continue;
					} else{
						isTypesCorresponding = 0;
						break;
					}
				}
				for (int i=0; i < table.numCols;i++){
				}
				if (isTypesCorresponding){
					for(int i=0; i < table.numCols; i++){
						if(i == table.numCols-1){
							fprintf(file,"%s",table.data[0][i]);
							fprintf(file, "%s", "\n");
						} else{
							table.data[0][i] = concat(table.data[0][i], "|");
							fprintf(file,"%s",table.data[0][i]);
						}
					}
					fclose(file);
					cyan();
					printf("\nItens inseridos com sucesso\n");
					resetColor();

				} else{
					fclose(file);
					boldRed();
					printf( "Erro: existem itens digitados que nao corresponde a seus tipos\n" );
					resetColor();
				}
			} else{
				fclose(file);
				boldRed();
				printf( "Erro: numero de colunas digitado difere das colunas do arquivo\n" );
				resetColor();
			}

		} else{
			fclose(file);
			boldRed();
			printf( "Erro:A Primary Key digitada ja esta sendo usada\n" );
			resetColor();
		}
	}

}

void deleteFromTable();

void dropDatabase(Database database){
	FILE *file;
	
	int ret; // Retorna 0 para caso o arquivo tenha sido removido com sucesso;
	/*
	*	o path é escrito com iniciais "rm -r dbs/" pois é usado a função system()
	*	para deletar o arquivo, por isso o rm -r, no início.
	*/
	char* path = "rm -r dbs/"; // deleta recursivamente todos os arquivos presentes em dbs/
	path = concat(path, database.name);
	ret = system(path); // system retorna um inteiro 0 para sucesso e 1 para falha.

	if(ret==0){
		boldGreen();
		printf("O banco de dados em %s foi removido com sucesso\n", path);
		resetColor();
	} else{
		boldRed();
		printf("O banco de dados em %s não foi encontrado\n", path);
		resetColor();
	}

}

void dropTable(Table table){
	
	int ret; //	Retorna 1 para caso o arquivo tenha sido removido com sucesso;

	/*
	*	o path é escrito com iniciais "rm dbs/" pois é usado a função system()
	*	para deletar o arquivo, por isso o rm, no início.
	*/
	char* path = "rm dbs/"; //	O commando rm em system() remove um arquivo ou diretório.
	path = concat(path, table.database);
	path = concat(path, "/");
	path = concat(path, table.name);
	path = concat(path, ".csv");

	ret = system(path);//  system retorna o inteiro 0 para sucesso e 1 para falha.

	if(ret==0){
		yellow();
		printf("Caminho %s foi removido com sucesso\n", path);
		resetColor();
	} else{
		boldRed();
		printf("O caminho %s não foi encontrado\n", path);
		resetColor();
	}

}

void replaceTable(Table table){
	FILE *file;
	char* path = "dbs/";
	/*
	*	Concatena o nome do path a ser recebido pelo file utilziando
	*	o nome da table.database e table.name
	*/
	path = concat(path, table.database);
	path = concat(path, "/");
	path = concat(path, table.name);
	path = concat(path, ".csv");
	/*
	*	Substitui o arquivo com o caminho anterior pelo novo
	*/
	file = fopen(path, "w");
	/*
	*	O laço de repetição vai escrever os dados no arquivo colocando
	*	'|' no final de cada item, com exceção do último.
	*/
	for(int i=0; i < table.numRows; i++){
		for(int j=0; j < table.numCols; j++){
			if(j == table.numCols-1){
				fprintf(file,"%s",table.data[i][j]);
				fprintf(file, "%s", "\n");
			} else{
				fprintf(file,"%s",table.data[i][j]);
				fprintf(file, "|");
			}
		}
	}
	boldGreen();
	printf("Dado deletado com sucesso.\n");
	fclose(file);
}