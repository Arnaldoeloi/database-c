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

int execute(char* command){
	if((strcmp("help", command)==0) || (strcmp("man", command)==0)){
		printHelp();
	}else if(findInVector("create database ", command)){
		
		createDatabase(name);
		printf("Creating database\n");
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

char** split(char* string, char* caracteres){
	//char string[80] = "This is www.tutorialspoint.com website";
		
	char m[strlen(string)][strlen(string)];
	char *token;
	token = strtok(string, caracteres);

	char** words=NULL;	

	int i=0;
	for(int x=0; token != NULL; x++) {
		printf( "%s\n", token);
		words[x]=(char*) calloc(strlen(token)+1, sizeof(char));
		words[x]=token;
	   	token = strtok(NULL, caracteres);
	}
	return words;
}




/*
int main () {
	
   char str[80] = "This is www.tutorialspoint.com website";
   char robalo[80][80];
   const char s[2] = " ";
   char *token;
   token = strtok(str, s);

   for(int x=0; token != NULL; x++) {
      printf( " %s\n", token );

      for(int i=0; i < strlen(token); i++){
        robalo[x][i] = token[i];
      }
      token = strtok(NULL, s);

   }
   printf("%s", robalo[0]);
   return(0);
}
*/
