#define HOLE_COUNT MAP_SIZE / 2
#define GOLD_COUNT 2

//Registro de IDs
#define goldID      0
#define stenchID    1
#define breezeID    2
#define playerID    3
#define holeID      4
#define wumpusID    5
#define shadowID    6

//Registro de texturas.
#define tileSprite      (TextureData){ "res/tile.png", 1, 1 }
#define tileHoleSprite  (TextureData){ "res/tile_hole.png", 1, 1 }
#define playerSprite    (TextureData){ "res/player_b.png", 1, 1 }
#define wumpusSprite    (TextureData){ "res/wumpus.png", 2, 1500 }
#define goldSprite      (TextureData){ "res/gold.png", 4, 400 }
#define holeSprite      (TextureData){ "res/hole.png", 1, 1 }
#define stenchSprite    (TextureData){ "res/stench.png", 2, 1000 }
#define breezeSprite    (TextureData){ "res/breeze.png", 2, 1000 }
#define shadowSprite    (TextureData){ "res/shadow.png", 1, 1 }

//Registro de entidades.
#define stenchEntity    (Entity){ stenchID, false, false, stenchSprite, NULL, NULL, NULL, NULL, NULL }
#define breezeEntity    (Entity){ breezeID, false, false, breezeSprite, NULL, NULL, NULL, NULL, NULL }
#define shadowEntity    (Entity){ shadowID, false, false, shadowSprite, NULL, NULL, NULL, NULL, NULL }

int golds = 0;      //Informações do player armazenadas quando o jogo
int movements = 0;  //acaba (para serem mostradas).

//Entidades mais significantes (com comportamentos e
//variáveis únicas) têm seu próprio header, para organização.
#include "gold.h"
#include "player.h"
#include "hole.h"
#include "wumpus.h"

List importantPositions;    //Lista onde as coordenadas importantes
                            //serão adicionadas para não haver repetição,
                            //por exemplo, o ouro nascer cima do Wumpus, etc.

//Gera cada tile do mapa.
void generate_tile(Tile *t, Coordinate position){
    t->spriteData = tileSprite;
}

//Calcula os atributos básicos do nível.
void calculate_level(){
    prepare_random_seed();

    initialize_cache(); //Inicializa o cache;
    initialize_actors(); //Inicializa atores;

    importantPositions = empty_list();  //Inicializa a lista de coordenadas importantes.

    Coordinate *playerPos = allocate_coordinate((to_coordinate(0, 0)));                                 //Coordenada inicial do Player.
    add_item(&importantPositions, playerPos);

    Coordinate *wumpusPos = allocate_coordinate(random_exclusive_coordinate(importantPositions));       //Coordenada do Wumpus.
    add_item(&importantPositions, wumpusPos);                                                           //Adicionada à lista

    List goldPositions = random_unique_coordinates(importantPositions, GOLD_COUNT);                     //Coordenadas do ouro.
    append_lists(&importantPositions, goldPositions);                                                   //Junção de listas.

    List holePositions = random_unique_coordinates(importantPositions, HOLE_COUNT);                     //Coordenadas do ouro.
    append_lists(&importantPositions, holePositions);                                                   //Junção de listas.

    Actor *player = spawn_actor(playerEntity, *playerPos, default_player_vars());                       //Spawna o Player.

    int i;
    for(i = 0; i < GOLD_COUNT; i++){
        spawn_actor(goldEntity, *((Coordinate*)get_item_at(goldPositions, i)), default_gold_vars());    //Spawna cada ouro.
    }

    for(i = 0; i < HOLE_COUNT; i++){
        spawn_actor(holeEntity, *((Coordinate*)get_item_at(holePositions, i)), NULL);                   //Spawna cada buraco.
    }

    spawn_actor(wumpusEntity, *wumpusPos, NULL);                                                        //Spawna o Wumpus.

    int j;
    for(i = 0; i < MAP_SIZE; i++){
        for(j = 0; j < MAP_SIZE; j++){
            if(compare_coordinates(to_coordinate(j, i), *playerPos)) continue;
            spawn_actor(shadowEntity, to_coordinate(j, i), NULL);                                       //Spawna cada sombra.
        }
    }

    possess(player);                                                                                    //Possúi o Player.

}

//Finaliza o jogo e mostra a pontuação.
void end_game(){
    char msg[64];
    sprintf(msg, "Movimentos: %i, Moedas: %i/%i", movements, golds, GOLD_COUNT);
    MsgBox(msg, "Fim de jogo!");
}

//Função que é executada ao iniciar o jogo.
void begin_game(){
    calculate_level();

    generate_map(&generate_tile);
}

