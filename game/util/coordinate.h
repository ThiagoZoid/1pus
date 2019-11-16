//Estrutura de uma coordenada.
typedef struct coordinate {
    int x, y;
} Coordinate;

//Compara duas coordenadas.
bool compare_coordinates(Coordinate first, Coordinate second){
    return first.x == second.x && first.y == second.y;
}

//Retorna verdadeiro se as coordenadas forem adjacentes (lados e diagonal);
bool adjacent_coordinate(Coordinate first, Coordinate second){
    return (absolute(first.x - second.x) == 1 && absolute(first.y - second.y) <= 1)
    || (absolute(first.y - second.y) == 1 && absolute(first.x - second.x) <= 0);
}

//Retorna verdadeiro se as coordenadas forem adjacentes diagonalmente (formando um X);
bool adjacent_coordinate_x(Coordinate first, Coordinate second){
    return absolute(first.x - second.x) == 1 && absolute(first.y - second.y) == 1;
}

//Retorna verdadeiro se as coordenadas forem adjacentes paralelamente (formando um +);
bool adjacent_coordinate_cross(Coordinate first, Coordinate second){
    return (absolute(first.x - second.x) == 1 && first.y - second.y == 0)
    || (absolute(first.y - second.y) == 1 && first.x - second.x == 0);
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

/*
//Junta a segunda lista de coordenadas na primeira.
bool append_lists(CoordinateList *firstList, CoordinateList secondList){
    if(!firstList) return false;
    if(is_coordinate_list_empty(secondList)) return true;

    Coordinate *newValues = malloc((firstList->listSize + secondList.listSize) * sizeof(Coordinate));
    int i, j;
    for(i = 0; i < firstList->listSize; i++){
        *(newValues + i) = *(firstList->values + i);
    }
    for(j = 0; j < secondList.listSize; j++){
        *(newValues + j + i) = *(secondList.values + j);
    }
    free(firstList->values);
    firstList->values = newValues;
    firstList->listSize = i + j;
    return true;
}
*/

//Cria uma coordenada.
Coordinate to_coordinate(int x, int y){
    return (Coordinate){ x, y };
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
        Coordinate r = random_coordinate();
        add_item(&newList, &r);
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
        Coordinate r = random_exclusive_coordinate(exclusionList);
        add_item(&newList, &r);
    }
    return newList;
}

//Cria uma lista de coordenadas aleatórias, sem repetição, recebendo uma lista de exclusão.
List random_unique_coordinates(List exclusionList, int number){
    List newList = exclusionList;
    int i;
    for(i = 0; i < number; i++){
        Coordinate r = random_exclusive_coordinate(newList);
        add_item(&newList, &r);
    }
    return newList;
}
