#define MAX_ACTORS 10

typedef struct entity Entity;
typedef struct actor Actor;

//Estrutura de uma entidade.
typedef struct entity{
    bool controllable;
    void (*spawn_event)(Actor *actor);
    void (*destroy_event)(Actor *actor);
    void (*move_event)(Actor *actor);
} Entity;

//Estrutura de um ator.
typedef struct actor{
    int id;
    Entity entity;
    Coordinate position;
} Actor;

//Lista de atores.
List actors;

//Inicializa a lista de atores.
void initialize_actors(){
    actors = empty_list();
}

//Spawna (criar) um ator no cenário.
Actor *spawn_actor(Entity entity, Coordinate position){
    Actor *actor = (Actor*)malloc(sizeof(Actor));
    *actor = (Actor){ rand(), entity, position };
    if(actor->entity.spawn_event){
        actor->entity.spawn_event(actor);
    }

    add_item(&actors, actor);
    return actor;
}

//Move um ator.
void move_actor(Actor *actor, Coordinate position){
    if(!actor) return;

    actor->position = position;
    if(actor->entity.move_event){
        actor->entity.move_event(actor);
    }
}

//Compara dois atores.
bool compare_actors(Actor *firstActor, Actor *secondActor){
    return firstActor->id == secondActor->id;
}

//Destrói um ator.
void destroy_actor(Actor *actor){
    if(!actor) return;

    remove_item_at(&actors, (index_of(actors, actor, compare_actors)));

    if(actor->entity.destroy_event){
        actor->entity.destroy_event(actor);
    }

    free(actor);
}

//Obtém um ator através de seu ID.
Actor *get_actor_by_id(int id){
    if(id < 0) return NULL;

    bool found = false;
    int i;
    Actor* actor;
    for(i = 0; i < actors.listSize; i++){
        if(!found) {
            actor = get_item_at(actors, i);
            found = actor->id == id;
        } else break;
    }
    return found ? actor : NULL;
}
