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

/*
*   Retorna se um suvector está contido no início de um vetor.
*
*   Recebe
*   @char* subvector
*   @char* vector
*   
*   Retorna 1 para verdadeiro ou 0 para false
*   @int
*/
int findInVector(char* subvector, char* vector);

/*
*   Retorna se um suvector está contido no fim de um vetor.
*
*   Recebe
*   @char* subvector
*   @char* vector
*   
*   Retorna 1 para verdadeiro ou 0 para false
*   @int
*/
int findInVectorReverse(char* subvector, char* vector);

/*
*   Retorna o vetor recebido por parâmetro em letras maiúsculas.
*
*   Recebe
*   @char* string
*   
*   Retorna string com todas as letras em caixa alta.
*   @char*
*/
char* capitalize(char* string);

/*
*   Retorna o vetor recebido por parâmetro em letras minúsculas.
*
*   Recebe
*   @char* string
*   
*   Retorna string com todas as letras minúsculas.
*   @char*
*/
char* lowerCase(char* string);

/*
*   Retorna o subvetor contido entre parênteses dada uma string.
*
*   Recebe
*   @char* string
*
*   Retorno   
*   @char*
*/
char* betweenParenthesis(char* string);

/*
*   Retorna uma string sem espaços após as vírgulas.
*
*   Recebe
*   @char* string
*
*   Retorno   
*   @char*
*/
char* removeSpacesAfterCommas(char* string);

/*
*   Retorna uma string sem o caractere passado por parâmetro dada a string e 
*   um caractere.
*
*   Recebe
*   @char* string
*   @char caractere
*
*   Retorno   
*   @char*
*/
char* removeCharsFromString (char* string, char c);

/*
*   Retorna se um caractere está ou não em uma string 
*
*   Recebe
*   @char* string
*   @char caractere
*
*   Retorno 1 para verdadeiro; 0 para falso   
*   @int 
*/
int isInString(char* string, char caracter);

/*
*   Retorna um subvetor de string após 'pos' quebras da string recebida
*   nos caracteres também recebidos.
*
*   Recebe
*   @char* string
*   @char* caracteres
*   int pos
*
*   Retorno   
*   @char*
*/
char* wordInPositionAfterSeparations(char* string, char* caracteres, int pos);

/*
*   Retorna um subvetor de string após 'pos' quebras da string recebida
*   nos caracteres também recebidos.
*
*   Recebe
*   @char* string
*   @char* caracteres
*   int pos
*
*   Retorno   
*   @char*
*/
char* stringTillChar(char* string, char c);

/*
*   Retorna se um subvetor de string recebido está contido na string recebida
*
*   Recebe
*   @char* string
*   @char* subString
*
*   Retorno   
*   @int
*/
int isSubstringInString(char* string, char* subString);

/*
*   Retorna um subvetor de string presente após outro subvetor de string
*
*   Recebe
*   @char* string
*   @char* subString
*
*   Retorno   
*   @int
*/
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
*   @char* string
*
*   Retorna
*   @int
*/
int howManyOcurrencesInString(char caracter, char* string);

/*  
*   Responsável por transformar uma string em um tipo inteiro
*   
*   Recebe
*   @char* string
*
*   Retorna
*   @int
*/
int stringToInt(char* string);

/*
*   Responsável por transformar uma string em uma varíavel do tipo char
*
*   Recebe
*   @char* string
*
*   Retorna
*   @char   
*/
char stringToChar(char* string);

/*
*   Responsável por transformar uma string em uma varíavel do tipo float
*
*   Recebe
*   @char* string
*
*   Retorna
*   @char   
*/
float stringToFloat(char* string);

/*
*   Responsável por transformar uma string em uma varíavel do tipo double
*
*   Recebe
*   @char* string
*
*   Retorna
*   @char   
*/
double stringToDouble(char* string);

/*
*   Responsável por substituir os caracteres
*   de uma string em um char* por '/'
*
*   Recebe
*   @caracter
*   @char* string
*
*   Retorna
*   @char*   
*/
char* switchCharToBar(char caracter, char* string);

/*
*   Responsável por substituir as vírgulas
*   de uma string por '|'
*
*   Recebe
*   @char* string
*
*   Retorna
*   @char*   
*/
char* switchCommaToVerticalBar(char* string);

/*
*   Responsável por substituir as vírgulas
*   de uma string por '|' onde há aspas
*
*   Recebe
*   @char* string
*
*   Retorna
*   @char*   
*/
char* switchCommaToVerticalBarWithQMarks(char* string);

/*
*   Responsável por inverter uma string
*
*   Recebe
*   @char* string
*
*   Retorna
*   @char*   
*/
char* invertString(char* string);

/*
*   Responsável por retornar uma string entre dois caracteres
*   específicos
*
*   Recebe
*   @char* string
*   @char symbol1
*   @char symbol2
*
*   Retorna
*   @char*   
*/
char* betweenSymbols(char* string, char symbol1, char symbol2);