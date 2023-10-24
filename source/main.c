#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tipo.h"

// ponteiro genérico para as funções inserir e listar a fila
processo *cabeca = NULL;
processo *corrente = NULL;

// ponteiro para a fila encadeada de cada prioridade
processo *cabeca_p1 = NULL, *cabeca_p2 = NULL, *cabeca_p3 = NULL;
processo *corrente_p1 = NULL, *corrente_p2 = NULL, *corrente_p3 = NULL;

void inserir(int numero, char *nome, int prioridade, int ticket);
void listar();

int main(int argc, char *argv[])
{
    FILE *arquivo;
    char linha[100];
    char *result;
    int i = 0;

    int numero;
    char nome[100];
    int prioridade;
    int ticket;

    arquivo = fopen(argv[1], "rt");
    if (arquivo == NULL)
    {
        // printf("Problemas na abertura do arquivo\n");
        return -1;
    }

    char *token;
    while (!feof(arquivo))
    {
        result = fgets(linha, 100, arquivo);
        int num_token = 0;
        if (result)
        {
            // printf("\n\nLinha %d : %s", i, linha);
            token = strtok(linha, " \n");
            while (token)
            {
                if (num_token == 0)
                {
                    strcpy(nome, token);
                }
                if (num_token == 1)
                {
                    if ((*token - 48) == 1) // avalia a prioridade do processo
                    {
                        // printf("Prioridade 1\n");
                        // printf("Nome do processo: %s\n", nome_processo);
                        inserir(1, nome, 1, 2);
                    }
                    if ((*token - 48) == 2) // avalia a prioridade do processo
                    {
                        inserir(1, nome, 2, 3);
                        // printf("Prioridade 2\n");
                    }
                    if ((*token - 48) == 3) // avalia a prioridade do processo
                    {
                        inserir(1, nome, 3, 4);
                        // printf("Prioridade 3\n");
                        // printf("Nome do processo: %s\n", nome_processo);
                    }
                }
                num_token++;
                token = strtok(NULL, " \n");
            }
        }
        i++;
    }

    fclose(arquivo);

    listar();

    return 0;
}

void inserir(int numero, char *nome, int prioridade, int ticket)
{
    if (prioridade == 1)
    {
        cabeca = cabeca_p1;
        corrente = corrente_p1;
    }
    if (prioridade == 2)
    {
        cabeca = cabeca_p2;
        corrente = corrente_p2;
    }
    if (prioridade == 3)
    {
        cabeca = cabeca_p3;
        corrente = corrente_p3;
    }

    if (cabeca == NULL)
    { // lista ainda vazia, inserindo o primeiro elemento
        cabeca = (processo *)malloc(sizeof(processo));
        if (cabeca == NULL)
            exit(1);

        cabeca->numero = numero;
        strcpy(cabeca->nome, nome);
        cabeca->prioridade = prioridade;
        cabeca->ticket = ticket;
        cabeca->proximo = NULL;
        corrente = cabeca;

        printf("Cabeca: %s", cabeca->nome);
        // printf("Cabeca de p1: %s", cabeca_p1->nome);
    }
    else
    {
        processo *noatual, *novono;
        noatual = cabeca;
        while (noatual != NULL)
            noatual = noatual->proximo;

        novono = (processo *)malloc(sizeof(processo));
        if (novono == NULL)
            exit(1);

        novono->numero = numero;
        strcpy(novono->nome, nome);
        novono->prioridade = prioridade;
        novono->ticket = ticket;
        novono->proximo = NULL;
        corrente->proximo = novono;
        corrente = novono;
    }

    if (prioridade == 1)
    {
        cabeca_p1 = cabeca;
        corrente_p1 = corrente;
    }
    if (prioridade == 2)
    {
        cabeca_p2 = cabeca;
        corrente_p2 = corrente;
    }
    if (prioridade == 3)
    {
        cabeca_p3 = cabeca;
        corrente_p3 = corrente;
    }
}

void listar()
{
    processo *iterador = NULL;

    printf("\n\n\n\n\nApresentar a lista de elementos com prioridade 1\n");
    iterador = cabeca_p1;
    while (iterador != NULL)
    {
        printf("Elemento da lista encadeada: %s\n", iterador->nome);
        iterador = iterador->proximo;
    }

    printf("\n\n\n\n\nApresentar a lista de elementos com prioridade 2\n");
    iterador = cabeca_p2;
    while (iterador != NULL)
    {
        printf("Elemento da lista encadeada: %s\n", iterador->nome);
        iterador = iterador->proximo;
    }

    printf("\n\n\n\n\nApresentar a lista de elementos com prioridade 3\n");
    iterador = cabeca_p3;
    while (iterador != NULL)
    {
        printf("Elemento da lista encadeada: %s\n", iterador->nome);
        iterador = iterador->proximo;
    }
}