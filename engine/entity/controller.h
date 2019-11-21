
Actor *possessedActor = NULL;

//Possúi um ator.
bool possess(Actor *actor){
    if(!actor || !actor->entity.controllable) return false;
    possessedActor = actor;
    return true;
}

//Despossúi um ator.
void unpossess(){
    possessedActor = NULL;
}

//Verifica se o ator em questão é o possuído.
bool is_actor_possessed(Actor *actor){
    if(!actor || !possessedActor) return false;
    return actor->id == possessedActor->id;
}

//Comunica uma tecla pressionada ao ator possúido.
void press_key(SDL_Keycode key){
    if(!possessedActor) return;
    possessedActor->entity.input_event(possessedActor, key);
}
