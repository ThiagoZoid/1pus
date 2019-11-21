#define HOLE_COUNT MAP_SIZE / 2
#define GOLD_COUNT 2

//Registro de texturas.
#define tileSprite      (TextureData){ "res/tile.png", 1, 1 }
#define tileHoleSprite  (TextureData){ "res/tile_hole.png", 1, 1 }
#define playerSprite    (TextureData){ "res/player_b.png", 1, 1 }
#define wumpusSprite    (TextureData){ "res/wumpus.png", 2, 1500 }
#define goldSprite      (TextureData){ "res/gold.png", 4, 400 }
#define holeSprite      (TextureData){ "res/hole.png", 1, 1 }
#define stenchSprite    (TextureData){ "res/stench.png", 2, 1000 }
#define breezeSprite    (TextureData){ "res/breeze.png", 2, 1000 }

//Registro de entidades.

#define goldEntity      (Entity){ false, goldSprite, NULL, NULL, NULL, NULL }               //Propriedades do Ouro.
#define stenchEntity    (Entity){ false, stenchSprite, NULL, NULL, NULL, NULL }             //Propriedades do Indicador de fedor.
#define breezeEntity    (Entity){ false, breezeSprite, NULL, NULL, NULL, NULL }             //Propriedades do Indicador de brisa.

#include "player.h"
#include "hole.h"
#include "wumpus.h"


//Registro de atores (inicializados em tempo de execução).

Actor *player;      //Referência ao Jogador.

List importantPositions;    //Lista onde as coordenadas importantes
                            //serão adicionadas para não haver repetição,
                            //por exemplo, o ouro nascer cima do Wumpus, etc.


//Gera cada tile do mapa.
void generate_tile(Tile *t, Coordinate position){

    /*
    //Checa se não há nada importante no tile (Wumpus, player, etc...)
    if(index_of_coordinate(importantPositions, position) < 0){

    }
    */

    t->spriteData = tileSprite;
}

//Calcula os atributos básicos do nível.
void calculate_level(){
    prepare_random_seed();

    initialize_cache(); //Inicializa o cache;
    initialize_actors(); //Inicializa atores;

    importantPositions = empty_list();  //Inicializa a lista de coordenadas importantes.

    Coordinate *playerPos = allocate_coordinate((to_coordinate(0, 0))); //Coordenada inicial do Player.
    add_item(&importantPositions, playerPos);

    Coordinate *wumpusPos = allocate_coordinate(random_exclusive_coordinate(importantPositions));   //Coordenada do Wumpus.
    add_item(&importantPositions, wumpusPos);                                                       //Adicionada à lista

    List goldPos = random_unique_coordinates(importantPositions, GOLD_COUNT);   //Coordenadas do ouro.
    append_lists(&importantPositions, goldPos);                                 //Junção de listas.

    List holePos = random_unique_coordinates(importantPositions, HOLE_COUNT);   //Coordenadas do ouro.
    append_lists(&importantPositions, holePos);                                 //Junção de listas.

    player = spawn_actor(playerEntity, *playerPos, default_player_vars());      //Spawna o Player.

    int i;
    for(i = 0; i < GOLD_COUNT; i++){
        spawn_actor(goldEntity, *((Coordinate*)get_item_at(goldPos, i)), NULL); //Spawna cada ouro.
    }
    for(i = 0; i < HOLE_COUNT; i++){
        spawn_actor(holeEntity, *((Coordinate*)get_item_at(holePos, i)), NULL); //Spawna cada buraco.
    }
    spawn_actor(wumpusEntity, *wumpusPos, NULL);                                //Spawna o Wumpus.

    possess(player);                                                            //Possúi o Player.

}

//Função que é executada ao iniciar o jogo.
void begin_game(){
    calculate_level();

    generate_map(&generate_tile);
}

