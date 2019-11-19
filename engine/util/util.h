//Define a seed de números aleatórios como o tempo atual.
void prepare_random_seed(){
    srand(time(0) * 0x9E3779BB);
}

//Retorna o módulo de um número (valor sempre positivo).
int absolute(int i){
    return i < 0 ? -i : i;
}