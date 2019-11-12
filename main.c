#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//Dimens�es da janela.
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#include "sdl/coordinate.h"

//Janela e renderizador de janela.
SDL_Window* gameWindow = NULL;
SDL_Renderer* gameRenderer = NULL;

#include "sdl/texture.h"
#include "sdl/starter.h"

//Textura de fundo.
Texture* background;
Texture* test;

//Tamanho do mapa.
#define MAP_SIZE 5

#include "game/util/util.h"
#include "game/util/coordinate.h"
#include "game/tile/tile.h"
#include "game/entity/actor.h"
#include "game/map.h"
#include "game/game.h"

//Se o usu�rio deseja sair do jogo.
bool quit = false;

int main(int argc, char *argv[]){
    if(init_graphics("Mundo de Wumpus", gameWindow, gameRenderer)){

        begin_game();

        SDL_Event e;
        while(!quit)
        {
            //Executa Eventos na Fila
            while(SDL_PollEvent(&e) != 0)
            {
                //Se o Usu�rio decide sair ou n�o
                if(e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
        }
        //Fecha os gr�ficos quando o la�o acaba.
        close_graphics(gameWindow, gameRenderer);
    }
    return 0;
}
