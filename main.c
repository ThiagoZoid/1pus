#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

//Dimens�es da janela.
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

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
#define MAP_SIZE 10

#include "engine/util/util.h"
#include "engine/util/coordinate.h"
#include "engine/tile/tile.h"
#include "engine/map/map.h"
#include "engine/entity/actor.h"
#include "engine/entity/controller.h"
#include "game/game.h"

//Se o usu�rio deseja sair do jogo.
bool quit = false;

int main(int argc, char *argv[]){
    if(init_graphics("Mundo de Wumpus", &gameWindow, &gameRenderer)){

        clear_graphics();
        render_graphics();

        begin_game();

        SDL_Event e;
        while(!quit) {
            //Executa Eventos na Fila.
            while(SDL_PollEvent(&e) != 0) {

                //Se o Usu�rio decide sair ou n�o.
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
        //Fecha os gr�ficos quando o la�o acaba.
        close_graphics();
    }
    return 0;
}
