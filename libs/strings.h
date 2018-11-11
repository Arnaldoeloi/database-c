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
*	
*/
char* wordInPositionAfterSeparations(char* string, char* caracteres, int pos);

int numberOfWords(char* string, char* caracteres);
char* capitalize(char* string);
char* lowerCase(char* string);
char* betweenParenthesis(char* string);
int isInString(char* string, char caracter);
char* switchCommaToVerticalBar(char* string);
char* switchCommaToVerticalBarWithQMarks(char* string);