//Universidade de Brasília. Novembro de 2015

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Concerto
{
    char tituloConcerto[30];
    int diaConcerto;
    int mesConcerto;
    char Local[300];
};

int exibirMenuConcerto(void);
void criarConcerto(void);
void buscarConcerto(void);
void atualizarLocal(void);
void excluirConcerto(void);




int main(void)
{
    int opcao;

    do
    {
        opcao = exibirMenuConcerto();

        switch (opcao)
        {
        case 1:
            criarConcerto();
            break;
        case 2:
            buscarConcerto();
            break;
        case 3:
            atualizarLocal();
            break;
        case 4:
            excluirConcerto();
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

int exibirMenuConcerto(void)
{
    int opcao;

    system("cls");

    printf("\tConcertos\n\n");
    printf(" 1. Criar Concerto\n");
    printf(" 2. Buscar Concerto\n");
    printf(" 3. Atualizar Local\n");
    printf(" 4. Excluir Concerto\n");
    printf(" 5. Encerrar\n\n");
    printf(" Digite a opcao desejada: ");
    scanf("%d", &opcao);

    return opcao;
}

void criarConcerto(void)
{
    struct Concerto meuConcerto;
    FILE *arquivo;

    system("cls");

    printf("\tConcertos - CRIAR Concerto\n\n");
    printf(" Titulo do Concerto: ");
    fflush(stdin);
    gets(meuConcerto.tituloConcerto);
    printf(" Dia de Lancamento do Concerto: ");
    scanf("%d", &meuConcerto.diaConcerto);
    printf(" Mes de Lancamento do Concerto: ");
    scanf("%d", &meuConcerto.mesConcerto);
    printf(" Local: ");
    fflush(stdin);
    gets(meuConcerto.Local);
    printf("\n\nConcerto Criado com sucesso\n");
    Sleep (2000);

    arquivo = fopen("Concerto.dat", "ab");
    if (!arquivo)
    {
        arquivo = fopen("Concerto.dat", "wb");
    }

    fwrite(&meuConcerto, 1, sizeof(struct Concerto), arquivo);

    fclose(arquivo);
}

void buscarConcerto(void)
{
    int encontrado = 0;
    char busca[30];
    struct Concerto meuConcerto;
    FILE *arquivo;

    system("cls"); //

    printf("\tConcertos - BUSCAR Concerto\n\n");
    printf(" Titulo do Concerto: ");
    fflush(stdin);
    gets(busca);

    arquivo = fopen("Concerto.dat", "rb");

    if (arquivo)
    {
        fread(&meuConcerto, 1, sizeof(struct Concerto), arquivo);
        while (!feof(arquivo))
        {
            if (strcmp(busca, meuConcerto.tituloConcerto) == 0)
            {
                printf("\n Titulo do Concerto: %s\n", meuConcerto.tituloConcerto);
                printf(" Data de lancamento: %d/%d/%d\n", meuConcerto.diaConcerto, meuConcerto.mesConcerto);
                printf(" Local: %s", meuConcerto.Local);
                printf ("\n\nPressione duas vezes 'Enter' para voltar ao menu inicial\n");
                getchar();
                encontrado = 1;
                break;
            }
            fread(&meuConcerto, 1, sizeof(struct Concerto), arquivo);
        }

        if (!encontrado)
        {
            printf("\n Concerto nao encontrado!");
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

void atualizarLocal(void)
{
    int encontrado = 0;
    char tituloConcerto[30], Local[15];
    struct Concerto ConcertoTemporario;
    FILE *arquivoAntigo = NULL, *arquivoAtualizado = NULL;

    system("cls");

    printf("\tConcertos - ATUALIZAR Concerto\n\n");
    printf(" Titulo do Concerto: ");
    fflush(stdin);
    gets(tituloConcerto);
    printf(" Novo Local: ");
    fflush(stdin);
    gets(Local);

    arquivoAntigo = fopen("Concerto.dat", "rb");
    if (arquivoAntigo)
    {
        arquivoAtualizado = fopen("temp.dat", "wb");
        if (!arquivoAtualizado)
        {
            printf("\n Falha na atualizacao do Concerto!");
            Sleep(1000);
            return;
        }

        fread(&ConcertoTemporario, 1, sizeof(struct Concerto), arquivoAntigo);
        while (!feof(arquivoAntigo))
        {
            if (strcmp(ConcertoTemporario.tituloConcerto, tituloConcerto) == 0)
            {
                strcpy(ConcertoTemporario.Local, Local);
                encontrado = 1;
            }
            fwrite(&ConcertoTemporario, 1, sizeof(struct Concerto), arquivoAtualizado);
            fread(&ConcertoTemporario, 1, sizeof(struct Concerto), arquivoAntigo);
        }

        fclose(arquivoAntigo);
        fclose(arquivoAtualizado);

        remove("Concerto.dat");
        rename("temp.dat", "Concerto.dat");

        if (!encontrado)
        {
            printf("\n Nao foi possivel encontrar o Concerto...");
        }
        else
        {
            printf("\n Atualizacao realizada com sucesso!");
        }

        Sleep(1000);
    }
    else
    {
        printf("\n Nenhum Concerto encontrado!");
        Sleep(1000);
    }
}

void excluirConcerto(void)
{
    int encontrado = 0;
    char tituloConcerto[30];
    struct Concerto ConcertoTemporario;
    FILE *arquivoAntigo = NULL, *arquivoAtualizado = NULL;

    system("cls");

    printf("\tConcertos - EXCLUIR Local\n\n");
    printf(" Nome do Concerto: ");
    fflush(stdin);
    gets(tituloConcerto);

    arquivoAntigo = fopen("Concerto.dat", "rb");
    if (arquivoAntigo)
    {
        arquivoAtualizado = fopen("temp.dat", "wb");
        if (!arquivoAtualizado)
        {
            printf("\n Falha na exclusao do Concerto!");
            fclose(arquivoAntigo);
            Sleep(1000);
            return;
        }

        fread(&ConcertoTemporario, 1, sizeof(struct Concerto), arquivoAntigo);
        while (!feof(arquivoAntigo))
        {
            if (strcmp(ConcertoTemporario.tituloConcerto, tituloConcerto) == 0)
            {
                encontrado = 1;
            }
            else
            {
                fwrite(&ConcertoTemporario, 1, sizeof(struct Concerto), arquivoAtualizado);
            }
            fread(&ConcertoTemporario, 1, sizeof(struct Concerto), arquivoAntigo);
        }

        fclose(arquivoAntigo);
        fclose(arquivoAtualizado);

        remove("Concerto.dat");
        rename("temp.dat", "Concerto.dat");

        if (!encontrado)
        {
            printf("\n Nao foi possivel encontrar o Concerto...");
        }
        else
        {
            printf("\n Exclusao realizada com sucesso!");
        }

        Sleep(2000);
    }
    else
    {
        printf("\n Nenhum Concerto encontrado!");
        Sleep(2000);
    }
}
