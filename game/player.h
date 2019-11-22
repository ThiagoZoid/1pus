//Entidade do Player.
#define playerEntity (Entity){ playerID, true, true, playerSprite, NULL, on_player_destroy, on_player_move, on_player_collide, on_player_input }

//Variáveis do jogador (movimentos, moedas adquiridas e flechas).
typedef struct playerVars{
    int movements;
    int golds;
    int arrows;
} PlayerVars;

//Registra a pontuação do jogador.
void register_stats_and_end(Actor *actor){
    golds = ((PlayerVars*)actor->vars)->golds;
    movements = ((PlayerVars*)actor->vars)->movements;
    gameEnded = true;
    if(is_actor_possessed(actor)) destroy_all_actors_with_entity_id(shadowID);
}

//Quando o player se mover, adiciona 1 aos movimentos.
void on_player_move(Actor *actor){
    ((PlayerVars*)actor->vars)->movements++;
    if(compare_coordinates(actor->position, to_coordinate(0, 0))){
        if(((PlayerVars*)actor->vars)->golds >= GOLD_COUNT){
            register_stats_and_end(actor);
        }
    }
}

//Quando o player receber algum evento de tecla.
void on_player_input(Actor *actor, SDL_Keycode key){
    switch(key){
    case SDLK_w:
        set_actor_sprite(actor, (TextureData){ "res/player_f.png", 1, 1 });
        move_actor(actor, to_coordinate(actor->position.x, actor->position.y - 1));
        break;
    case SDLK_a:
        set_actor_sprite(actor, (TextureData){ "res/player_l.png", 1, 1 });
        move_actor(actor, to_coordinate(actor->position.x - 1, actor->position.y));
        break;
    case SDLK_s:
        set_actor_sprite(actor, (TextureData){ "res/player_b.png", 1, 1 });
        move_actor(actor, to_coordinate(actor->position.x, actor->position.y + 1));
        break;
    case SDLK_d:
        set_actor_sprite(actor, (TextureData){ "res/player_r.png", 1, 1 });
        move_actor(actor, to_coordinate(actor->position.x + 1, actor->position.y));
        break;
    }
}

//Quando o player colidir com a sombra, remove-a.
void on_player_collide(Actor *actor, Actor *collidingActor){
    switch(collidingActor->entity.id){
    case shadowID:
        destroy_actor(collidingActor);
        break;
    case goldID:
        if(!((GoldVars*)collidingActor->vars)->taken){
            ((PlayerVars*)actor->vars)->golds++;
            ((GoldVars*)collidingActor->vars)->taken = true;
        }
        break;
    }
}

//Quando o player for destruído.
void on_player_destroy(Actor *actor){
    register_stats_and_end(actor);
}

//Inicializa as variáveis padrão do player.
PlayerVars *default_player_vars(){
    PlayerVars *vars = (PlayerVars*)malloc(sizeof(PlayerVars));
    vars->arrows = 1;
    vars->golds = 0;
    vars->movements = 0;
    return vars;
}
