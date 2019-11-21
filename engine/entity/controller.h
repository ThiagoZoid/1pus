
static Actor *possessedActor = NULL;

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

//Comunica uma tecla pressionada ao ator possúido.
void press_key(SDL_Keycode key){
    if(!possessedActor) return;
    possessedActor->entity.input_event(possessedActor, key);
}
