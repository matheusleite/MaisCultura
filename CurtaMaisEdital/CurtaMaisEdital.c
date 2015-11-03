//Universidade de Brasília. Novembro de 2015

//Fábio Barbosa Pinto 11/0116356
//Matheus Clemente Carvalho de Azevedo 15/0042817

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct edital
{
    char tituloEdital[30];
    int diaEdital;
    int mesEdital;
    char conteudo[300];
};

int exibirMenuEdital(void);
void criarEdital(void);
void buscarEdital(void);
void atualizarConteudo(void);
void excluirEdital(void);




int main(void)
{
    int opcao;

    do
    {
        opcao = exibirMenuEdital();

        switch (opcao)
        {
        case 1:
            criarEdital();
            break;
        case 2:
            buscarEdital();
            break;
        case 3:
            atualizarConteudo();
            break;
        case 4:
            excluirEdital();
            break;
        case 5:
            printf("\n Encerrando...");
            break;
        default:
            printf("\n Opcao invalida!");
        }
        Sleep(1000);
    } while (opcao != 5);

    return 0;
}

int exibirMenuEdital(void)
{
    int opcao;

    system("cls");

    printf("\tEDITAIS\n\n");
    printf(" 1. Criar Edital\n");
    printf(" 2. Buscar Edital\n");
    printf(" 3. Atualizar Conteudo\n");
    printf(" 4. Excluir Edital\n");
    printf(" 5. Encerrar\n\n");
    printf(" Digite a opcao desejada: ");
    scanf("%d", &opcao);

    return opcao;
}

void criarEdital(void)
{
    struct edital meuEdital;
    FILE *arquivo;

    system("cls");

    printf("\tEDITAIS - CRIAR EDITAL\n\n");
    printf(" Titulo do Edital: ");
    fflush(stdin);
    gets(meuEdital.tituloEdital);
    printf(" Dia de Lancamento do Edital: ");
    scanf("%d", &meuEdital.diaEdital);
    printf(" Mes de Lancamento do Edital: ");
    scanf("%d", &meuEdital.mesEdital);
    printf(" Conteudo: ");
    fflush(stdin);
    gets(meuEdital.conteudo);
    printf("\n\nEdital Criado com sucesso\n");
    Sleep (2000);

    arquivo = fopen("edital.dat", "ab");
    if (!arquivo)
    {
        arquivo = fopen("edital.dat", "wb");
    }

    fwrite(&meuEdital, 1, sizeof(struct edital), arquivo);

    fclose(arquivo);
}

void buscarEdital(void)
{
    int encontrado = 0;
    char busca[30];
    struct edital meuEdital;
    FILE *arquivo;

    system("cls"); //

    printf("\tEDITAIS - BUSCAR EDITAL\n\n");
    printf(" Titulo do Edital: ");
    fflush(stdin);
    gets(busca);

    arquivo = fopen("edital.dat", "rb");

    if (arquivo)
    {
        fread(&meuEdital, 1, sizeof(struct edital), arquivo);
        while (!feof(arquivo))
        {
            if (strcmp(busca, meuEdital.tituloEdital) == 0)
            {
                printf("\n Titulo do Edital: %s\n", meuEdital.tituloEdital);
                printf(" Data de lancamento: %d/%d\n", meuEdital.diaEdital, meuEdital.mesEdital);
                printf(" Conteudo: %s", meuEdital.conteudo);
                printf ("\n\nPressione duas vezes 'Enter' para voltar ao menu inicial\n");
                getchar();
                encontrado = 1;
                break;
            }
            fread(&meuEdital, 1, sizeof(struct edital), arquivo);
        }

        if (!encontrado)
        {
            printf("\n Edital nao encontrado!");
            Sleep(1000);
        }
        fclose(arquivo);
    }
    else
    {
        printf("\n Nada encontrado no arquivo!");
        Sleep(1000);
    }
}

void atualizarConteudo(void)
{
    int encontrado = 0;
    char tituloEdital[30], conteudo[15];
    struct edital editalTemporario;
    FILE *arquivoAntigo = NULL, *arquivoAtualizado = NULL;

    system("cls");

    printf("\tEDITAIS - ATUALIZAR EDITAL\n\n");
    printf(" Titulo do Edital: ");
    fflush(stdin);
    gets(tituloEdital);
    printf(" Novo Conteudo: ");
    fflush(stdin);
    gets(conteudo);

    arquivoAntigo = fopen("edital.dat", "rb");
    if (arquivoAntigo)
    {
        arquivoAtualizado = fopen("temp.dat", "wb");
        if (!arquivoAtualizado)
        {
            printf("\n Falha na atualizacao do edital!");
            Sleep(1000);
            return;
        }

        fread(&editalTemporario, 1, sizeof(struct edital), arquivoAntigo);
        while (!feof(arquivoAntigo))
        {
            if (strcmp(editalTemporario.tituloEdital, tituloEdital) == 0)
            {
                strcpy(editalTemporario.conteudo, conteudo);
                encontrado = 1;
            }
            fwrite(&editalTemporario, 1, sizeof(struct edital), arquivoAtualizado);
            fread(&editalTemporario, 1, sizeof(struct edital), arquivoAntigo);
        }

        fclose(arquivoAntigo);
        fclose(arquivoAtualizado);

        remove("edital.dat");
        rename("temp.dat", "edital.dat");

        if (!encontrado)
        {
            printf("\n Nao foi possivel encontrar o edital...");
        }
        else
        {
            printf("\n Atualizacao realizada com sucesso!");
        }

        Sleep(1000);
    }
    else
    {
        printf("\n Nenhum edital encontrado!");
        Sleep(1000);
    }
}

void excluirEdital(void)
{
    int encontrado = 0;
    char tituloEdital[30];
    struct edital editalTemporario;
    FILE *arquivoAntigo = NULL, *arquivoAtualizado = NULL;

    system("cls");

    printf("\tEDITAIS - EXCLUIR CONTEUDO\n\n");
    printf(" Nome do Edital: ");
    fflush(stdin);
    gets(tituloEdital);

    arquivoAntigo = fopen("edital.dat", "rb");
    if (arquivoAntigo)
    {
        arquivoAtualizado = fopen("temp.dat", "wb");
        if (!arquivoAtualizado)
        {
            printf("\n Falha na exclusao do edital!");
            fclose(arquivoAntigo);
            Sleep(1000);
            return;
        }

        fread(&editalTemporario, 1, sizeof(struct edital), arquivoAntigo);
        while (!feof(arquivoAntigo))
        {
            if (strcmp(editalTemporario.tituloEdital, tituloEdital) == 0)
            {
                encontrado = 1;
            }
            else
            {
                fwrite(&editalTemporario, 1, sizeof(struct edital), arquivoAtualizado);
            }
            fread(&editalTemporario, 1, sizeof(struct edital), arquivoAntigo);
        }

        fclose(arquivoAntigo);
        fclose(arquivoAtualizado);

        remove("edital.dat");
        rename("temp.dat", "edital.dat");

        if (!encontrado)
        {
            printf("\n Nao foi possivel encontrar o edital...");
        }
        else
        {
            printf("\n Exclusao realizada com sucesso!");
        }

        Sleep(2000);
    }
    else
    {
        printf("\n Nenhum edital encontrado!");
        Sleep(2000);
    }
}
