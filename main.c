#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs/common.h" //Biblioteca com comandos padrões (leitura do comando)
#include "libs/database_types.h"

int main(){
	// commandVersion();
	// while(1){
	// 	char*v=input();
	// 	if(strcmp("exit",v)==0){
	// 		break;
	// 	}
	// 	execute(v);
	// }
	// return 0;
	Table usuarios;
	usuarios.name = "usuarios";
	usuarios.database = "escola";
	usuarios.data = (char***) calloc(1, sizeof(char***));

	usuarios.data[0]=(char**) calloc(1, sizeof(char**));
	usuarios.data[0][0] = "Arnaldo";
	usuarios.data[0][1] = "(84) 9 9381-8314";
	
	usuarios.data[1]=(char**) calloc(1, sizeof(char**));
	usuarios.data[1][0] = "Claudinho batata";
	usuarios.data[1][1] = "(42) 9 8474-0238";

	// usuarios.data[2][0] = "Nathanael DeRico";
	// usuarios.data[2][1] = "(42) 9 9374-1637";

	// usuarios.data[3][0] = "Pedro boca de batata";
	// usuarios.data[3][1] = "(42) 9 3223-4707";

	// usuarios.data[4][0] = "Marjory Marjority";
	// usuarios.data[4][1] = "(22) 8 3441-2101";

	printTable(usuarios);

	return 0;
}	