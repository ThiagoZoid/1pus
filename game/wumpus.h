//Entidade do Wumpus.
#define wumpusEntity (Entity){ wumpusID, false, false, wumpusSprite, on_wumpus_spawn, NULL, NULL, on_wumpus_collide, NULL }

typedef struct wumpusVars{
    bool alive;
} WumpusVars;

void on_wumpus_spawn(Actor *actor){
    List stenchPositions = adjacent_coordinates_cross(actor->position);

    int i;
    for(i = 0; i < stenchPositions.listSize; i++){
        spawn_actor(stenchEntity, *(Coordinate*)get_item_at(stenchPositions, i), NULL);
    }
}

//Quando o Player colidir com o buraco, ele morre.
void on_wumpus_collide(Actor *actor, Actor *collidingActor){
    if(collidingActor->entity.id == playerID){
        destroy_actor(collidingActor);
    }
}

WumpusVars *default_wumpus_vars(){
    return (WumpusVars*)malloc(sizeof(WumpusVars));
}
