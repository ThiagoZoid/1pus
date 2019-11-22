#include <stdio.h>
#include <stdlib.h>

//Mensagem
#if defined(WIN32) || defined(WINDOWS)
#include <windows.h>
void MsgBox(char *s, char *t){
    MessageBox(0, s, t, 0);
}
#else
#include <unistd.h>
void MsgBox(char *s){
    char cmd[1024];
    sprintf(cmd, "xmessage -center \"%s\" -title \"%s\"", s, t);
    if(fork()==0){
        close(1); close(2);
        system(cmd);
        exit(0);
    }
}
#endif

//Define a seed de números aleatórios como o tempo atual.
void prepare_random_seed(){
    srand(time(0) * 0x9E3779BB);
}

//Retorna o módulo de um número (valor sempre positivo).
int absolute(int i){
    return i < 0 ? -i : i;
}
