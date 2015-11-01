#include <stdio.h>
#include <stdlib.h>

void create(char *concerto, char *local, char *data){
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
    printf("1. Adicionar concerto\n");
    printf("2. Listar concertos\n");
    printf("3. Editar concerto\n");
    printf("4. Remover concerto\n");
    printf("0. Voltar\n");
    int ans;
    scanf("%d", &ans);

    switch(ans){

        case 1:
            char nome_concerto[100], local[100], data_evento[30];
            printf("Adicionar concerto");
            printf("\nInsira o nome do concerto: ");
            scanf("%s", &nome_concerto);
            printf("\nInsira o local: ");
            scanf("%s", &local);
            printf("\nInsira a data do evento: ");
            scanf("%s", &data_evento);

            create(nome_concerto, local, data_evento);
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
