#include <stdio.h>
#include <stdlib.h>
#include "database_operations.h"


void commandVersion(){
	printf("0.0.3 All rights reserved to Go Horse interprise LTDA.\n");
}

char* input(){
	char*string = malloc(sizeof(char));

	int i=0;
	while(string[i-1]!='\n'){
		string=realloc(string, (sizeof(char)*i+sizeof(char)));
		string[i]=getchar();
		i++;
	}
	i++;
	string[i]='\0';
	return string;
}


int findInVector(char* command){
	
}