
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

//Obtém um item (referência) em um índice de uma lista.
void *get_item_at(List itemList, int index){

    return !is_list_empty(itemList) &&
    index < itemList.listSize ? *(itemList.values + index) : NULL;
}

//Checa se uma lista possúi uma item.
bool contains_item(List itemList, void *item, bool (*compare_function)(void*, void*)){
    int i;
    bool contains = false;
    for(i = 0; i < itemList.listSize; i++){
        if(!contains){
            void *currentItem = get_item_at(itemList, i);
            contains = compare_function(currentItem, item);
        } else break;
    }
    return contains;
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

    if(is_list_empty(*itemList) || index >= itemList->listSize) return false;
    int i, j;
    for(i = 0, j = 0; i < itemList->listSize; i++){
        if(i != j) *(itemList->values + j) = *(itemList->values + i);
        if(i != index) j++;
    }
    itemList->listSize--;
    free(itemList + j);
    return true;
}
