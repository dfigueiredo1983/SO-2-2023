#include "stdio.h"

#include "escalonador.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Erro na passagem dos parametros");
        exit(1);
    }

    escalonador(argv[1]);

    return 0;
}

// void inserir(int numero, char *nome, int prioridade, int ticket, int status)
// {
//     if (cabeca == NULL)
//     { // lista ainda vazia, inserindo o primeiro elemento
//         cabeca = (processo *)malloc(sizeof(processo));
//         if (cabeca == NULL)
//             exit(1);

//         cabeca->numero = numero;
//         strcpy(cabeca->nome, nome);
//         cabeca->num_ticket = prioridade + 1;
//         cabeca->status = status;
//         cabeca->proximo = NULL;
//         corrente = cabeca;
//     }
//     else
//     {
//         processo *noatual, *novono;
//         noatual = corrente;
//         while (noatual != NULL)
//             noatual = noatual->proximo;

//         novono = (processo *)malloc(sizeof(processo));
//         if (novono == NULL)
//             exit(1);

//         novono->numero = numero;
//         strcpy(novono->nome, nome);
//         novono->num_ticket = prioridade + 1;
//         novono->status = status;
//         novono->proximo = NULL;
//         corrente->proximo = novono;
//         corrente = novono;
//     }
// }

// void loteria(int num_processo)
// {
//     processo *iterador = cabeca;
//     int n = 0, soma_tickets = 0;
//     while (iterador != NULL)
//     {
//         if (num_processo == iterador->numero)
//         {
//             iterador->status = 1;
//         }
//         soma_tickets = soma_tickets + iterador->num_ticket;
//         iterador = iterador->proximo;
//     }

//     int universo_tickets[soma_tickets],
//         temp;

//     for (int i = 0; i < soma_tickets; i++)
//         universo_tickets[i] = i;

//     int aux = 0;
//     srand((unsigned)time(NULL));
//     for (int i = 0; i < soma_tickets; i++)
//     {
//         int temp = 0;
//         aux = (int)(rand() % (soma_tickets - i));
//         temp = universo_tickets[aux];
//         universo_tickets[aux] = universo_tickets[i];
//         universo_tickets[i] = temp;
//     }

//     iterador = cabeca;
//     int j = 0;
//     while (iterador != NULL)
//     {
//         for (int i = 0; i < iterador->num_ticket; i++)
//         {
//             iterador->tickets[i] = universo_tickets[j];
//             printf("%s, Tickts: %d, Valor ticket: %d, Status: %d\n", iterador->nome, iterador->num_ticket, iterador->tickets[i], iterador->status);
//             j += 1;
//         }
//         iterador = iterador->proximo;
//     }

//     int num_sorteado = (int)(rand() % soma_tickets);
//     printf("Numero sorteado: %d - ", num_sorteado);

//     // procurar o processo na lista
//     iterador = cabeca;
//     while (iterador != NULL)
//     {
//         for (int i = 0; i < iterador->num_ticket; i++)
//         {
//             if (num_sorteado == iterador->tickets[i])
//             {
//                 printf("Processo selecionado: %s\n\n", iterador->nome);
//                 selecionado = iterador;
//                 break;
//             }
//         }
//         iterador = iterador->proximo;
//     }
// }

// void listar()
// {
//     processo *iterador = cabeca;
//     printf("\nApresentar a lista de elementos\n");
//     while (iterador != NULL)
//     {
//         printf("%s, Numero: %d, Tickets: %d\n", iterador->nome, iterador->numero, iterador->num_ticket);
//         iterador = iterador->proximo;
//     }
// }
