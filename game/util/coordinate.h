//Estrutura de uma coordenada.
typedef struct coordinate {
    int x, y;
} Coordinate;

//Estrutura de uma lista de coordenadas.
typedef struct coordinateList {
    Coordinate *values;
    int listSize;
} CoordinateList;

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
void print_coordinates(CoordinateList coordinateList){
    int i;
    for(i = 0; i < coordinateList.listSize; i++){
        print_coordinate(*(coordinateList.values + i));
    }
}

//Cria uma lista de coordenadas e a inicializa como vazia.
CoordinateList empty_list(){
    CoordinateList newList;
    newList.values = NULL;
    newList.listSize = 0;
    return newList;
}

//Checa se uma lista de coordenadas esta vazia.
bool is_list_empty(CoordinateList coordinateList){
    return coordinateList.listSize <= 0;
}

//Obtém uma coordenada em um índice de uma lista.
Coordinate* get_coordinate_at(CoordinateList *coordinateList, int index){
    if(!coordinateList) return false;

    return !is_list_empty(*coordinateList) ? (Coordinate*)(coordinateList->values + index) : NULL;
}

//Checa se uma lista possúi uma coordenada.
bool contains_coordinate(CoordinateList coordinateList, Coordinate coordinate){
    int i;
    bool contains = false;
    for(i = 0; i < coordinateList.listSize; i++){
        if(!contains){
            Coordinate currentCoordinate = *get_coordinate_at(&coordinateList, i);
            contains = compare_coordinates(currentCoordinate, coordinate);
        } else break;
    }
    return contains;
}

//Remove uma coordenada de um índice em uma lista.
bool remove_coordinate_at(CoordinateList *coordinateList, int index){
    if(!coordinateList) return false;

    if(is_list_empty(*coordinateList) || index >= coordinateList->listSize) return false;
    int i, j;
    for(i = 0, j = 0; i < coordinateList->listSize; i++){
        if(i != j) *(coordinateList->values + j) = *(coordinateList->values + i);
        if(i != index) j++;
    }
    coordinateList->listSize--;
    free(coordinateList + j);
    return true;
}

//Adiciona uma coordenada a uma lista.
bool add_coordinate(CoordinateList *coordinateList, Coordinate coordinate){
    if(!coordinateList) return false;

    if(is_list_empty(*coordinateList)){
        coordinateList->listSize = 0;
        free(coordinateList->values);
    }
    Coordinate *newValues = (Coordinate*)malloc((coordinateList->listSize + 1) * sizeof(Coordinate));
    int i;
    for(i = 0; i < coordinateList->listSize; i++){
        *(newValues + i) = *(coordinateList->values + i);
    }
    *(newValues + i) = coordinate;
    coordinateList->listSize++;
    coordinateList->values = newValues;
    return true;
}

//Junta a segunda lista de coordenadas na primeira.
bool append_lists(CoordinateList *firstList, CoordinateList secondList){
    if(!firstList) return false;
    if(is_list_empty(secondList)) return true;

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

//Cria uma coordenada.
Coordinate to_coordinate(int x, int y){
    return (Coordinate){ x, y };
}

//Cria uma lista de coordenadas a partir de 1 coordenada.
CoordinateList to_list(Coordinate coordinate){
    CoordinateList newList = empty_list();
    add_coordinate(&newList, coordinate);
    return newList;
}

//Obtém uma coordenada aleatória no mapa.
Coordinate random_coordinate(){
    return to_coordinate(rand() % MAP_SIZE, rand() % MAP_SIZE);
}

//Cria uma lista de coordenadas aleatórias.
CoordinateList random_coordinates(int number){
    CoordinateList newList = empty_list();
    int i;
    for(i = 0; i < number; i++){
        add_coordinate(&newList, random_coordinate());
    }
    return newList;
}

//Cria uma coordenada aleatória recebendo uma lista de exclusão.
Coordinate random_exclusive_coordinate(CoordinateList exclusionList){
    Coordinate result;
    bool uniqueCoordinate;
    do{
        uniqueCoordinate = true;
        result = random_coordinate();
        int i;
        for(i = 0; i < exclusionList.listSize; i++){
            if(uniqueCoordinate){
                uniqueCoordinate = !compare_coordinates(result, *get_coordinate_at(&exclusionList, i));
            } else break;
        }
    }while(uniqueCoordinate == false);
    return result;
}

//Cria uma lista de coordenadas aleatórias, recebendo uma lista de exclusão.
CoordinateList random_exclusive_coordinates(CoordinateList exclusionList, int number){
    CoordinateList newList = empty_list();
    int i;
    for(i = 0; i < number; i++){
        add_coordinate(&newList, random_exclusive_coordinate(exclusionList));
    }
    return newList;
}

//Cria uma lista de coordenadas aleatórias, sem repetição, recebendo uma lista de exclusão.
CoordinateList random_unique_coordinates(CoordinateList exclusionList, int number){
    CoordinateList newList = exclusionList;
    int i;
    for(i = 0; i < number; i++){
        add_coordinate(&newList, random_exclusive_coordinate(newList));
    }
    return newList;
}
