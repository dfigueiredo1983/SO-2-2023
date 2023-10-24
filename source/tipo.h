typedef struct Processo
{
    int numero;
    char nome[100];
    int prioridade;
    int ticket;
    struct Processo *proximo; /* aponta para o próximo elemento da lista */
} processo;