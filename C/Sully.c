int i = 5;
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
char *q = "int i = %d;%c#include <stdio.h>%c#include <stdlib.h>%c#include <unistd.h>%cchar *q = %c%s%c;%cint main(){char p[64];sprintf(p, %cSully_%%d.c%c, i);int j = i - 1;if(access(p, R_OK) == -1)j = i;if(j < 0)return 0;char f[64];sprintf(f, %cSully_%%d.c%c, j);FILE *o = fopen(f, %cw%c);fprintf(o, q, j, 10, 10, 10, 10, 34, q, 34, 10, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 10);fclose(o);char c[128];sprintf(c, %cgcc Sully_%%d.c -o Sully_%%d%c, j, j);system(c);char r[64];sprintf(r, %c./Sully_%%d%c, j);system(r);return 0;}%c";
int main(){char p[64];sprintf(p, "Sully_%d.c", i);int j = i - 1;if(access(p, R_OK) == -1)j = i;if(j < 0)return 0;char f[64];sprintf(f, "Sully_%d.c", j);FILE *o = fopen(f, "w");fprintf(o, q, j, 10, 10, 10, 10, 34, q, 34, 10, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 10);fclose(o);char c[128];sprintf(c, "gcc Sully_%d.c -o Sully_%d", j, j);system(c);char r[64];sprintf(r, "./Sully_%d", j);system(r);return 0;}
