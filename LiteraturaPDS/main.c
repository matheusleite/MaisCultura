#include <stdio.h>
#include <stdlib.h>

void create(char *literatura, char *autor, char *publicacao){
}

void list(){
}

void edit(){
}

void remove(){
}

int main()
{
    printf("MENU\n");
    printf("1. Adicionar Literatura\n");
    printf("2. Listar Literaturas\n");
    printf("3. Editar Literatura\n");
    printf("4. Remover Literatura\n");
    printf("0. Voltar\n");
    int ans;
    scanf("%d", &ans);

    switch(ans){

        case 1:
            char nome_literatura[100], nome_autor[100], data_publicacao[30];
            printf("Adicionar Literatura");
            printf("\nInsira o nome da literatura: ");
            scanf("%s", &nome_literatura);
            printf("\nInsira o nome do autor: ");
            scanf("%s", &nome_autor);
            printf("\nInsira a data de publicação: ");
            scanf("%s", &data_publicacao);

            create(nome_literatura, nome_autor, data_publicacao);
            break;

        case 2:
            list();
            break;

        case 3:
            edit();
            break;

        case 4:
            remove();
            break;


    }
    return 0;
}
