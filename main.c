#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//Dimensões da janela.
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#include "engine/util/list.h"
#include "sdl/imgcoordinate.h"

//Janela e renderizador de janela.
SDL_Window* gameWindow = NULL;
SDL_Renderer* gameRenderer = NULL;

#include "sdl/cache.h"
#include "sdl/starter.h"
#include "sdl/texture.h"

//Textura de fundo.
Texture* background;
Texture* test;

//Tamanho do mapa.
#define MAP_SIZE 5

#include "engine/util/util.h"
#include "engine/util/coordinate.h"
#include "engine/tile/tile.h"
#include "engine/entity/actor.h"
#include "engine/map/map.h"
#include "game/game.h"

//Se o usuário deseja sair do jogo.
bool quit = false;

int main(int argc, char *argv[]){
    if(init_graphics("Mundo de Wumpus", &gameWindow, &gameRenderer)){

        clear_graphics();

        Texture tex = load_texture((TextureData){"res/player_b.png", 1});

        render_texture(&tex, (Transform){{SCREEN_WIDTH/2, SCREEN_HEIGHT/2}, 0, 5.0, false}, PIVOT_MID_CENTER, 1.0F);

        render_graphics();

        begin_game();

        SDL_Event e;
        while(!quit)
        {
            //Executa Eventos na Fila
            while(SDL_PollEvent(&e) != 0)
            {
                //Se o Usuário decide sair ou não
                if(e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
        }
        //Fecha os gráficos quando o laço acaba.
        close_graphics();
    }
    return 0;
}
