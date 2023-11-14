#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    long i;
    int pid = getpid();
    printf("Inicio do processo. Processo Pid: %d - Pai do processo: %d\n", getpid(), getppid());
    for(i = 0; i < 20000000; i++){}
    // sleep(6);
    printf("\nFim do processo\n");

    return 0;
}
