#include <stdlib.h>
#include <stdio.h>

void read ()
{
    FILE *f;
    f = fopen("edital.txt","r");
    char edital[1000];
    while (fgets(edital, 1000, f)!= NULL)
    {
        printf("%s", edital);
    }
    printf ("\n");
    fclose(f);
}
void edit()
{
    FILE *f;
    f = fopen("edital.txt","a");
    char edit[150];
    printf("Digite o edital a ser adicionado: ");
    fgets(edit,150,stdin);
    fputs(edit, f);
    fclose(f);
}
void remover()
{
    /*FILE *f1, *f2;
    int linha=1, linha_deletar;
    char edital[1000];
    f1 = fopen("edital.txt","r");
    f2 = fopen("edital2.txt","w");
    printf("Digite a linha a ser removida: ");
    scanf("%d", &linha_deletar);
    getchar();
    while (fgets(edital, 1000, f1)!= NULL)
    {
        if (=='\n'){
            linha++;
        }
        if(linha != linha_deletar)
            fputs(edital, f2);
    }*/

}
int main()
{
    int n;
    printf("MENU\n");
    printf("1. Adicionar edital\n");
    printf("2. Listar editais\n");
    printf("3. Editar edital\n");
    printf("4. Remover edital\n");
    printf("0. Voltar\n");
    scanf("%d", &n);
    getchar();
    switch (n)
    {
    case 1:
        edit();
        break;
    case 2:
        read();
        break;
    case 3:
        read();
        edit();
        break;
    case 4:
        printf("\n");
        read();
        remover();
        break;
    }
    return 0;
}
