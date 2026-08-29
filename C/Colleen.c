/*quine in C*/
#include <stdio.h>
void put_string(char *s){printf(s,10,10,10,10,10,34,s,34,10);}
int main(){
/*main of quine*/
char*s="/*quine in C*/%c#include <stdio.h>%cvoid put_string(char *s){printf(s,10,10,10,10,10,34,s,34,10);}%cint main(){%c/*main of quine*/%cchar*s=%c%s%c;%cput_string(s);return 0;}";
put_string(s);return 0;}