//Estrutura de uma coordenada (usada na engine gr�fica).
typedef struct coord{
    int x, y;
} Coord;

//Estrutura de uma transforma��o.
typedef struct transform{
    Coord position;
    float rotation;
    float scale;
    bool orientation;
} Transform;
