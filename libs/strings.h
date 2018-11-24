/*
*	Responsável por quebrar um string
*	em um vetor a cada caractere encontrado
*
*	Recebe
*	@char* string
*	@char* caracteres
*	@int   pos	
*	
*	Retorna
*	@char*
*/
char* wordInPositionAfterSeparations(char* string, char* caracteres, int pos);
int numberOfWords(char* string, char* caracteres);
char* capitalize(char* string);
char* lowerCase(char* string);
char* betweenParenthesis(char* string);
char* removeSpacesAfterCommas(char* string);
int isInString(char* string, char caracter);
char* stringTillChar(char* string, char c);
int isSubstringInString(char* string, char* subString);
char* getSubstringAfterSubstringInString(char* string, char* subString);
/*
*   Responsável por verificar se a string recebida é do tipo informado
*
*   Recebe
*   @char* type
*   @char* string
*
*   Retorna
*   @int
*/
int isInFormat(char* type, char* string);
/*
*   Responsável por verificar quantas ocorrências de um char ocorre em
*   uma string
*
*   Recebe
*   @caracter
*   @string
*
*   Retorna
*   @int
*/
int howManyOcurrencesInString(char caracter, char* string);
/*  
*   Reponsável por transformar uma string em um tipo inteiro
*   
*   Recebe
*   @string
*
*   Retorna
*   @int
*/
int stringToInt(char* string);
char* switchCommaToVerticalBar(char* string);
char* switchCommaToVerticalBarWithQMarks(char* string);
char* invertString(char* string);
char* betweenSymbols(char* string, char symbol1, char symbol2);