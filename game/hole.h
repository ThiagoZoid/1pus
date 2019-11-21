//Entidade do Buraco.
#define holeEntity (Entity){ holeID, false, false, holeSprite, on_hole_spawn, NULL, NULL, on_hole_collide, NULL }

//Quando o buraco spawna, cria indicadores de brisa ao redor.
void on_hole_spawn(Actor *actor){
    List breezePositions = adjacent_coordinates_cross(actor->position);

    int i;
    for(i = 0; i < breezePositions.listSize; i++){
        spawn_actor(breezeEntity, *(Coordinate*)get_item_at(breezePositions, i), NULL);
    }
}

//Quando o Player colidir com o buraco, ele morre.
void on_hole_collide(Actor *actor, Actor *collidingActor){
    if(collidingActor->entity.id == playerID){
        destroy_actor(collidingActor);
    }
}
