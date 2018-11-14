#include <stdio.h>
#include <stdlib.h>

int main(){
    system("gcc main.c libs/common.c libs/database_operations.c libs/colors.c libs/strings.c -o exec -g -W");
    return 0;
}