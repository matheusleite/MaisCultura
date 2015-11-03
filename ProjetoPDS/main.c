
#include <stdio.h>
#include <stdlib.h>

int main(){


int ans = 1;
	do{

    printf("MENU\n");
    printf("1. Adicionar concerto\n");
    printf("2. Listar concertos\n");
    printf("3. Editar concerto\n");
    printf("4. Remover concerto\n");
    printf("0. Voltar\n");
    scanf("%d", &ans);
    FILE *dados;

    switch(ans){

        case 1:

			// criando arquivo
        	dados = fopen("dados.txt", "a");

            char nome_concerto[100], local[100], data_evento[30];
            printf("Adicionar concerto");
            printf("\nInsira o nome do concerto: ");
            scanf("%s", &nome_concerto);
            printf("\nInsira o local: ");
            scanf("%s", &local);
            printf("\nInsira a data do evento: ");
            scanf("%s", &data_evento);

            fprintf(dados, "%s, %s, %s\n", nome_concerto, local, data_evento);
            fclose(dados);
            printf("Concerto adicionado ao arquivo.\n");

            break;

        case 2:

            printf("\nVisualizar Concertos: \n\n");

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
