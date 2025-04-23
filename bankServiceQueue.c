#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
#define SUCCESS 1

int senha = 0;

typedef struct Cliente
{
    int numeroSenha;
    char nome[MAX_NOME];
    struct Cliente* prox;
} Cliente;

typedef struct
{
    Cliente* inicio;
    Cliente* fim;
} FilaDinamica;

void inicializarFilaDinamica(FilaDinamica *fila);
void iniciarMenu(FilaDinamica *fila);
void adicionarCliente(FilaDinamica *fila);
void imputarDadosCliente(FilaDinamica *fila);
void tratarDadoImputado(char *campo);
void limparBuffer();
void enfileirarFilaDinamica(FilaDinamica* fila, Cliente cliente);
void desenfileirarFilaDinamica(FilaDinamica* fila);
void imprimirProximoCliente(FilaDinamica* fila);
void imprimirTodosClientes(FilaDinamica* fila);
void imprimirOpcaoInvalida();
void imprimirFilaVazia();
void imprimirClienteSalvo();
void imprimirAtendimendoConcluido();
void imprimirProgramaFinalizado();

int main()
{
    FilaDinamica fila;
    inicializarFilaDinamica(&fila);
    iniciarMenu(&fila);
    return SUCCESS;
}

void iniciarMenu(FilaDinamica *fila)
{
    char entrada[10];
    int resultScan = -1;

    while (resultScan != 5)
    {
        printf("\n----------------------------------------------------\n");
        printf("---------------------- MENU ------------------------\n");
        printf("1 - Adicionar cliente a fila\n");
        printf("2 - Atender proximo cliente\n");
        printf("3 - Mostrar proximo cliente\n");
        printf("4 - Mostrar todos os clientes\n");
        printf("5 - Sair \n");
        printf("Escolha: ");

        fgets(entrada, sizeof(entrada), stdin);
        resultScan = atoi(entrada);

        switch (resultScan)
        {
        case 1:
            adicionarCliente(fila);
            break;
        case 2:
            desenfileirarFilaDinamica(fila);
            break;
        case 3:
            imprimirProximoCliente(fila);
            break;
        case 4:
            imprimirTodosClientes(fila);
            break;
        case 5:
            break;
        default:
            imprimirOpcaoInvalida();
        }
    }

    imprimirProgramaFinalizado();
}

void adicionarCliente(FilaDinamica *fila)
{
    imputarDadosCliente(fila);
}

void imputarDadosCliente(FilaDinamica *fila)
{
    printf("\n-----------------------------------------------------\n");
    printf("---------------- Adicione o seu nome ----------------\n");

    Cliente cliente;

    printf("Nome: ");
    fgets(cliente.nome, sizeof(cliente.nome), stdin);
    tratarDadoImputado(cliente.nome);
    cliente.numeroSenha = senha++;

    enfileirarFilaDinamica(fila, cliente);
    imprimirClienteSalvo();
}

void tratarDadoImputado(char *campo)
{
    if (strchr(campo, '\n') == NULL)
    {
        limparBuffer();
    }
    else
    {
        campo[strcspn(campo, "\n")] = '\0';
    }
}

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inicializarFilaDinamica(FilaDinamica *fila)
{
    fila->inicio = NULL;
    fila->fim = NULL;
}

void enfileirarFilaDinamica(FilaDinamica* fila, Cliente cliente)
{
    Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));

    if (novoCliente == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    strcpy(novoCliente->nome, cliente.nome);
    novoCliente->numeroSenha = cliente.numeroSenha;
    novoCliente->prox = NULL;

    if (fila->fim == NULL)
    {
        fila->inicio = novoCliente;
    }
    else
    {
        fila->fim->prox = novoCliente;
    }
    fila->fim = novoCliente;
}

void desenfileirarFilaDinamica(FilaDinamica* fila)
{
    if (fila->inicio == NULL)
    {
        imprimirFilaVazia();
        return;
    }

    Cliente* temp = fila->inicio;
    fila->inicio = fila->inicio->prox;

    if (fila->inicio == NULL)
    {
        fila->fim = NULL;
    }

    imprimirAtendimendoConcluido();
    free(temp);
}

void imprimirProximoCliente(FilaDinamica* fila)
{
    Cliente* atual = fila->inicio;

    if (atual != NULL)
    {
        printf("\n-----------------------------------------------------\n");
        printf("-------------------Proximo Cliente ------------------\n");
        printf("Senha: %d\n", atual->numeroSenha);
        printf("Nome: %s\n", atual->nome);
        printf("-----------------------------------------------------\n");
    }
    else
    {
        imprimirFilaVazia();
    }
}

void imprimirTodosClientes(FilaDinamica* fila)
{
    Cliente* atual = fila->inicio;

    if (atual != NULL)
    {
        printf("\n----------------------------------------------------\n");
        printf("--------------------- Clientes ---------------------\n");

        while (atual != NULL)
        {
            printf("----------------------------------------------------\n");
            printf("Senha: %d\n", atual->numeroSenha);
            printf("Nome: %s\n", atual->nome);
            atual = atual->prox;
        }
        printf("----------------------------------------------------\n\n");
    }
    else
    {
        imprimirFilaVazia();
    }
}

void imprimirOpcaoInvalida()
{
    printf("\n-----------------------------------------------------\n");
    printf("------------------ Opcao Invalida! ------------------\n");
    printf("-----------------------------------------------------\n\n");
}

void imprimirFilaVazia()
{
    printf("\n-----------------------------------------------------\n");
    printf("------------------- Fila Vazia! --------------------\n");
    printf("-----------------------------------------------------\n\n");
}

void imprimirClienteSalvo()
{
    printf("\n-----------------------------------------------------\n");
    printf("------------------ Cliente Salvo! -------------------\n");
    printf("-----------------------------------------------------\n\n");
}

void imprimirAtendimendoConcluido()
{
    printf("\n-----------------------------------------------------\n");
    printf("----------------- Cliente Atendido! -----------------\n");
    printf("-----------------------------------------------------\n\n");
}

void imprimirProgramaFinalizado()
{
    printf("\nPrograma finalizado!\n");
}
