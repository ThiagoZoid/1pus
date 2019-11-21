
static Actor *possessedActor = NULL;

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

//Comunica uma tecla pressionada ao ator poss�ido.
void press_key(SDL_Keycode key){
    if(!possessedActor) return;
    possessedActor->entity.input_event(possessedActor, key);
}
