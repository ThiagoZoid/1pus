#define TILE_SCALE 10

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
void render_map(Coordinate tileSize){
    //Posição inicial dos tiles.
    Coord base = {(SCREEN_WIDTH / 2) - (MAP_SIZE / 2) * tileSize.x,
                    (SCREEN_HEIGHT / 2) - (MAP_SIZE / 2) * tileSize.y};
    int i, j;
    // Y
    for(i = 0; i < MAP_SIZE; i++){
        // X
        for(j = 0; j < MAP_SIZE; j++){
            Tile *currentTile = get_tile(to_coordinate(j, i));
            //Verifica se a textura do tile já foi carregada.
            Texture currentTexture = empty_texture();
            currentTexture.data.path = currentTile->type->textureData.path;
            int index = index_of(textureCache, &currentTexture, compare_textures);

            //Caso não exista, carrega a textura do arquivo.
            if(index < 0){
                Texture *newTexture = malloc(sizeof(Texture));
                *newTexture = load_texture(currentTile->type->textureData);
                add_item(&textureCache, newTexture);
                index = get_last_index(textureCache);
            }

            //Cálculo da posição do tile.
            Coord tilePosition = {base.x + j * tileSize.x, base.y + i * tileSize.y};
            Transform tileTransform = {tilePosition, 0, TILE_SCALE, false};

            printf("%i", get_last_index(textureCache));

            //Renderiza a textura.
            render_texture(get_item_at(textureCache, index), tileTransform, PIVOT_TOP_RIGHT, 1.0);
        }
    }

}
