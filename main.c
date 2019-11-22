#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

//Dimensões da janela.
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#include "engine/util/list.h"
#include "sdl/imgcoordinate.h"

//Janela e renderizador de janela.
SDL_Window* gameWindow = NULL;
SDL_Renderer* gameRenderer = NULL;

#include "sdl/starter.h"
#include "sdl/texture.h"

//Textura de fundo.
Texture* background;
Texture* test;

//Tamanho do mapa.
#define MAP_SIZE 6

#include "engine/util/util.h"
#include "engine/util/coordinate.h"
#include "engine/tile/tile.h"
#include "engine/map/map.h"
#include "engine/entity/actor.h"

//Se o jogo acabou.
bool gameEnded = false;

#include "game/game.h"

//Se o usuário deseja sair do jogo.
bool quit = false;

int main(int argc, char *argv[]){
    if(init_graphics("Mundo de Wumpus", &gameWindow, &gameRenderer)){

        clear_graphics();
        render_graphics();

        begin_game();

        SDL_Event e;
        while(!quit) {
            if(gameEnded) {
                end_game();
            }
            //Executa Eventos na Fila.
            while(SDL_PollEvent(&e) != 0) {

                //Se o Usuário decide sair ou não.
                if(e.type == SDL_QUIT) {
                    quit = true;
                } else if( e.type == SDL_KEYDOWN ) {
                    press_key(e.key.keysym.sym);
                }
            }
            clear_graphics();

            render_map();
            render_actors();

            render_graphics();
            update_sprites();
        }
        //Fecha os gráficos quando o laço acaba.
        close_graphics();
    }
    return 0;
}
