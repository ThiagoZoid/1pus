#define MAX_ACTORS 10

typedef struct entity Entity;
typedef struct actor Actor;

typedef struct entity{
    bool controllable;
    void (*spawn_event)(Actor *actor);
    void (*move_event)(Actor *actor);
} Entity;


typedef struct actor{
    Entity entity;
    Coordinate position;
} Actor;


Actor *actors[MAX_ACTORS];

Actor *spawn_actor(Entity entity, Coordinate position){
    Actor *actor = (Actor*)malloc(sizeof(Actor));
    *actor = (Actor){ entity, position };
    if(actor->entity.spawn_event){
        actor->entity.spawn_event(actor);
    }

    for(int i = 0; i < MAX_ACTORS; i++){
        if(!actors[i]){
            actors[i] = actor;
            break;
        }
    }

    return actor;
}

void move_actor(Actor *actor, Coordinate position){
    if(!actor) return;
    actor->position = position;
    if(actor->entity.move_event){
        actor->entity.move_event(actor);
    }
}
