#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct Literatura
{
    char tituloLiteratura[40];
    int livroLiteratura;
    char autorLiteratura [100];
    char data[30];
};

int exibirMenuLiteratura(void);
void criarLiteratura(void);
void buscarLiteratura(void);
void atualizardata(void);
void excluirLiteratura(void);




int main(void)
{
    int opcao;

    do
    {
        opcao = exibirMenuLiteratura();

        switch (opcao)
        {
        case 1:
            criarLiteratura();
            break;
        case 2:
            buscarLiteratura();
            break;
        case 3:
            atualizardata();
            break;
        case 4:
            excluirLiteratura();
            break;
        case 5:
            printf("\n Encerrando...");
            break;
        default:
            printf("\n Opcao invalido!");
        }
        Sleep(1000);
    } while (opcao != 5);

    return 0;
}

int exibirMenuLiteratura(void)
{
    int opcao;

    system("cls");

    printf("\tLITERATURA\n\n");
    printf(" 1. Criar Literatura\n");
    printf(" 2. Buscar Literatura\n");
    printf(" 3. Atualizar data\n");
    printf(" 4. Excluir Literatura\n");
    printf(" 5. Encerrar\n\n");
    printf(" Digite a opcao desejada: ");
    scanf("%d", &opcao);

    return opcao;
}

void criarLiteratura(void)
{
    struct Literatura minhaLiteratura;
    FILE *arquivo;

    system("cls");

    printf("\tLITERATURA - CRIAR Literatura\n\n");
    printf(" Titulo da Literatura: ");
    fflush(stdin);
    gets(minhaLiteratura.tituloLiteratura);
    printf(" data de Lancamento da Literatura: ");
    scanf("%s", &minhaLiteratura.data);
    printf(" autor da Literatura: ");

    fflush(stdin);
    gets(minhaLiteratura.autorLiteratura);
    printf("\n\nLiteratura Criado com sucesso\n");
    Sleep (2000);

    arquivo = fopen("Literatura.dot", "ab");
    if (!arquivo)
    {
        arquivo = fopen("Literatura.dot", "wb");
    }

    fwrite(&minhaLiteratura, 1, sizeof(struct Literatura), arquivo);

    fclose(arquivo);
}

void buscarLiteratura(void)
{
    int encontrada = 0;
    char busca[30];
    struct Literatura minhaLiteratura;
    FILE *arquivo;

    system("cls"); //

    printf("\tLITERATURA - BUSCAR Literatura\n\n");
    printf(" Titulo da Literatura: ");
    fflush(stdin);
    gets(busca);

    arquivo = fopen("Literatura.dot", "rb");

    if (arquivo)
    {
        fread(&minhaLiteratura, 1, sizeof(struct Literatura), arquivo);
        while (!feof(arquivo))
        {
            if (strcmp(busca, minhaLiteratura.tituloLiteratura) == 0)
            {
                printf("\n Titulo da Literatura: %s\n", minhaLiteratura.tituloLiteratura);
                printf(" data: %s\n", minhaLiteratura.data);
                printf(" autor: %s", minhaLiteratura.autorLiteratura);
                printf ("\n\nPressione duas vezes 'Enter' para voltar ao menu inicial\n");
                getchar();
                encontrada = 1;
                break;
            }
            fread(&minhaLiteratura, 1, sizeof(struct Literatura), arquivo);
        }

        if (!encontrada)
        {
            printf("\n Literatura nao encontrada!");
            Sleep(1000);
        }
        fclose(arquivo);
    }
    else
    {
        printf("\n Nado encontrada no arquivo!");
        Sleep(1000);
    }
}

void atualizardata(void)
{
    int encontrada = 0;
    char tituloLiteratura[30], data[15];
    struct Literatura LiteraturaTemporaria;
    FILE *arquivoAntigo = NULL, *arquivoAtualizado = NULL;

    system("cls");

    printf("\tLITERATURA - ATUALIZAR Literatura\n\n");
    printf(" Titulo da Literatura: ");
    fflush(stdin);
    gets(tituloLiteratura);
    printf(" Nova data: ");
    fflush(stdin);
    gets(data);

    arquivoAntigo = fopen("Literatura.dot", "rb");
    if (arquivoAntigo)
    {
        arquivoAtualizado = fopen("temp.dot", "wb");
        if (!arquivoAtualizado)
        {
            printf("\n Falha na atualizacao da Literatura!");
            Sleep(1000);
            return;
        }

        fread(&LiteraturaTemporaria, 1, sizeof(struct Literatura), arquivoAntigo);
        while (!feof(arquivoAntigo))
        {
            if (strcmp(LiteraturaTemporaria.tituloLiteratura, tituloLiteratura) == 0)
            {
                strcpy(LiteraturaTemporaria.data, data);
                encontrada = 1;
            }
            fwrite(&LiteraturaTemporaria, 1, sizeof(struct Literatura), arquivoAtualizado);
            fread(&LiteraturaTemporaria, 1, sizeof(struct Literatura), arquivoAntigo);
        }

        fclose(arquivoAntigo);
        fclose(arquivoAtualizado);

        remove("Literatura.dot");
        rename("temp.dot", "Literatura.dot");

        if (!encontrada)
        {
            printf("\n Nao foi possivel encontrar a Literatura...");
        }
        else
        {
            printf("\n Atualizacao realizado com sucesso!");
        }

        Sleep(1000);
    }
    else
    {
        printf("\n Nenhuma Literatura encontrada!");
        Sleep(1000);
    }
}

void excluirLiteratura(void)
{
    int encontrada = 0;
    char tituloLiteratura[30];
    struct Literatura LiteraturaTemporaria;
    FILE *arquivoAntigo = NULL, *arquivoAtualizado = NULL;

    system("cls");

    printf("\tLITERATURA - EXCLUIR data\n\n");
    printf(" Nome da Literatura: ");
    fflush(stdin);
    gets(tituloLiteratura);

    arquivoAntigo = fopen("Literatura.dot", "rb");
    if (arquivoAntigo)
    {
        arquivoAtualizado = fopen("temp.dot", "wb");
        if (!arquivoAtualizado)
        {
            printf("\n Falha na exclusao da Literatura!");
            fclose(arquivoAntigo);
            Sleep(1000);
            return;
        }

        fread(&LiteraturaTemporaria, 1, sizeof(struct Literatura), arquivoAntigo);
        while (!feof(arquivoAntigo))
        {
            if (strcmp(LiteraturaTemporaria.tituloLiteratura, tituloLiteratura) == 0)
            {
                encontrada = 1;
            }
            else
            {
                fwrite(&LiteraturaTemporaria, 1, sizeof(struct Literatura), arquivoAtualizado);
            }
            fread(&LiteraturaTemporaria, 1, sizeof(struct Literatura), arquivoAntigo);
        }

        fclose(arquivoAntigo);
        fclose(arquivoAtualizado);

        remove("Literatura.dot");
        rename("temp.dot", "Literatura.dot");

        if (!encontrada)
        {
            printf("\n Nao foi possivel encontrar a Literatura...");
        }
        else
        {
            printf("\n Exclusao realizado com sucesso!");
        }

        Sleep(2000);
    }
    else
    {
        printf("\n Nenhuma Literatura encontrada!");
        Sleep(2000);
    }
}
