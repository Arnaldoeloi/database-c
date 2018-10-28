#include<stdlib.h>
#include<string.h>
#include<stdio.h>

char* wordInPositionAfterSeparations(char* string, char* caracteres, int pos){
	char m[100][strlen(string)];
	char *token;
	token = strtok(string, caracteres);
	
	for(int i=0; token != NULL; i++) {
		for(int j=0; j < (int)strlen(token)+1; j++){
			m[i][j] = token[j];
		}
		token = strtok(NULL, caracteres);
	}

	char* word=NULL;
	for (int i = 0; i < (int)strlen(m[pos])+1; i++){
		word=realloc(word, i*sizeof(char)+sizeof(char));
		word[i]=m[pos][i];
	}
	return word;
}


int numberOfWords(char* string, char* caracteres){
	char m[100][strlen(string)];
	char *token;
	int nWords;
	token = strtok(string, caracteres);
	
	for(int i=0; token != NULL; i++) {
		for(int j=0; j < (int)strlen(token); j++){
			m[i][j] = token[j];
		}
		token = strtok(NULL, caracteres);
		nWords = i + 1;
	}
	return nWords;
}