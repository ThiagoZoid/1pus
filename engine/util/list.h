//Estrutura de uma lista.
typedef struct itemList {
    void **values;
    int listSize;
} List;

//Cria uma lista e a inicializa como vazia.
List empty_list(){
    List newList;
    newList.values = NULL;
    newList.listSize = 0;
    return newList;
}

//Checa se uma lista está vazia.
bool is_list_empty(List itemList){
    return itemList.listSize <= 0;
}

//Obtém um item em um índice de uma lista.
void *get_item_at(List itemList, int index){

    return !is_list_empty(itemList) &&
            index < itemList.listSize ? *(itemList.values + index) : NULL;
}

//Obtém um item em um índice de uma lista.
bool set_index(List *itemList, void *item, int index){
    if(!itemList || !item || index < 0 || index >= itemList->listSize) return false;

    *(itemList->values + index) = item;
    return true;
}

//Obtém o último índice de uma lista.
int get_last_index(List itemList){
    return itemList.listSize - 1;
}

//Checa se uma lista possúi uma item.
int index_of(List itemList, void *item, bool (*compare_function)()){
    int i;
    for(i = 0; i < itemList.listSize; i++){
        void *currentItem = get_item_at(itemList, i);
        if(compare_function(currentItem, item)) return i;
    }
    return -1;
}

//Adiciona um item a uma lista.
bool add_item(List *itemList, void *item){
    if(!itemList) return false;

    if(is_list_empty(*itemList)){
        itemList->listSize = 0;
        free(itemList->values);
    }
    void **newValues = (void**)malloc((itemList->listSize + 1) * sizeof(void*));
    int i;
    for(i = 0; i < itemList->listSize; i++){
        *(newValues + i) = *(itemList->values + i);
    }
    *(newValues + i) = item;
    itemList->listSize++;
    itemList->values = newValues;
    return true;
}

//Remove uma coordenada de um índice em uma lista.
bool remove_item_at(List *itemList, int index){
    if(!itemList) return false;

    if(is_list_empty(*itemList) || index >= itemList->listSize || index < 0) return false;
    int i, j;
    for(i = 0, j = 0; i < itemList->listSize; i++){
        if(i != j) *(itemList->values + j) = *(itemList->values + i);
        if(i != index) j++;
    }
    itemList->listSize--;
    free(itemList + j);
    return true;
}

//Junta uma segunda lista a uma primeira.
bool append_lists(List *firstList, List secondList){
    if(is_list_empty(secondList)) return true;

    if(is_list_empty(*firstList)){
        firstList->listSize = 0;
        free(firstList->values);
    }
    int finalSize = firstList->listSize + secondList.listSize;
    void **newValues = (void**)malloc((finalSize) * sizeof(void*));

    int i;
    for(i = 0; i < finalSize; i++){
        if(i < firstList->listSize){
            *(newValues + i) = *(firstList->values + i);
        } else {
            *(newValues + i) = *(secondList.values + (i - firstList->listSize));
        }
    }

    free(firstList->values);
    firstList->values = newValues;
    firstList->listSize = finalSize;
    return true;
}
