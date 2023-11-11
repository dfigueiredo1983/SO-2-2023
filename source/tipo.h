#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include<unistd.h>
// #include <windows.h> // For linux #include<unistd.h>

typedef struct Processo
{
    int numero;
    char nome[100];
    int num_ticket;
    int tickets[4];
    time_t t_inicio;
    time_t t_final;
    int status;               // 0 - esperando, 1 - rodando, 2 finalizado
    struct Processo *proximo; /* aponta para o próximo elemento da lista */
} processo;