#include <stdio.h>

#include "escalonador.h"

// ponteiro para a fila encadeada (ready e temp)
processo *cabeca = NULL, *corrente = NULL, *selecionado = NULL;

void escalonador(char *arquivo)
{
    if (!read_file(arquivo))
    {
        printf("Erro na leitura do arquivo\n");
    }

    // imprimir_lista();

    for (int i = 0; i < 5; i++)
    {
        loteria(i);
        printf("\n\n");
        imprimir_lista();
    }
}

boolean read_file(char *arquivo)
{
    FILE *file = fopen(arquivo, "rt");
    if (file == NULL) // printf("Problemas na abertura do arquivo\n");
        return FALSE;

    char *token, nome[100], *result, linha[100];
    int i = 0;

    while (!feof(file))
    {
        result = fgets(linha, 100, file);
        int num_token = 0;
        if (result)
        {
            // printf("Linha %d : %s", i, linha);
            token = strtok(linha, " \n");
            while (token)
            {
                if (num_token == 0)
                    strcpy(nome, token);

                if (num_token == 1)
                {
                    if ((*token - 48) == 1)
                    {
                        // avalia a prioridade do processo
                        if (!inserir_lista(i, nome, 1, 2, 0))
                            printf("Erro ao inserir elemento na lista");
                    }
                    if ((*token - 48) == 2)
                    {
                        // avalia a prioridade do processo
                        if (!inserir_lista(i, nome, 2, 3, 0))
                            printf("Erro ao inserir elemento na lista");
                    }
                    if ((*token - 48) == 3)
                    {
                        // avalia a prioridade do processo
                        if (!inserir_lista(i, nome, 3, 4, 0))
                            printf("Erro ao inserir elemento na lista");
                    }
                }
                num_token++;
                token = strtok(NULL, " \n");
            }
        }
        i++;
    }
    fclose(file);
    return TRUE;
}

boolean inserir_lista(int numero, char *nome, int prioridade, int ticket, int status)
{
    if (cabeca == NULL)
    { // lista ainda vazia, inserindo o primeiro elemento
        cabeca = (processo *)malloc(sizeof(processo));
        if (cabeca == NULL)
            exit(1);

        cabeca->numero = numero;
        strcpy(cabeca->nome, nome);
        cabeca->num_ticket = prioridade + 1;
        cabeca->status = status;
        cabeca->proximo = NULL;
        for (int i = 0; i <= prioridade; i++)
            cabeca->tickets[i] = 0;
        corrente = cabeca;
        return TRUE;
    }
    else
    {
        processo *noatual, *novono;
        noatual = corrente;
        while (noatual != NULL)
            noatual = noatual->proximo;

        novono = (processo *)malloc(sizeof(processo));
        if (novono == NULL)
            exit(1);

        novono->numero = numero;
        strcpy(novono->nome, nome);
        novono->num_ticket = prioridade + 1;
        novono->status = status;
        novono->proximo = NULL;
        for (int i = 0; i <= prioridade; i++)
            novono->tickets[i] = 0;
        corrente->proximo = novono;
        corrente = novono;
        return TRUE;
    }
    return FALSE;
}

void loteria(int num_processo)
{
    processo *iterador = cabeca;
    int n = 0, soma_tickets = 0;
    while (iterador != NULL) // somando os tickets
    {                        // devemos somar apenas os tickets dos processos em ready
        if (num_processo == iterador->numero)
            iterador->status = 1;

        if (iterador->status == 1)
            soma_tickets = soma_tickets + iterador->num_ticket;

        iterador = iterador->proximo;
    }

    // printf("\nSoma dos tickets: %d\n", soma_tickets);

    int universo_tickets[soma_tickets],
        temp;

    for (int i = 0; i < soma_tickets; i++)
        universo_tickets[i] = i;

    // printf("Antes do embaralhamento: ");
    // for (int i = 0; i < soma_tickets; i++)
    //     printf("%d - ", universo_tickets[i]);

    int aux = 0;
    srand((unsigned)time(NULL));
    for (int i = 0; i < soma_tickets; i++)
    {
        int temp = 0;
        aux = (int)(rand() % (soma_tickets - i));
        temp = universo_tickets[aux];
        universo_tickets[aux] = universo_tickets[i];
        universo_tickets[i] = temp;
    }

    // printf("Apos o embaralhamento: ");
    // for (int i = 0; i < soma_tickets; i++)
    //     printf("%d - ", universo_tickets[i]);

    iterador = cabeca;
    int j = 0;
    while (iterador != NULL) // distribuindo os valores para os processos com status == 1
    {
        if (iterador->status == 1)
        {
            for (int i = 0; i < iterador->num_ticket; i++)
            {
                iterador->tickets[i] = universo_tickets[j];
                // printf("%s, Tickts: %d, Valor ticket: %d, Status: %d\n", iterador->nome, iterador->num_ticket, iterador->tickets[i], iterador->status);
                j += 1;
            }
        }
        iterador = iterador->proximo;
    }

    // for (int i = 0; i < soma_tickets; i++)
    //     printf("%d\n", universo_tickets[i]);

    int num_sorteado = (int)(rand() % soma_tickets);
    printf("Numero sorteado: %d - ", num_sorteado);

    // procurar o processo na lista
    iterador = cabeca;
    while (iterador != NULL)
    {
        if (iterador->status == 1)
        {
            for (int i = 0; i < iterador->num_ticket; i++)
            {
                if (num_sorteado == iterador->tickets[i])
                {
                    printf("Processo selecionado: %s\n\n", iterador->nome);
                    selecionado = iterador;
                    break;
                }
            }
        }
        iterador = iterador->proximo;
    }
}

void imprimir_lista()
{
    processo *iterador = cabeca;
    printf("Apresentar a lista de elementos\n");
    while (iterador != NULL)
    {
        for (int i = 0; i, i < iterador->num_ticket; i++)
        {
            printf("%s, Numero do processo: %d, Qtde de Tickets: %d, Valor do ticket[%d]: %d, Status: %d\n", iterador->nome, iterador->numero, iterador->num_ticket, i, iterador->tickets[i], iterador->status);
        }
        iterador = iterador->proximo;
    }
}
