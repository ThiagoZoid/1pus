#define MAX_TILE_ATTRIBUTES 10

//Estrutura do tipo do tile.
typedef struct tileType{
    TextureData textureData;
} TileType;

//Estrutura de um tile.
typedef struct tile{
    TileType *type;
    void *attributes[MAX_TILE_ATTRIBUTES];
} Tile;

//Define um tipo de um tile.
bool tile_set_type(Tile *tile, TileType *type){
    if(!tile || !type) return false;
    tile->type = type;
    return true;
}

//Adiciona um atributo a um tile.
bool tile_add_attribute(Tile *tile, void *attribute){
    int i;
    bool foundSpace = false;

    if(tile && attribute){
        for(i = 0; i < MAX_TILE_ATTRIBUTES; i++){
            if(!tile->attributes[i]){
                foundSpace = true;
                break;
            }
        }

        if(foundSpace) tile->attributes[i] = attribute;
    }

    return foundSpace;
}
