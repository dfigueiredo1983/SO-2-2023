#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    long i;

    for(i = 0; i < 20000000000; i++){} //30 segundos

    return 0;
}

