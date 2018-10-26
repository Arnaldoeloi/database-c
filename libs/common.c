#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
	if (strlen(vector) < strlen(subvector)){
		return 0;
	}else{
		for (int i=0; vector[i] != '\0'; i++){
			if(vector[i] ==  subvector[i]){
				if (i == (int)strlen(vector)-1) return 1;
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
		printf("Creating database\n");
	}else if(findInVector("create ", command)){
		printf("Creating table\n");
	}else if(findInVector("alter table ", command)){
		printf("Creating table\n");
	}else if(findInVector("insert into ", command)){
		printf("Creating table\n");
	}else if(findInVector("delete from ", command)){
		printf("Creating table\n");
	}else if(findInVector("drop database ", command)){
		printf("Creating table\n");
	}else if(findInVector("select ", command)){
		printf("Creating table\n");
	}
}