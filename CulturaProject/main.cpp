//Universidade de Brasília. Novembro de 2015

//Daniel Farias Corre 15/0008163
//Leonardo Arthur Degolim Oliveira 14/0025171

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct exposicao
{
    char Exposicao_name [50];
    int Dia_evento;
    int Mes_evento;
    char Descricao [500];

};

int Exibir_menu(void);
void Criar_exposicao(void);
void Buscar_exposicao(void);
void Atualizar_descricao(void);
void Excluir_exposicao(void);

int main(void)
{
    int opcao;

    do
    {
        opcao = Exibir_menu();

        switch (opcao)
        {
        case 1:
            Criar_exposicao();
            break;
        case 2:
            Buscar_exposicao();
            break;
        case 3:
            Atualizar_descricao();
            break;
        case 4:
            Excluir_exposicao();
            break;
        case 5:
            printf("\n Encerrando...");
            break;
        default:
            printf("\n Opcao invalida");
        }
        Sleep(1000);
    } while (opcao != 5);

    return 0;
}
int Exibir_menu(void)
{
    int opcao;

    system("cls");

    printf("\tEXPOSICOES\n\n");
    printf(" 1. Criar Exposicao\n");
    printf(" 2. Buscar Exposicao\n");
    printf(" 3. Atualizar Descricao\n");
    printf(" 4. Excluir Exposicao\n");
    printf(" 5. Encerrar \n\n");
    printf(" Digite a opcao desejada: ");
    scanf("%d", &opcao);

    return opcao;
}

void Criar_exposicao(void)
{
    struct exposicao Minha_exposicao;
    FILE *arquivo;

    system("cls");

    printf("\tEXPOSICOES - CRIAR EXPOSICAO\n\n");
    printf(" Titulo da Exposicao:");
    fflush(stdin);
    gets(Minha_exposicao.Exposicao_name);
    printf(" Dia de Abertura da Exposicao: ");
    scanf("%d", &Minha_exposicao.Dia_evento);
    printf(" Mes de Abertura da Exposicao: ");
    scanf("%d", &Minha_exposicao.Mes_evento);
    printf(" Descricao: ");
    fflush(stdin);
    gets(Minha_exposicao.Descricao);
    printf(" Exposicao Criada com sucesso\n");
    Sleep(2000);

    arquivo = fopen("exposicao.dat", "ab");
    if (!arquivo)
    {
        arquivo = fopen("exposicao.dat", "wb");
    }

    fwrite(&Minha_exposicao, 1, sizeof(struct exposicao), arquivo);

    fclose(arquivo);
}

void Buscar_exposicao(void)
{
    int encontrado = 0;
    char buscado[50];
    struct exposicao Minha_exposicao;
    FILE *arquivo;

    system("cls");

    printf("\tEXPOSICOES - BUSCAR EXPOSICAO\n\n");
    printf(" Titulo da Exposicao: ");
    fflush(stdin);
    gets(buscado);

    arquivo = fopen("exposicao.dat", "rb");

    if(arquivo)
    {
        fread(&Minha_exposicao, 1, sizeof(struct exposicao), arquivo);
        while (!feof(arquivo))
        {
            if (strcmp(buscado, Minha_exposicao.Exposicao_name) == 0);
            {
                printf("\n Titulo da Exposicao: %s\n", Minha_exposicao.Exposicao_name);
                printf(" Data de Abertura: %d/%d\n", Minha_exposicao.Dia_evento, Minha_exposicao.Mes_evento);
                printf(" Descricao: %s", Minha_exposicao.Descricao);
                printf("\n\nPressione duas vezes 'Enter' para voltar ao menu inicial\n");
                getchar();
                encontrado = 1;
                break;
            }
            fread(&Minha_exposicao, 1, sizeof(struct exposicao), arquivo);
        }

        if(!encontrado)
        {
            printf("\n Exposicao nao encontrada!");
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
void Atualizar_descricao(void)
{
    int encontrado = 0;
    char Exposicao_name[30], Descricao[15];
    struct exposicao Exposicao_Temp;
    FILE *arquivoAntigo = NULL, *arquivoAtualizado = NULL;

    system("cls");

    printf("\tEXPOSICOES - ATUALIZAR EXPOSICAO\n\n");
    printf(" Titulo da Exposicao: ");
    fflush(stdin);
    gets(Exposicao_name);
    printf(" Nova Descricao: ");
    fflush(stdin);
    gets(Descricao);

    arquivoAntigo = fopen("exposicao.dat", "rb");
    if (arquivoAntigo)
    {
        arquivoAtualizado = fopen("temp.dat", "wb");
        if (!arquivoAtualizado)
        {
            printf("\n Falha na atualizacao da exposicao!");
            Sleep(1000);
            return;
        }

        fread(&Exposicao_Temp, 1, sizeof(struct exposicao), arquivoAntigo);
        while (!feof(arquivoAntigo))
        {
            if (strcmp(Exposicao_Temp.Exposicao_name, Exposicao_name) == 0)
            {
                strcpy(Exposicao_Temp.Descricao, Descricao);
                encontrado = 1;
            }
            fwrite(&Exposicao_Temp, 1, sizeof(struct exposicao), arquivoAtualizado);
            fread(&Exposicao_Temp, 1, sizeof(struct exposicao), arquivoAntigo);
        }

        fclose(arquivoAntigo);
        fclose(arquivoAtualizado);

        remove("exposicao.dat");
        rename("temp.dat", "exposicao.dat");

        if (!encontrado)
        {
            printf("\n Nao foi possivel encontrar a exposicao...");
        }
        else
        {
            printf("\n Atualizacao realizada com sucesso!");
        }

        Sleep(1000);
    }
    else
    {
        printf("\n Nenhuma exposicao encontrada!");
        Sleep(1000);
    }
}

void Excluir_exposicao(void)
{
    int encontrado = 0;
    char Exposicao_name[30];
    struct exposicao Exposicao_Temp;
    FILE *arquivoAntigo = NULL, *arquivoAtualizado = NULL;

    system("cls");

    printf("\tEXPOSICOES - EXCLUIR CONTEUDO\n\n");
    printf(" Nome da exposicao: ");
    fflush(stdin);
    gets(Exposicao_name);

    arquivoAntigo = fopen("exposicao.dat", "rb");
    if (arquivoAntigo)
    {
        arquivoAtualizado = fopen("temp.dat", "wb");
        if (!arquivoAtualizado)
        {
            printf("\n Falha na exclusao da exposicao!");
            fclose(arquivoAntigo);
            Sleep(1000);
            return;
        }

        fread(&Exposicao_Temp, 1, sizeof(struct exposicao), arquivoAntigo);
        while (!feof(arquivoAntigo))
        {
            if (strcmp(Exposicao_Temp.Exposicao_name, Exposicao_name) == 0)
            {
                encontrado = 1;
            }
            else
            {
                fwrite(&Exposicao_Temp, 1, sizeof(struct exposicao), arquivoAtualizado);
            }
            fread(&Exposicao_Temp, 1, sizeof(struct exposicao), arquivoAntigo);
        }

        fclose(arquivoAntigo);
        fclose(arquivoAtualizado);

        remove("exposicao.dat");
        rename("temp.dat", "exposicao.dat");

        if (!encontrado)
        {
            printf("\n Nao foi possivel encontrar a exposicao...");
        }
        else
        {
            printf("\n Exclusao realizada com sucesso!");
        }

        Sleep(2000);
    }
    else
    {
        printf("\n Nenhuma exposicao encontrada!");
        Sleep(2000);
    }
}
