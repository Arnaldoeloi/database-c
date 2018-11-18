#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>

char* betweenSymbols(char* string, char symbol1, char symbol2){
	char* newString=NULL;
	int cont=0;
	int foundSymbol=0;
	
	for(int i=0; i<(int)strlen(string)+1;i++){
		if(string[i]==symbol1 && foundSymbol==0){
			foundSymbol=1;
		}
		else if(foundSymbol){
			if(string[i]!=symbol2){
				newString=(char*) realloc(newString, cont*sizeof(char)+sizeof(char));
				newString[cont]=string[i];
				cont++;
			}else{
				break;
			}
		}
	}
	printf("newString:%s\n", newString);
	return newString;
}

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

char* capitalize(char* string){
	char* capitalString=string;
	strcpy(capitalString, string);
	for(int i=0; i< (int)strlen(string)+1; i++){
		capitalString[i]=toupper(string[i]);
	}
	return capitalString;
}
char* lowerCase(char* string){
	char* lowerCaseString=string;
	strcpy(lowerCaseString, string);
	for(int i=0; i< (int)strlen(string)+1; i++){
		lowerCaseString[i]=tolower(string[i]);
	}
	return lowerCaseString;
}

char* betweenParenthesis(char* string){
	// yellow();
	printf("60\n");
	// resetColor();
	int cont=0;
	int pos=0;
	char*str = NULL;
	int size=0;

	while(1){
		printf("69\n");
		str= (char*) realloc(str, sizeof(char));
		printf("71\n");
		if(string[cont]=='('){
			printf("73\n");
			for(int i=cont+1; string[i]!=')' && string[i]!='\0' && string[i]!='\0';i++){
				printf("75: i=%i\n", i);
				str=(char*) realloc(str, ((sizeof(char)*size)+sizeof(char)));
				printf("77: size=%i\n\n", size);
				str[size]=string[i];
				pos=i;
				size++;
			}
			printf("80\n");
			str=(char*) realloc(str, size*sizeof(char)+sizeof(char));
			printf("82\n");
			str[size]='\0';
			return str;
			break;
		}
		cont++;
	}
	return str;
}

char* removeSpacesAfterCommas(char* string){
	char* data=NULL;
	int cont=0;

	int lastWasComma=0; //false
	for(int i=0; i<(int)strlen(string)+1; i++){
		if(string[i]==',' && lastWasComma==0){
			lastWasComma=1; //true
			data=(char*) realloc(data, (sizeof(char)*cont)+sizeof(char));
			data[cont]=string[i];
			cont++;
			continue;
		}else if(lastWasComma && string[i]==' '){
			continue;
		}else{
			lastWasComma=0;
			data=(char*) realloc(data, (sizeof(char)*cont)+sizeof(char));
			data[cont]=string[i];
			cont++;
		}
	}
	return data;
}

int isInString(char* string, char caracter){
	for (int i=0; i < (int)strlen(string); i++){
		if (string[i] != caracter){
			if(i == (int)strlen(string)-1){
				return 0;
			}
			continue;
		}
		if (string[i] == caracter){
			return 1;
			break;
		}
	}
}

char* switchCommaToVerticalBar(char* string){
	char* stringNew = (char*)calloc((int)strlen(string),sizeof(char));
	strcpy(stringNew, string); //Copia "string" e atribui o valor a "stringNew"
	
	for(int i=0; i < (int)strlen(string) ; i++){
		if(string[i] == ','){
			stringNew[i] = '|';
		}
	}
	return stringNew;
	free(stringNew);
}

char* switchCommaToVerticalBarWithQMarks(char* string){
	char* stringNew = (char*)calloc((int)strlen(string),sizeof(char));
	strcpy(stringNew, string); //Copia "string" e atribui o valor a "stringNew"

	//"hasQMark" é uma boleana que é 0 quando o laço a seguir não está rodando dentro de aspas e é 1 quando está
	int hasQMark = 0; 

	for(int i=0; i < (int)strlen(string) ; i++){
		//Ativo se o laço não está contido em aspas e vai até a primeira aspa
		if(hasQMark == 0){
		    if(string[i] != '\"'){
				if(string[i] == ','){
					stringNew[i] = '|';
					continue;
				}
			} else{
				hasQMark = 1;
				continue;
			}
		}
		//Ativo se o laço está rodando dentro de aspas e vai até a última aspa
		if(hasQMark == 1){
			if(string[i] == '"'){
				hasQMark = 0;
			}
		}
	}
	return stringNew;
	free(stringNew);
}

int isSubstringInString(char* string, char* subString){
	char* validatedString = (char*)calloc((int)strlen(subString),sizeof(char));
	for(int i=0, j=0; i < (int)strlen(string); i++){
		if (string[i] == subString[j]){
			validatedString[j] = string[i];
			j++;
		}
	}
	if (strcmp(validatedString,subString) == 0){
		return 1;
		free(validatedString);
	} else {
		return 0;
		free(validatedString);
	}
}

char* getSubstringAfterSubstringInString(char* string, char* subString){
	// Serve para chegar se há a substring dentro da string
	char* validatedString = (char*)calloc((int)strlen(subString),sizeof(char));
	// É a subString nova que fica logo após a subString dentro da string
	char* subStringAfter = (char*)calloc((int)strlen(string),sizeof(char));
	// Verifica que a subString é igual a validatedString
	int alreadyValidated=0;
	for(int i=0, j=0, k=0, fSpace=0; i <= (int)strlen(string); i++){
		// Condição bool para ver se o primeiro espaço já foi usado
		//Checa se a posição i da string e a posição j da subString são iguais e se forem, salva em validatedString[j]
		if (string[i] == subString[j]){
			if(alreadyValidated == 0){
				validatedString[j] = string[i];
				j = j+1;
				continue;
			}
		}
		// Após a string validatedString se tornar igual a subString o laço de repetição agora vai salvar e retornar subStringAfter 
		if (strcmp(validatedString, subString) == 0){
			alreadyValidated = 1;
			int firstSpace = 0;
			if(string[i] == ' ' || string[i] == '\n'){
				if(fSpace == 0){
					continue;
				} else{
					return subStringAfter;
					break;
				}
			} else{
				subStringAfter[k] = string[i];
				k++;
				if(i == (int)strlen(string)-1){
					subStringAfter = (char*)realloc(subStringAfter, k);
					return subStringAfter;
					break;
				} continue;
			}	
		}
	}
	free(validatedString);
	free(subStringAfter);
}

char* invertString(char* string){
	char c;
	for (int i = 0, j = strlen(string)-1; i < j; i++, j--) {
        c = string[i];
        string[i] = string[j];
        string[j] = c;
    }
	return string;
}