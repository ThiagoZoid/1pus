
Actor *possessedActor = NULL;

//Poss�i um ator.
bool possess(Actor *actor){
    if(!actor || !actor->entity.controllable) return false;
    possessedActor = actor;
    return true;
}

//Desposs�i um ator.
void unpossess(){
    possessedActor = NULL;
}

//Verifica se o ator em quest�o � o possu�do.
bool is_actor_possessed(Actor *actor){
    if(!actor || !possessedActor) return false;
    return actor->id == possessedActor->id;
}

//Comunica uma tecla pressionada ao ator poss�ido.
void press_key(SDL_Keycode key){
    if(!possessedActor) return;
    possessedActor->entity.input_event(possessedActor, key);
}
