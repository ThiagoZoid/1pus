//Mapa.
Tile gameMap[MAP_SIZE][MAP_SIZE];

//Gera o mapa a partir da função recebida como parâmetro.
void generate_map(void (*tile_function)(Tile*, Coordinate)){
    int i, j;
    for(i = 0; i < MAP_SIZE; i++){
        for(j = 0; j < MAP_SIZE; j++){
            tile_function(&gameMap[i][j], to_coordinate(i, j));
        }
    }
}

//Renderiza o mapa.
void render_map(){
    int i, j;
    for(i = 0; i < MAP_SIZE; i++){
        for(j = 0; j < MAP_SIZE; j++){

        }
    }

}

//Obtém um tile de acordo com uma coordenada.
Tile* get_tile(Coordinate position){
    return &gameMap[position.x][position.y];
}
