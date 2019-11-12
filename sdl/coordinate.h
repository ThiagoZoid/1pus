//Estrutura de uma coordenada (usada na engine gráfica).
typedef struct coord{
    int x, y;
} Coord;

//Estrutura de uma coordenada flutuante (usada na engine gráfica).
typedef struct fcoord{
    float x, y;
} FCoord;

//Estrutura de uma transformação.
typedef struct transform{
    Coord position;
    float rotation;
    float scale;
    bool orientation;
} Transform;

//Converte uma coordenada inteira em flutuante.
FCoord CoordToFCoord(Coord c){
    FCoord a;
    a.x = (float)c.x;
    a.y = (float)c.y;
    return a;
}

//Converte uma coordenada flutuante em inteira.
Coord FCoordToCoord(FCoord c){
    Coord a;
    a.x = (int)c.x;
    a.y = (int)c.y;
    return a;
}
