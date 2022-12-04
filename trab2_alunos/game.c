#include "game.h"
#include <stdio.h>

#define ERROR_MAX_WALLS -10
// globals

Game game; // represents the state of the snake game

// level functions

/**
 * inicia a estrutura apontada por "level" com a informação
 * recebida nos parâmetros
 * Todos os valores são considerados válidos
 */
void level_init(Level *level, int cells_x, int cells_y, int target_size, int target_timeout) {
                        
    //(*level).cells_x = cells_y;
    level->cells_x = cells_x;
    level->cells_y = cells_y;
    level->target_size = target_size;
    level->target_timeout = target_timeout;
    level->nfood = 0;
    level->nwalls = 0; 
}

/**
 * Adiciona uma nova parede ao nível apontada por "level",
 * caso não se tenha atingido o máximo número de paredes
 */
int level_add_wall(Level* level, int type, int pos_x, int pos_y, int size) {
    
    if (level->nwalls == MAX_WALLS) {
        return ERROR_MAX_WALLS;
    } else {
        Wall *wall = &level->walls[level->nwalls];
        wall->type = type;
        wall->start.x = pos_x;
        wall->start.y = pos_y;
        wall->size = size;
        level->nwalls++;
        return SUCCESS;
    }
    return 0;
}


// game functions

/**
 * inicia "game"com a informação recebida nos parâmetros 
 * Todos os valores são considerados válidos
 */
void game_init(int window_size_x, int window_size_y) {
    game.nlevels = 0; 
    game.window_width = window_size_x;
    game.window_height = window_size_y;
}

/**
 * Adiciona um novo nível a "game"
 * caso não se tenha atingido o máximo número de níveis
 */
int game_add_level( int cells_x, int cells_y, int target_size, int target_timeout) {
    if (game.nlevels == MAX_LEVELS) 
        return ERROR_NO_MORE_LEVELS_PERMITTED;
    level_init(&game.levels[game.nlevels],
               cells_x, cells_y, target_size, target_timeout);
    // incrementa o total de níveis
    game.nlevels++;
    return SUCCESS;
}

/**
 * retorna o endereço do nível corrente
 */
Level *game_curr_level() {
    if (game.nlevels == 0) return NULL;
    return &game.levels[game.nlevels-1];
}
