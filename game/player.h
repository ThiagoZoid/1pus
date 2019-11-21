#define playerEntity (Entity){ true, playerSprite, NULL, NULL, NULL, on_player_input }   //Entidade do Player.

typedef struct playerVars{
    bool alive;
    int arrows;
} PlayerVars;

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

PlayerVars *default_player_vars(){
    return (PlayerVars*)malloc(sizeof(PlayerVars));
}
