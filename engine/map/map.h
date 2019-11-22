//Tamanho de um tile na tela.
#define TILE_SCALE 4

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

//Obtém um tile de acordo com uma coordenada.
Tile* get_tile(Coordinate position){
    return &gameMap[position.x][position.y];
}

//Renderiza o mapa.
void render_map(){
    //Posição inicial dos tiles.
    Coord base = {(SCREEN_WIDTH / 2) - (GRID_SIZE * TILE_SCALE) * (MAP_SIZE / 2.0),
                    (SCREEN_HEIGHT / 2) - (GRID_SIZE * TILE_SCALE) * (MAP_SIZE / 2.0)};
    int i, j;
    // Y
    for(i = 0; i < MAP_SIZE; i++){
        // X
        for(j = 0; j < MAP_SIZE; j++){
            Tile *currentTile = get_tile(to_coordinate(j, i));
            int index = get_texture(currentTile->spriteData);

            //Cálculo da posição do tile.
            Coord tilePosition = {base.x + j * GRID_SIZE * TILE_SCALE, base.y + i * GRID_SIZE * TILE_SCALE};
            Transform tileTransform = {tilePosition, 0, TILE_SCALE, false};

            //Renderiza a textura.
            render_texture(((CacheTexture*)get_item_at(textureCache, index))->texture, tileTransform, PIVOT_TOP_LEFT, 1.0);
        }
    }
}
