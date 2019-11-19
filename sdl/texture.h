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
} TextureData;

//Estrutura de uma textura.
typedef struct texture{
    SDL_Texture     *image;
    TextureData     data;
    int             width;
    int             height;
} Texture;

//Limpa uma textura.
void clear_texture(Texture *texture){
    if(texture && texture->image){
        SDL_DestroyTexture(texture->image);
        free(texture);
    }
}

//Compara duas texturas.
bool compare_textures(Texture *first, Texture *second){
    return *first->data.path == *second->data.path;
}

//Cria dados de textura em branco.
TextureData empty_texture_data(){
    TextureData d;
    d.frames = 1;
    d.path = NULL;
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
    if( loadedSurface == NULL ){
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

//Renderiza uma textura.
void render_texture(Texture* texture, Transform transf, Pivot pos, float fraction){
    int finalWidth = texture->width * transf.scale;
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
    SDL_Rect renderRect = {transf.position.x, transf.position.y, finalWidth * fraction, finalHeight};
    //Manda a textura para o renderizador.
    SDL_RenderCopyEx(*rendererRef, texture->image, NULL, &renderRect, 0, NULL, transf.orientation);
}
