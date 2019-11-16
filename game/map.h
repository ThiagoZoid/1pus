//Mapa.
Tile gameMap[MAP_SIZE][MAP_SIZE];

//Gera o mapa a partir da fun��o recebida como par�metro.
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

//Obt�m um tile de acordo com uma coordenada.
Tile* get_tile(Coordinate position){
    return &gameMap[position.x][position.y];
}
