#include <sys/signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void sigalrm_handler(){
    printf("Quantum\n");
    alarm(6);
}

int main(){

    time_t t_inicio, t_final, now;

    time(&t_inicio);
    printf("\nInicio do programa: %ld\n", t_inicio);

    printf("Cria o primeiro processo\n");
    sigalrm_handler();
    signal(SIGALRM, sigalrm_handler);
    alarm(6);

    int cont = 10;

    while(cont > 0){
        printf("Espera por 2 segundos e executa novamente\n");
        for(int i = 0; i < 2; i++){
            sleep(1);
        }
        time(&now);
        // printf("Today is %s\n", ctime(&now));
        cont--;
    }

    time(&t_final);
    printf("Final do programa: %ld\n", t_final);

    printf("Tempo de execução: %ld\n", (t_final - t_inicio));

    return 0;
}