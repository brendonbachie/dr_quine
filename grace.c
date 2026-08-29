/*quine in C*/
#include <stdio.h>
#define OUT "Grace_kid.c"
#define P(a,b) fprintf(f,a,b)
#define Q(q)char*b=#q;q
Q(int main(){FILE*f=fopen(OUT,"w");fprintf(f,"/*quine in C*/%c#include <stdio.h>%c#define OUT %cGrace_kid.c%c%c#define P(a,b) fprintf(f,a,b)%c#define Q(q)char*b=#q;q%cQ(%s)%c",10,10,34,34,10,10,10,b,10);return 0;})
