// filho.c
#include <stdio.h>
#include <unistd.h>

int main() {
    for (int i = 0; i < 23; i++) {
        printf("Processo filho em execucao...\n");

        sleep(1);
    }

    return 0;
}