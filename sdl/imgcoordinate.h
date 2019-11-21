//Estrutura de uma coordenada (usada na engine gráfica).
typedef struct coord{
    int x, y;
} Coord;

//Estrutura de uma transformação.
typedef struct transform{
    Coord position;
    float rotation;
    float scale;
    bool orientation;
} Transform;
