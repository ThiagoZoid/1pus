#define ACTOR_SCALE 5

typedef enum direction {
    FRONT,
    BACK,
    RIGHT,
    LEFT
} Direction;

typedef struct entity Entity;
typedef struct actor Actor;

//Estrutura de uma entidade.
typedef struct entity{
    int id;
    bool controllable;
    bool blockable;
    TextureData spriteData;
    void (*spawn_event)(Actor*);
    void (*destroy_event)(Actor*);
    void (*move_event)(Actor*);
    void (*collide_event)(Actor*, Actor*);
    void (*input_event)(Actor*, SDL_Keycode);
} Entity;

//Estrutura de um ator.
typedef struct actor{
    int id;
    Entity entity;
    Coordinate position;
    Texture *sprite;
    void *vars;
} Actor;

//Lista de atores.
List actors;

#include "controller.h"

//Inicializa a lista de atores.
void initialize_actors(){
    actors = empty_list();
}

//Compara dois atores.
bool compare_actors(Actor *first, Actor *second){
    return first->id == second->id;
}

//Spawna (criar) um ator no cen�rio.
Actor *spawn_actor(Entity entity, Coordinate position, void *vars){
    if(position.x < 0 || position.y < 0 || position.x >= MAP_SIZE || position.y >= MAP_SIZE) return NULL;

    Actor *actor = (Actor*)malloc(sizeof(Actor));
    Texture *sprite = ((CacheTexture*)get_item_at(textureCache, get_texture(entity.spriteData)))->texture;
    *actor = (Actor){ rand(), entity, position, sprite, vars };
    if(actor->entity.spawn_event){
        actor->entity.spawn_event(actor);
    }

    add_item(&actors, actor);
    return actor;
}

//Obt�m todos os atores em um tile.
List get_all_actors_at(Coordinate position){
    List actorsList = empty_list();
    int i;
    for(i = 0; i < actors.listSize; i++){
        Actor *currentActor = (Actor*)get_item_at(actors, i);
        if(compare_coordinates(position, currentActor->position)){
            add_item(&actorsList, currentActor);
        }
    }
    return actorsList;
}

//Destr�i um ator.
bool destroy_actor(Actor *actor){
    if(!actor) return false;

    remove_item_at(&actors, index_of(actors, actor, compare_actors));

    if(actor->entity.destroy_event){
        actor->entity.destroy_event(actor);
    }

    if(is_actor_possessed(actor)) unpossess();
    //free(actor);
    return true;
}

//Obt�m todos os atores em um tile.
void destroy_all_actors_with_entity_id(int id){
    int i;
    Actor *currentActor;
    for(i = 0; i < actors.listSize; i++){
        currentActor = (Actor*)get_item_at(actors, i);
        if(currentActor->entity.id == id){
            destroy_actor(currentActor);
            i--;
        }
    }
}

//Move um ator.
bool move_actor(Actor *actor, Coordinate position){
    if(!actor || position.x < 0 || position.y < 0 || position.x >= MAP_SIZE || position.y >= MAP_SIZE)
        return false;

    //Verifica se algum dos atores no tile alvo � bloque�vel.
    List collidingActors = get_all_actors_at(position);
    int i;
    bool canMove = true;
    for(i = 0; i < collidingActors.listSize; i++){
        if(((Actor*)get_item_at(collidingActors, i))->entity.blockable){
            canMove = false;
            break;
        }
    }

    if(canMove){
        //Ativa os eventos de colis�o.
        if(actor){
            for(i = 0; i < collidingActors.listSize; i++){
                Actor *currentActor = (Actor*)get_item_at(collidingActors, i);
                if(currentActor){
                    if(currentActor->entity.collide_event){
                        currentActor->entity.collide_event(currentActor, actor);
                    }
                    if(actor->entity.collide_event){
                        actor->entity.collide_event(actor, currentActor);
                    }
                };
            }
        }
        if(actor){
            //Ativa o evento de movimento do pr�prio ator.
            actor->position = position;
            if(actor->entity.move_event){
                actor->entity.move_event(actor);
            }
        }
    }
    return canMove;
}

//Obt�m um ator atrav�s de seu ID.
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

//Define a textura de um ator.
bool set_actor_sprite(Actor *actor, TextureData data){
    if(!actor) return false;

    actor->sprite = (Texture*)((CacheTexture*)get_item_at(textureCache, get_texture(data)))->texture;
    return true;
}

//Renderiza um ator.
bool render_actor(Actor *actor){
    if(!actor || !actor->sprite) return false;

    //Posi��o do tile (0, 0).
    Coord base = {(SCREEN_WIDTH / 2) - (GRID_SIZE * TILE_SCALE) * (MAP_SIZE / 2.0),
                    (SCREEN_HEIGHT / 2) - (GRID_SIZE * TILE_SCALE) * (MAP_SIZE / 2.0)};
    //C�lculo da posi��o do tile.
    Coord actorPosition = {base.x + actor->position.x * GRID_SIZE * TILE_SCALE + GRID_SIZE * TILE_SCALE / 2,
                            base.y + actor->position.y * GRID_SIZE * TILE_SCALE + GRID_SIZE * TILE_SCALE / 2};
    Transform actorTransform = {actorPosition, 0, ACTOR_SCALE, false};

    //Renderiza a textura.
    render_texture(actor->sprite, actorTransform, PIVOT_MID_CENTER, 1.0);

    return true;
}

//Renderiza os atores.
void render_actors(){
    int i;
    for(i = 0; i < actors.listSize; i++){
        Actor *currentActor = get_item_at(actors, i);
        render_actor(currentActor);
    }
}
