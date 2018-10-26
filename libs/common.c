#include <stdio.h>
#include <stdlib.h>


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
	string[i-1]='\0';
	return string;
}


int findInVector(char* subvector, char* vector){
	int comparison[strlen(vector)];

	if (strlen(vector) < strlen(subvector)){
		return 0;
	} else{
		for (int i=0; vector[i] == "\0"; i++){
			if(vector[i] ==  subvector[i]){
				comparison[i] = 1;
				if (i = strlen(vector)) return 1;
			}
			else return 0;
		}
	}
}