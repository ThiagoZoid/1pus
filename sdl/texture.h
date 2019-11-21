//Lista de cache de texturas do jogo.
//Todas as texturas carregadas vêm pra cá.
List textureCache;

//Posições para o pivô.
typedef enum pivot{
    PIVOT_TOP_LEFT,
    PIVOT_TOP_CENTER,
    PIVOT_TOP_RIGHT,
    PIVOT_MID_LEFT,
    PIVOT_MID_CENTER,
    PIVOT_MID_RIGHT,
    PIVOT_BOT_LEFT,
    PIVOT_BOT_CENTER,
    PIVOT_BOT_RIGHT
} Pivot;

//Estrutura dos dados de uma textura.
typedef struct textureData{
    char            *path;
    int             frames;
    int             delay;
} TextureData;

//Estrutura de uma textura.
typedef struct texture{
    SDL_Texture     *image;
    TextureData     data;
    int             width;
    int             height;
} Texture;

typedef struct cacheTexture{
    Texture     *texture;
    int         step;
} CacheTexture;

//Limpa uma textura.
void clear_texture(Texture *texture){
    if(texture && texture->image){
        SDL_DestroyTexture(texture->image);
        free(texture);
    }
}

//Compara duas texturas.
bool compare_textures(Texture *first, Texture *second){
    return strcmp(first->data.path, second->data.path) == 0;
}

//Compara uma textura de cache e uma informação de textura.
bool compare_textures_cache(CacheTexture *texture, TextureData *data){
    return strcmp(texture->texture->data.path, data->path) == 0;
}

//Cria dados de textura em branco.
TextureData empty_texture_data(){
    TextureData d;
    d.frames = 1;
    d.path = NULL;
    d.delay = 500;
    return d;
}

//Cria uma textura em branco.
Texture empty_texture(){
    Texture t;
    t.image = NULL;
    t.data = empty_texture_data();
    t.width = 0;
    t.height = 0;
    return t;
}

//Carrega uma imagem do arquivo e põe em uma textura animada.
Texture load_texture(TextureData data){
    Texture texture = empty_texture();
    texture.data = data;

    //Imagem final.
	SDL_Texture* newImage = NULL;
    //Carrega a imagem para uma superfície.
    SDL_Surface* loadedSurface = IMG_Load(data.path);
    if(loadedSurface == NULL){
		printf("%s", SDL_GetError());
	}else{
        newImage = SDL_CreateTextureFromSurface(*rendererRef, loadedSurface);
        if(newImage == NULL){
            printf("%s", SDL_GetError());
        }else{
            texture.height = loadedSurface->h;
            texture.width = loadedSurface->w;
        }
        SDL_FreeSurface(loadedSurface);
	}
	texture.image = newImage;
	return texture.image ? texture : empty_texture();
}

//Obtém uma textura do cache ou a carrega caso não exista.
int get_texture(TextureData data){
    //Verifica se a textura já foi carregada.
    int index = index_of(textureCache, &data, compare_textures_cache);

    //Caso não exista, carrega a textura do arquivo.
    if(index < 0){
        CacheTexture *newTexture = malloc(sizeof(CacheTexture));
        newTexture->texture = malloc(sizeof(Texture));
        *newTexture->texture = load_texture(data);
        newTexture->step = 0;

        add_item(&textureCache, newTexture);
        index = get_last_index(textureCache);
    }
    return index;
}

//Renderiza uma textura.
void render_texture(Texture* texture, Transform transf, Pivot pos, float fraction){
    int finalWidth = texture->width * transf.scale / texture->data.frames;
    int finalHeight = texture->height * transf.scale;

    switch(pos){
        case PIVOT_TOP_LEFT: default:
            break;
        case PIVOT_TOP_CENTER:
            transf.position.x -= finalWidth/2;
            break;
        case PIVOT_TOP_RIGHT:
            transf.position.x -= finalWidth;
            break;
        case PIVOT_MID_LEFT:
            transf.position.y -= finalHeight/2;
            break;
        case PIVOT_MID_CENTER:
            transf.position.x -= finalWidth/2;
            transf.position.y -= finalHeight/2;
            break;
        case PIVOT_MID_RIGHT:
            transf.position.x -= finalWidth;
            transf.position.y -= finalHeight/2;
            break;
        case PIVOT_BOT_LEFT:
            transf.position.y -= finalHeight;
            break;
        case PIVOT_BOT_CENTER:
            transf.position.x -= finalWidth/2;
            transf.position.y -= finalHeight;
            break;
        case PIVOT_BOT_RIGHT:
            transf.position.x -= finalWidth;
            transf.position.y -= finalHeight;
            break;
    }

    //Gera um retângulo para renderizar a textura.
    SDL_Rect renderRect;
    SDL_Rect clipRect;

    int index = get_texture(texture->data);
    if(index < 0) {
        clipRect = (SDL_Rect){0, 0, texture->width / texture->data.frames, texture->height};
        renderRect = (SDL_Rect){transf.position.x, transf.position.y, finalWidth, finalHeight};
    } else {
        CacheTexture *cacheTexture = (CacheTexture*)get_item_at(textureCache, index);
        clipRect = (SDL_Rect){(texture->width / texture->data.frames) * (int)(cacheTexture->step / texture->data.delay), 0,
                                texture->width / texture->data.frames, texture->height};
        renderRect = (SDL_Rect){transf.position.x, transf.position.y, finalWidth, finalHeight};
    }

    //Manda a textura para o renderizador.
    SDL_RenderCopyEx(*rendererRef, texture->image, &clipRect, &renderRect, transf.rotation, NULL, transf.orientation);
}

//Atualiza as animações.
void update_sprites(){
    int i;
    CacheTexture *cacheTexture;
    for(i = 0; i < textureCache.listSize; i++){
        cacheTexture = (CacheTexture*)get_item_at(textureCache, i);
        cacheTexture->step = (cacheTexture->step + 1) % (cacheTexture->texture->data.frames * cacheTexture->texture->data.delay);
    }
}

//Inicializa o cache.
void initialize_cache(){
    textureCache = empty_list();
}
