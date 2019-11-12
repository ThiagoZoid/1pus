//Inicializa a engine gráfica.
bool init_graphics(char title[], SDL_Window* window, SDL_Renderer* renderer){
     bool success = true;

     //Determina a qualidade de redimensionamento de imagens.
     //"0" -> equivale à técnica de redimensionamento "Nearest neighbour",
     //que é preferível para jogos pixelados. Para outros tipos de gráficos,
     //é sugerido um valor maior.
     SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

     if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("%s", SDL_GetError());
        success = false;
     }else{
         //Cria a janela
         window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
         if(window == NULL) {
                printf("%s", SDL_GetError());
                success = false;
         }else{
             //Cria um renderizador
             renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
             if(renderer == NULL){
                printf("%s", SDL_GetError());
             }else{
				//Inicializa a cor de fundo do Renderizador
				SDL_SetRenderDrawColor(renderer, 0x3d, 0x3d, 0x3d, 0x00);

                int imgFlags;
				//Inicializa o carregamento do formato PNG
                imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("%s", IMG_GetError());
				}
				//Inicializa o carregamento do formato JPG
				imgFlags = IMG_INIT_JPG;
				if(!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("%s", IMG_GetError());
				}
            }
        }
    }
    return success;
}

//Desaloca os gráficos.
void close_graphics(SDL_Window* window, SDL_Renderer* renderer){
	//Finaliza as texturas.

	//Finaliza o Renderizador.
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//Finaliza a Janela.
	SDL_DestroyWindow(window);
	window = NULL;

	//Sai dos subsistemas do SDL.
	IMG_Quit();
	SDL_Quit();
}
