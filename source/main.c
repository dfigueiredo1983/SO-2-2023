#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

struct itimerval timer;
struct timespec tempoRestante;
pid_t filho_pid;  // Variável para armazenar o PID do processo filho
int contador = 0;  // Contador para controlar a contagem de 6 segundos

void interropeProcessosFilho(pid_t signum) {
    printf("Temporizador expirou. Enviando SIGSTOP para PID %d.\n", filho_pid);
    kill(signum, SIGSTOP);
}

void continuarProcessoFilho(pid_t signum) {
    printf("Continuando o processo filho com PID %d.\n", filho_pid);
    kill(signum, SIGCONT);
}

int temporizadorExpirou(int signum) {
    // A cada 6 segundos, retorna true
    if (contador == 6) {
        contador = 0;
        return 1;
    } else {
        contador++;
        return 0;
    }
}

void iniciarTemporizador() {
    struct sigaction sa;
    sa.sa_handler = temporizadorExpirou;
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);

    tempoRestante.tv_sec = 1;
    tempoRestante.tv_nsec = 0;

    timer.it_interval.tv_sec = 1;  // Intervalo para 1 segundo
    timer.it_interval.tv_usec = 0;
    timer.it_value.tv_sec = tempoRestante.tv_sec;
    timer.it_value.tv_usec = tempoRestante.tv_nsec / 1000;

    setitimer(ITIMER_REAL, &timer, NULL);
}

int main() {
    iniciarTemporizador();
    // Cria um novo processo filho
    if ((filho_pid = fork()) == -1) {
        perror("Erro ao criar processo filho");
        exit(EXIT_FAILURE);
    }

    // Código do processo pai e do filho
    if (filho_pid == 0) {
        // Código do processo filho
        // Sera inclusido a logica de processos filhos aqui
        execlp("./filho_exec", "./filho_exec", NULL);
        perror("Erro ao executar o processo filho");
        exit(EXIT_FAILURE);
    } else {
        // Código do processo pai
        // Configuração do tratamento de sinais para continuar o processo filho
        contador = 0;
        int continueFlag = 1;
        while (continueFlag) {
            int status;
            pause();
            pid_t result = waitpid(filho_pid, &status, WNOHANG);
            if(result != 0) {
                // Aguarda o processo filho terminar completamente
                printf("Matando o Zumbi\n");
                continueFlag = 0;
            }
            else if (contador == 6) {
                contador = 0;
                printf("Quantum 6s\n");
                interropeProcessosFilho(filho_pid);
                //Chama loteria
                printf("Continuando o processo filho com PID %d.\n", filho_pid);
                kill(filho_pid, SIGCONT);
            }
        }
        // Aguarda o processo filho parar
        // printf("Continuando o processo filho com PID %d.\n", filho_pid);
        // kill(filho_pid, SIGCONT);
        printf("Finalizando processo pai.\n");
    }

    return 0;
}