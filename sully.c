#include <stdio.h>
#include <stdlib.h>
int main() {int i = 5; if (i < 0) return 1; char s[1000]; sprintf(s, "Sully_%d.c", i); FILE *arquivo = fopen(s, "w");
    char *quine = "#include <stdio.h>%c#include <stdlib.h>%cint main() {int i = %d; if (i < 0) return 1; char s[1000]; sprintf(s, %cSully_%%d.c%c, i); FILE *arquivo = fopen(s, %cw%c);%c    char *quine = %c%s%c;%c    fprintf(arquivo, quine, 10, 10, i - 1, 34, 34, 34, 34, 10, 34, quine, 34, 10, 10, 34, 34, 10, 10, 10, 10);%c    fclose(arquivo); char compile[100]; sprintf(compile, %cgcc Sully_%%d.c -o Sully_%%d && ./Sully_%%d%c, i, i, i);%c    system(compile);%c    return 0;%c}%c";
    fprintf(arquivo, quine, 10, 10, i - 1, 34, 34, 34, 34, 10, 34, quine, 34, 10, 10, 34, 34, 10, 10, 10, 10);
    fclose(arquivo); char compile[100]; sprintf(compile, "gcc Sully_%d.c -o Sully_%d && ./Sully_%d", i, i, i);
    system(compile);
    return 0;
}