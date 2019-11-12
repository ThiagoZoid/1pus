#define HOLE_COUNT 2
#define GOLD_COUNT 2

//Registro de tipos de tile.
TileType TILE_DEFAULT = { 0 };  //Tile padrão.
TileType TILE_HOLE = { 0 };     //Tile com buraco.

//Registro de atributos.
TileAttribute TILE_ATTR_BREEZY = { 0 }; //Brisa.
TileAttribute TILE_ATTR_STINKY = { 0 }; //Fedor do Wumpus.

//Registro de entidades.
Entity playerEntity = {true, NULL, NULL};   //Propriedades do Player.
Entity wumpusEntity = {false, NULL, NULL};  //Propriedades do Wumpus.
Entity goldEntity = {false, NULL, NULL};    //Propriedades do Ouro.

//Coordinate wumpusCoordinate;
//Coordinate goldCoordinate;
//Coordinate *holeCoordinates;

//Registro de atores (inicializados em runtime).
Actor* wumpus;              //Wumpus
Actor* golds[GOLD_COUNT];   //Ouro (No jogo original há apenas 1 ouro,
                            //mas para demonstração, esta versão conta
                            //com 2 barras de ouro.
Actor* player;              //Jogador.

CoordinateList importantPositions;  //Lista onde as coordenadas importantes
                                    //serão adicionadas para não haver repetição,
                                    //por exemplo, o ouro nascer cima do Wumpus, etc.


//Gera cada tile do mapa.
void generate_tile(Tile *t, Coordinate position){

    //Checa se não há nada importante no tile (Wumpus, player, etc...)
    if(!contains_coordinate(importantPositions, position)){
        if(adjacent_coordinate_cross(position, wumpus->position)){

        }
    }
    tile_set_type(t, &TILE_HOLE);
    tile_add_attribute(t, &TILE_ATTR_BREEZY);
}

//Calcula os atributos básicos do nível.
void calculate_level(){
    prepare_random_seed();

    importantPositions = empty_list();  //Inicializa a lista de coordenadas importantes.

    Coordinate playerPos = to_coordinate(0, 0);      //Coordenada inicial do Player.
    add_coordinate(&importantPositions, playerPos);  //Adicionada à lista de repetição.

    Coordinate wumpusPos = random_exclusive_coordinate(importantPositions); //Coordenada do Wumpus.
    add_coordinate(&importantPositions, wumpusPos);                         //Adicionada à lista.

    CoordinateList goldPos = random_unique_coordinates(importantPositions, GOLD_COUNT); //Coordenadas do ouro.
    append_lists(&importantPositions, goldPos);                                         //Junção de listas.

    player = spawn_actor(playerEntity, playerPos);  //Spawna o Player.
    wumpus = spawn_actor(wumpusEntity, wumpusPos);  //Spawna o Wumpus.

    int i;
    for(i = 0; i < GOLD_COUNT; i++){
        golds[i] = spawn_actor(goldEntity, *get_coordinate_at(&goldPos, i)); //Spawna cada ouro.
    }
}

//Renderiza o mapa.
void render_map_test(){
    int i, j;
    for(i = 0; i < MAP_SIZE; i++){
        for(j = 0; j < MAP_SIZE; j++){
            char a;
            if(contains_coordinate(importantPositions, to_coordinate(i, j))){
                if(compare_coordinates(player->position, to_coordinate(i, j))){
                    a = 'P';
                } else if(compare_coordinates(wumpus->position, to_coordinate(i, j))){
                    a = 'W';
                } else {
                    a = 'G';
                }
            } else {
                a = 'O';
            }
            printf("%c ", a);
        }
        printf("\n");
    }

}

//Função que é executada ao iniciar o jogo.
void begin_game(){
    calculate_level();
    generate_map(&generate_tile);
    render_map_test();
}
