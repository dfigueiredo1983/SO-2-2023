// INTEGRANTES DO GRUPO
// Daniel do Carmo Figueiredo 160057922
// Davi Matheus Garcia 160070040
// Pedro Fernandes 180108069

#include "stdio.h"

#include "escalonador.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Erro na passagem dos parametros.\n");
        exit(1);
    }

    if (!read_file(argv[1]))
    {
        printf("Erro na leitura do arquivo\n");
    }

    escalonador();

    return 0;
}
