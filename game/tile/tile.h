#define MAX_TILE_ATTRIBUTES 10

//Estrutura do tipo do tile.
//No jogo do Wumpus, é usado para definir
//características como "buraco".
typedef struct tileType{
    char texture[32];
} TileType;

//Atributo de um Tile.
//No jogo do Wumpus, é usado para definir
//características como o fedor ou a brisa.
typedef struct tileAttribute{
    int id;
} TileAttribute;


//Estrutura de um tile.
typedef struct tile{
    TileType *type;
    TileAttribute* attributes[MAX_TILE_ATTRIBUTES];
} Tile;

//Define um tipo de um tile.
bool tile_set_type(Tile *tile, TileType *type){
    if(!tile || !type) return false;
    tile->type = type;
    return true;
}

//Adiciona um atributo a um tile.
bool tile_add_attribute(Tile *tile, TileAttribute *attribute){
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
