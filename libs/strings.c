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

char*** splitIntoMatrix(char *string, char separator){
	char*** data=(char***) calloc(1, sizeof(char***));
	int col=0;
	int row=0;
	data[row]=(char**) calloc(1, sizeof(char**));
	data[row][col]=strtok(string, ",");
	printf("data[%i][%i]:%4s\n",row,col,data[row][col]);
	col++;
	for(int i=0; i<(int)strlen(string)+1; i++){
		if(string[i]==separator){
			data[row][col]=strtok(string, ",");
			col++;
		}else if(string[i]=='\n'){
			row++;
			data[row]=(char**) calloc(1, sizeof(char**));
			//printf("%c", string[i]);
		}
	}
	return data;
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