#define holeEntity (Entity){ false, holeSprite, on_hole_spawn, NULL, NULL, NULL }  //Entidade do Buraco.

void on_hole_spawn(Actor *actor){
    List breezePositions = adjacent_coordinates_cross(actor->position);

    int i;
    for(i = 0; i < breezePositions.listSize; i++){
        spawn_actor(breezeEntity, *(Coordinate*)get_item_at(breezePositions, i), NULL);
    }
}
