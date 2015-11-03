#include <stdio.h>
#include <stdlib.h>

int main(){


int ans = 1;
    do{

    printf("MENU\n");
    printf("1. Adicionar Literatura\n");
    printf("2. Listar Literaturas\n");
    printf("3. Editar Literatura\n");
    printf("4. Remover Literatura\n");
    printf("0. Voltar\n");
    scanf("%d", &ans);
    FILE *dados;

    switch(ans){

        case 1:


            dados = fopen("dados.txt", "a");

            char livro[100], autor[100], data[30];
            printf("Adicionar Literatura");
            printf("\nInsira o nome da literatura: ");
            scanf("%s", &livro);
            printf("\nInsira o nome do autor: ");
            scanf("%s", &autor);
            printf("\nInsira a data de publicação: ");
            scanf("%s", &data);

            fprintf(dados, "%s, %s, %s\n", livro, autor, data);
            fclose(dados);
            printf("Livro adicionado ao arquivo!");

            break;

        case 2:

            printf("\nVisualizar livros: \n\n");

            dados = fopen("dados.txt", "r");


            int nLinhas=0;

            char c;
            while(!feof(dados)){
                c = fgetc(dados);
                if(c =='\n'){
                    nLinhas++;
                }
            }
            rewind(dados);


            char line[150];
            int n = 1;
            int count=0;

            while(count<nLinhas){
                fgets(line, 150, dados);
                printf("%d - %s", n, line);
                n++;
                count++;
            }

            fclose(dados);
            printf("\n");
            break;

        case 3:

            break;

        case 4:

            break;
    }

    }while(ans!=0);

    return 0;
}
