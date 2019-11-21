//Entidade do Player.
#define playerEntity (Entity){ playerID, true, true, playerSprite, NULL, on_player_destroy, on_player_move, on_player_collide, on_player_input }

typedef struct playerVars{
    int movements;
    int arrows;
} PlayerVars;

//Quando o player se mover, adiciona 1 aos movimentos.
void on_player_move(Actor *actor){
    ((PlayerVars*)actor->vars)->movements++;
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

//Quando o player colidir com a sombra, removê-la.
void on_player_collide(Actor *actor, Actor *collidingActor){
    if(collidingActor->entity.id == shadowID){
        destroy_actor(collidingActor);
    }
}

//Quando o player for destruído.
void on_player_destroy(Actor *actor){
    if(is_actor_possessed(actor)) destroy_all_actors_with_entity_id(shadowID);
}

//Inicializa as variáveis padrão do player.
PlayerVars *default_player_vars(){
    return (PlayerVars*)malloc(sizeof(PlayerVars));
}
