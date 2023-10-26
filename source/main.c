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
