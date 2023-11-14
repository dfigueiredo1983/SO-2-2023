#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

typedef struct Processo
{
    // pid_t pid;
    int pid;
    int numero;
    char nome[100];
    int num_ticket;
    int tickets[4];
    long t_inicio;
    long t_final;
    int status;               // 0 - esperando, 1 - rodando, 2 finalizado
    struct Processo *proximo; /* aponta para o próximo elemento da lista */
} processo;
