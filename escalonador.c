#include <stdio.h>

#include "escalonador.h"

// ponteiro para a fila encadeada (ready e temp)
processo *cabeca = NULL, *corrente = NULL, *selecionado = NULL, *executando = NULL;
int quantidade_processos = 0;

bool read_file(char *arquivo)
{
    FILE *file = fopen(arquivo, "rt");
    if (file == NULL) // printf("Problemas na abertura do arquivo\n");
        return false;

    char *token, nome[100], *result, linha[100];
    int i = 0;

    while (!feof(file))
    {
        result = fgets(linha, 100, file);
        int num_token = 0;
        if (result)
        {
            // printf("Linha %d : %s", i, linha);
            token = strtok(linha, " \n");
            while (token)
            {
                if (num_token == 0)
                    strcpy(nome, token);

                if (num_token == 1)
                {
                    if ((*token - 48) == 1)
                    {
                        // avalia a prioridade do processo
                        if (!inserir_lista(i, nome, 1, 2, 0, 0, 0, 0))
                            printf("Erro ao inserir elemento na lista");
                    }
                    if ((*token - 48) == 2)
                    {
                        // avalia a prioridade do processo
                        if (!inserir_lista(i, nome, 2, 3, 0, 0, 0, 0))
                            printf("Erro ao inserir elemento na lista");
                    }
                    if ((*token - 48) == 3)
                    {
                        // avalia a prioridade do processo
                        if (!inserir_lista(i, nome, 3, 4, 0, 0, 0, 0))
                            printf("Erro ao inserir elemento na lista");
                    }
                }
                num_token++;
                token = strtok(NULL, " \n");
            }
        }
        i++;
    }
    fclose(file);
    return true;
}

bool inserir_lista(int numero, char *nome, int prioridade, int ticket, int status, int pid, int t_final, int t_inicio)
{
    if (cabeca == NULL)
    { // lista ainda vazia, inserindo o primeiro elemento
        cabeca = (processo *)malloc(sizeof(processo));
        if (cabeca == NULL)
            exit(1);

        cabeca->numero = numero;
        strcpy(cabeca->nome, nome);
        cabeca->num_ticket = prioridade + 1;
        cabeca->status = status;
        cabeca->pid = pid;
        cabeca->proximo = NULL;
        cabeca->t_final = t_final;
        cabeca->t_inicio = t_inicio;
        for (int i = 0; i <= prioridade; i++)
            cabeca->tickets[i] = 0;
        corrente = cabeca;
        quantidade_processos++; 
        return true;
    }
    else
    {
        processo *noatual, *novono;
        noatual = corrente;
        while (noatual != NULL)
            noatual = noatual->proximo;

        novono = (processo *)malloc(sizeof(processo));
        if (novono == NULL)
            exit(1);

        novono->numero = numero;
        strcpy(novono->nome, nome);
        novono->num_ticket = prioridade + 1;
        novono->status = status;
        novono->pid = pid;
        novono->proximo = NULL;
        novono->t_final = t_final;
        novono->t_inicio = t_inicio;

        for (int i = 0; i <= prioridade; i++)
            novono->tickets[i] = 0;
        corrente->proximo = novono;
        corrente = novono;
        quantidade_processos++;
        return true;
    }
    return false;
}

void criar_processo(){
    processo *iterador = cabeca;
    int status;
    time_t t_inicio;

    // printf("\n\nAlterar o status do processo a cada 2 segundos\n");
    while (iterador != NULL)
    {
        if(iterador->status == 0){ // Processo em waiting, devemos criar um processo para ele
            pid_t pid_filho;
            pid_filho = fork();
            if (pid_filho == -1) {
                printf("Erro na criação do processo: %s", iterador->nome);
                exit(EXIT_FAILURE);
            }

            if (pid_filho == 0) { /* Filho executando */
                // printf("\nChild PID is %ld\n", (long) getpid());
                if (execl("/home/vboxuser/Documents/SO/programas/trabalho/processo", " ", (char *) NULL) < 0){
                    printf("erro no execl = %d\n", errno);
                }
            } else { /* Pai executando */
                iterador->status = 1;
                time(&t_inicio);
                iterador->t_inicio = t_inicio;
                iterador->pid = pid_filho;
                kill(pid_filho, SIGSTOP);
                // printf("Processo criado com sucesso. pid: %ld - ppid: %ld\n", (long) pid_filho, (long) getppid());
                break;
            }
        }
        iterador = iterador->proximo;
    }
}

void loteria()
{
    processo *iterador = cabeca;
    int soma_tickets = 0;

    while (iterador != NULL) // somando os tickets
    {                        // devemos somar apenas os tickets dos processos em ready
        if(iterador->status == 1 && iterador->pid != 0)
            soma_tickets = soma_tickets + iterador->num_ticket;
        iterador = iterador->proximo;
    }

    // printf("\nSoma dos tickets: %d\n", soma_tickets);

    if(soma_tickets > 0){
        int universo_tickets[soma_tickets];

        for (int i = 0; i < soma_tickets; i++)
            universo_tickets[i] = i;

        // // printf("Antes do embaralhamento: ");
        // // for (int i = 0; i < soma_tickets; i++)
        // //     printf("%d - ", universo_tickets[i]);

        int aux = 0;
        srand((unsigned)time(NULL));
        for (int i = 0; i < soma_tickets; i++)
        {
            int temp = 0;
            aux = (int)(rand() % (soma_tickets - i));
            temp = universo_tickets[aux];
            universo_tickets[aux] = universo_tickets[i];
            universo_tickets[i] = temp;
        }

        // // printf("Apos o embaralhamento: ");
        // // for (int i = 0; i < soma_tickets; i++)
        // //     printf("%d - ", universo_tickets[i]);

        iterador = cabeca;
        int j = 0;
        while (iterador != NULL) // distribuindo os valores para os processos com status == 1
        {
            if (iterador->status == 1)
            {
                for (int i = 0; i < iterador->num_ticket; i++)
                {
                    iterador->tickets[i] = universo_tickets[j];
                    // printf("%s, Tickts: %d, Valor ticket: %d, Status: %d\n", iterador->nome, iterador->num_ticket, iterador->tickets[i], iterador->status);
                    j += 1;
                }
            }
            iterador = iterador->proximo;
        }

        // // for (int i = 0; i < soma_tickets; i++)
        // //     printf("%d\n", universo_tickets[i]);

        int num_sorteado = (int)(rand() % soma_tickets);
        // printf("Numero sorteado: %d\n", num_sorteado);

        // procurar o processo na lista
        iterador = cabeca;
        while (iterador != NULL)
        {
            if (iterador->status == 1)
            {
                for (int i = 0; i < iterador->num_ticket; i++)
                {
                    if (num_sorteado == iterador->tickets[i])
                    {
                        // printf("Processo selecionado: %s - status: %d - pid: %d\n", iterador->nome, iterador->status, iterador->pid);
                        selecionado = iterador;
                        break;
                    }
                }
            }
            iterador = iterador->proximo;
        }
    }else{
        printf("Não existe processos para serem criados\n");
    }
}

bool verificar_status(){
    processo *iterador = cabeca;
    bool retorno = true;
    // printf("\n\n\nVerificar Status\n");
    while(iterador != NULL){
        // printf("Processo: %s - Pid: %d - Status: %d\n\n", iterador->nome, iterador->pid, iterador->status);

        if(iterador->status == -1)
            retorno = retorno && true;
        else
            retorno = retorno && false;
        iterador = iterador->proximo;
    }
    // if(retorno)
    //     // printf("Todos os processos tem status -1\n\n");
    // else
    //     // printf("Algum processo tem status != -1\n\n");

    return retorno;
}

void matar_zumbie(){
    processo *iterador = cabeca;
    int status;
    time_t t_final;
    system("clear");
    printf("\nProcessos\n");
    while (iterador != NULL)
    {
        // printf("Processo: %s - pid: %d\n", iterador->nome, iterador->pid);    
        if(iterador->pid != 0){
            int estado_processo = waitpid(iterador->pid, &status, WNOHANG);

            if(estado_processo == iterador->pid){
                iterador->status = -1;
                time(&t_final);
                iterador->t_final = t_final;
                kill(iterador->pid, SIGTERM);
            }

            // printf("Processo: %s - pid: %d - Status: %d", iterador->nome, iterador->pid, iterador->status);
            printf("Processo: %s - pid: %d", iterador->nome, iterador->pid);

            if(selecionado->pid == iterador->pid)
                printf(" - Processo em execução\n");
            else if(iterador->status == 1)
                printf(" - Processo aguardando\n");
            else if(iterador->status == -1)
                printf(" - Processo encerrado\n");
            else
                printf("\n");


        }
        iterador = iterador->proximo;
    }
}

void sigalrm_handler(){ // para o processo atual, roda a loteria e executa o processo selecionado
    // printf("\n\n\nQuantum. Rodando a loteria + stop/cont\n");
    if(executando != NULL){ // pararando o processo em executando
        kill(executando->pid, SIGSTOP);
    }

    loteria();

    executando = selecionado;
    kill(executando->pid, SIGCONT);

    alarm(6);
}

void escalonador(){

    time_t time_start, time_now, markspan_inicio, markspan_final;
    time(&time_start);
    time(&time_now);
    time(&markspan_inicio);

    // printf("Cria processo, em: %ld\n", time_now - time_start);
    criar_processo();
    sigalrm_handler();
    signal(SIGALRM, sigalrm_handler);
    alarm(6);

    for(int i = 0; i < 2; i++){
        matar_zumbie();
        sleep(1);
    }

    while(1){
        //ler a lista e criar os processos a cada 2 segundos
        time(&time_now);
        // printf("Cria processo, em: %ld\n", time_now - time_start);
        criar_processo(); // cria processo se ainda não existir
        for(int i = 0; i < 2; i++){
            matar_zumbie(); // deve ser executado dentro do loop com menos de 1 segundo
            sleep(1);
            // usleep(1000);
        }
        if(verificar_status()){
            processo *iterador = cabeca;
            time(&markspan_final);
            system("clear");
            printf("\n\nMAKESPAN: %ld segundos\n\n", markspan_final - markspan_inicio);

            while(iterador != NULL){
                printf("Processo: %s - ", iterador->nome);
                printf("Pid: %d - ", iterador->pid);
                printf("tempo de execução: %ld segundos\n", iterador->t_final - iterador->t_inicio);
                iterador = iterador->proximo;
            }
            exit(1);
        }
    }
}