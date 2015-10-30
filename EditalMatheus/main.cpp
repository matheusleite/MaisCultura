#include <iostream>
#include <stdio.h>
using namespace std;

void read (){
    FILE *f;
    f = fopen("edital.txt","r");
    char edital[150];
    while (fgets(edital, 100, f)!= NULL){
        printf("%s", edital);
    }
    printf ("\n");
    fclose(f);
}

int main()
{
    FILE *f;
    f = fopen("edital.txt","a");
    read();
    char edit[150];
    printf("Digite o edital a ser adicionado: ");
    gets(edit);
    fputs(edit, f);
    fprintf(f,"\n");
    fclose(f);
    read();
    return 0;
}
