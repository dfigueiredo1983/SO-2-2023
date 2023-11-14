Escalonador por loteria

Criado para ser usado em sistema operacional LINUX

Inicialmente deve ser criado o arquivo processo que irá executar um for por 30 segundos aproximadamente
gcc ./processo.c -O0 -o processo
Para verificar se o programa está executando normalmente e o tempo de execução use
time ./processo
que irá apresentar o tempo de execução

Antes de execução o program a do escalonador verifique se o endereço do executável "processo" está correto no arquivo escalonador.c dentro da função criar_processo.
para criar o executavel use o comando: gcc ./main.c ./escalonador.c -O0 -o programa
para executar use o comando ./programa ./processos_1.txt

pode ser usado qualquer um dos 3 arquivos de testes
./processos_1.txt // possui 1 processo de teste
./processos_5.txt // possui 5 processo de teste
./processos_10.txt // possui 10 processo de teste

Ao final da execução dos processos é apresentando o tempo de execução total do escalonador e o tempo de execução de cada processo.
O tempo de execução de cada processo é medido do momento em que ele é colocado para executar pela primeira vez até o momento em que ele é encerrado
