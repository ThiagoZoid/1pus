#define wumpusEntity (Entity){ false, wumpusSprite, on_wumpus_spawn, NULL, NULL, NULL }  //Entidade do Wumpus.

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

WumpusVars *default_wumpus_vars(){
    return (WumpusVars*)malloc(sizeof(WumpusVars));
}
