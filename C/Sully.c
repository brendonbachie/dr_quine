#include <stdio.h>
#include <stdlib.h>
int i = 5;
char *q = "#include <stdio.h>%c#include <stdlib.h>%cint i = %d;%cchar *q = %c%s%c;%cint main(){int j = i - 1;char f[64];sprintf(f, %cSully_%%d.c%c, j);FILE *o = fopen(f, %cw%c);fprintf(o, q, 10, 10, j, 10, 34, q, 34, 10, 34, 34, 34, 34, 34, 34, 34, 34, 10);fclose(o);char c[128];sprintf(c, %cgcc Sully_%%d.c -o Sully_%%d%c, j, j);system(c);if (j >= 0){char r[64];sprintf(r, %c./Sully_%%d%c, j);system(r);}return 0;}%c";
int main(){int j = i - 1;char f[64];sprintf(f, "Sully_%d.c", j);FILE *o = fopen(f, "w");fprintf(o, q, 10, 10, j, 10, 34, q, 34, 10, 34, 34, 34, 34, 34, 34, 34, 34, 10);fclose(o);char c[128];sprintf(c, "gcc Sully_%d.c -o Sully_%d", j, j);system(c);if (j >= 0){char r[64];sprintf(r, "./Sully_%d", j);system(r);}return 0;}
