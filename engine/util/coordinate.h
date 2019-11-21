//Estrutura de uma coordenada.
typedef struct coordinate {
    int x, y;
} Coordinate;

//Compara duas coordenadas.
bool compare_coordinates(Coordinate first, Coordinate second){
    return first.x == second.x && first.y == second.y;
}

//Compara dois ponteiros de coordenadas.
//Usada apenas para encontrar coordenadas em listas (que trabalham apenas com ponteiros).
static bool compare_coordinate_pointers(Coordinate *first, Coordinate *second){
    return first->x == second->x && first->y == second->y;
}

//Função da Lista customizada para coordenadas (para evitar tratativas de ponteiro).
int index_of_coordinate(List itemList, Coordinate coordinate){
    return index_of(itemList, &coordinate, compare_coordinate_pointers);
}

//Cria uma coordenada.
Coordinate to_coordinate(int x, int y){
    return (Coordinate){ x, y };
}

//Aloca uma coordenada na memória e a inicializa.
Coordinate *allocate_coordinate(Coordinate coordinate){
    Coordinate *newCoordinate = (Coordinate*)malloc(sizeof(Coordinate));
    *newCoordinate = coordinate;
    return newCoordinate;
}

//Retorna verdadeiro se as coordenadas forem adjacentes (lados e diagonal).
bool adjacent_coordinate(Coordinate first, Coordinate second){
    return (absolute(first.x - second.x) == 1 && absolute(first.y - second.y) <= 1)
    || (absolute(first.y - second.y) == 1 && absolute(first.x - second.x) <= 0);
}

//Retorna verdadeiro se as coordenadas forem adjacentes diagonalmente (formando um X).
bool adjacent_coordinate_x(Coordinate first, Coordinate second){
    return absolute(first.x - second.x) == 1 && absolute(first.y - second.y) == 1;
}

//Retorna verdadeiro se as coordenadas forem adjacentes paralelamente (formando um +).
bool adjacent_coordinate_cross(Coordinate first, Coordinate second){
    return (absolute(first.x - second.x) == 1 && first.y - second.y == 0)
    || (absolute(first.y - second.y) == 1 && first.x - second.x == 0);
}

//Retorna uma lista de coordenadas adjacentes paralelamente (formando um +).
List adjacent_coordinates_cross(Coordinate coordinate){
    List coordinateList = empty_list();

    add_item(&coordinateList, allocate_coordinate(to_coordinate(coordinate.x - 1, coordinate.y)));
    add_item(&coordinateList, allocate_coordinate(to_coordinate(coordinate.x + 1, coordinate.y)));
    add_item(&coordinateList, allocate_coordinate(to_coordinate(coordinate.x, coordinate.y - 1)));
    add_item(&coordinateList, allocate_coordinate(to_coordinate(coordinate.x, coordinate.y + 1)));

    return coordinateList;
}

//Retorna uma lista de coordenadas adjacentes paralelamente (formando um X).
List adjacent_coordinates_x(Coordinate coordinate){
    List coordinateList = empty_list();

    add_item(&coordinateList, allocate_coordinate(to_coordinate(coordinate.x - 1, coordinate.y - 1)));
    add_item(&coordinateList, allocate_coordinate(to_coordinate(coordinate.x + 1, coordinate.y + 1)));
    add_item(&coordinateList, allocate_coordinate(to_coordinate(coordinate.x + 1, coordinate.y - 1)));
    add_item(&coordinateList, allocate_coordinate(to_coordinate(coordinate.x - 1, coordinate.y + 1)));

    return coordinateList;
}

//Exibe uma coordenada.
void print_coordinate(Coordinate coordinate){
    printf("X: %i, Y: %i\n", coordinate.x, coordinate.y);
}

//Exibe uma lista de coordenadas.
void print_coordinates(List coordinateList){
    int i;
    for(i = 0; i < coordinateList.listSize; i++){
        print_coordinate(*(Coordinate*)get_item_at(coordinateList, i));
    }
}

//Cria uma lista de coordenadas a partir de 1 coordenada.
List to_list(Coordinate coordinate){
    List newList = empty_list();
    add_item(&newList, &coordinate);
    return newList;
}

//Obtém uma coordenada aleatória no mapa.
Coordinate random_coordinate(){
    return to_coordinate(rand() % MAP_SIZE, rand() % MAP_SIZE);
}

//Cria uma lista de coordenadas aleatórias.
List random_coordinates(int number){
    List newList = empty_list();
    int i;
    for(i = 0; i < number; i++){
        Coordinate *r = allocate_coordinate(random_coordinate());
        add_item(&newList, r);
    }
    return newList;
}

//Cria uma coordenada aleatória recebendo uma lista de exclusão.
Coordinate random_exclusive_coordinate(List exclusionList){
    Coordinate result;
    bool uniqueCoordinate;
    do{
        uniqueCoordinate = true;
        result = random_coordinate();
        int i;
        for(i = 0; i < exclusionList.listSize; i++){
            if(uniqueCoordinate){
                uniqueCoordinate = !compare_coordinates(result, *((Coordinate*)get_item_at(exclusionList, i)));
            } else break;
        }
    }while(uniqueCoordinate == false);
    return result;
}

//Cria uma lista de coordenadas aleatórias, recebendo uma lista de exclusão.
List random_exclusive_coordinates(List exclusionList, int number){
    List newList = empty_list();
    int i;
    for(i = 0; i < number; i++){
        Coordinate *r = allocate_coordinate(random_exclusive_coordinate(exclusionList));
        add_item(&newList, r);
    }
    return newList;
}

//Cria uma lista de coordenadas aleatórias, sem repetição, recebendo uma lista de exclusão.
List random_unique_coordinates(List exclusionList, int number){
    List auxList = exclusionList;
    List newList = empty_list();
    int i;
    for(i = 0; i < number; i++){
        Coordinate *r = allocate_coordinate(random_exclusive_coordinate(auxList));
        add_item(&newList, r);
        add_item(&auxList, r);
    }
    return newList;
}
