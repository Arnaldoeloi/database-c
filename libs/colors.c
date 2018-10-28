#include <stdio.h>
/*
[0;31m	Red
[1;31m	Bold Red
[0;32m	Green
[1;32m	Bold Green
[0;33m	Yellow
[01;33m	Bold Yellow
[0;34m	Blue
[1;34m	Bold Blue
[0;35m	Magenta
[1;35m	Bold Magenta
[0;36m	Cyan
[1;36m	Bold Cyan
[0m	    Reset
*/
void red(){
  printf("\033[0;31m");
}
void boldRed(){
  printf("\033[1;31m");
}
void green(){
  printf("\033[0;32m");
}
void boldGreen(){
  printf("\033[1;32m");
}
void blue(){
  printf("\033[0;34m");
}
void boldBlue(){
  printf("\033[1;34m");
}
void magenta(){
  printf("\033[0;35m");
}
void boldMagenta(){
  printf("\033[1;35m");
}
void cyan(){
  printf("\033[0;36m");
}
void boldCyan(){
  printf("\033[1;36m");
}
void yellow(){
  printf("\033[0;33m");
}
void boldYellow(){
  printf("\033[01;33m");
}
void resetColor(){
  printf("\033[0m");
}