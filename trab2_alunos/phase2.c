#include <stdio.h>
#include "strutils.h"
#include <string.h>
#include "game.h"
#include "pg/pglib.h"
 
// ERROR CODES
#define STR_OK 0
#define SUCCESS                              0
#define ERROR_INT_EXPECTED                  -1
#define ERROR_EOL_EXPECTED                  -2
#define ERROR_INVALID_CMD                   -3
#define ERROR_CHAR_EXPECTED                 -4



#define ERROR_NO_MORE_LEVELS_PERMITTED      -50
#define ERROR_GAME_NOT_INITIALIZED         -51
// globals constants

#define LEVELS_FILE_NAME "levels.txt"
#define MAX_LINE 256
#define MAX_CMD_NAME 20

Game game;

// show error function

void show_error(int error, int line, int col) {
    printf("error on line %d, col %d: ", line, col);
    switch(error) {
        case ERROR_EOL_EXPECTED:
            printf(" end of line expected!\n");
            break;
        case ERROR_INT_EXPECTED:
            printf("int expected!\n");
            break;
        case ERROR_INVALID_CMD:
            printf("invalid cmd!\n");
            break;
        case ERROR_NO_MORE_LEVELS_PERMITTED:
            printf("no more levels permitted");
            break;
        case ERROR_GAME_NOT_INITIALIZED:
            printf("must initialize game first!");
            break;
        default:
            printf("unknown error!\n");
            break;
    }
}

// commands processing

int cmd_game_config(const char line[], int *pos) {
    int window_size_x, window_size_y;
    
    if (str_next_int(line, pos, &window_size_x) != STR_OK){
        return ERROR_INT_EXPECTED;
    }
        
    if (str_next_int(line, pos, &window_size_y) != STR_OK) {
        return ERROR_INT_EXPECTED;
    }
    
    // if we can read more from in an error
    char w[2];
    if (str_next(line, pos, w, 2) != EOL) {
        return ERROR_EOL_EXPECTED;
    }
    game_init(window_size_x, window_size_y);
    game.window_width = window_size_x;
    game.window_height = window_size_y;
    return SUCCESS;
}

int cmd_level_config(const char line[], int *pos)  {
    int cells_x=0, cells_y = 0 , target_size = 0, target_timeout = 0; i = 0;
   if (str_next_int(line, pos, &cells_x) != STR_OK){
        return ERROR_INT_EXPECTED;
    }
        
    if (str_next_int(line, pos, &cells_y) != STR_OK){
        return ERROR_INT_EXPECTED;
    }
        
    if (str_next_int(line, pos, &target_size) != STR_OK){
        return ERROR_INT_EXPECTED;
    }
        
    if (str_next_int(line, pos, &target_timeout) != STR_OK){
        return ERROR_INT_EXPECTED;
    }
        
    // if we can read more from in an error
    char w[2];
    if (str_next(line, pos, w, 2) != EOL) {
        return ERROR_EOL_EXPECTED;
    }
    if (game.level != NULL) {
        return ERROR_NO_MORE_LEVELS_PERMITTED;
    }
    game.level.cells_x = cells_x;
    game.level.cells_y = cells_y;
    game.level.target_size = target_size;
    game.level.target_timeout = target_timeout;
    return game_add_level(cells_x, cells_y, target_size, target_timeout);
}

int cmd_wall_config(const char line[], int *pos) {
    int pos_x, pos_y, size;
	char type;
	
	if(str_next(line, pos, &type , MAX_CMD_NAME) != STR_OK)
		return ERROR_CHAR_EXPECTED;
        
	if(str_next_int(line, pos, &pos_x) != STR_OK)
		return ERROR_INT_EXPECTED;
        
	if(str_next_int(line, pos, &pos_y) != STR_OK)
		return ERROR_INT_EXPECTED;
        
	if(str_next_int(line, pos, &size) != STR_OK)
		return ERROR_INT_EXPECTED;
	
	if(read_more_error(line, pos)) return ERROR_EOL_EXPECTED;

    // while(i < game.level.cells_x * game.level.cells_y) {
    //     if (game.levels.cells[i].type == CELL_EMPTY) {
    //         game.levels.cells[i].type = CELL_WALL;
    //         game.levels.cells[i].wall.type = type;
    //         game.levels.cells[i].wall.pos_x = pos_x;
    //         game.levels.cells[i].wall.pos_y = pos_y;
    //         game.levels.cells[i].wall.size = size;
    //         return SUCCESS;
    //     }
    //     i++;
    // }

    return level_add_wall(game.levels[game.nlevels], type, pos_x, pos_y, size);
}


Level *game_curr_level(const char line[] , int *pos) { 
     struct Level *level;
     if(str_next(line, pos, level->walls[pos].type, MAX_CMD_NAME) != STR_OK)
		return ERROR_CHAR_EXPECTED;
        
	if(str_next_int(line, pos, level->walls.start.x) != STR_OK)
		return ERROR_INT_EXPECTED;
        
	if(str_next_int(line, pos, level->walls.start.y) != STR_OK)
		return ERROR_INT_EXPECTED;
        
	if(str_next_int(line, pos, &size) != STR_OK)
		return ERROR_INT_EXPECTED;
	
	if(read_more_error(line, pos)) return ERROR_EOL_EXPECTED;
    
    return level;
     
}
 
 
void load_snake_config(const char levels_filename[]) {
    
    FILE *flevels = fopen(levels_filename, "r");
    
    if (flevels == NULL) {
        printf("erro ao abrir o ficheiro de connfiguração!\n");
        return;
    }
    
    char line[MAX_LINE];
    
    int line_number = 0; // current line number
    bool game_initialized = false;
    
    
    while(fgets(line, MAX_LINE, flevels) != NULL) {
        char cmdname[MAX_CMD_NAME];
        int pos = 0;
        
        // new line
        line_number++;
        
        int res = str_next(line, &pos, cmdname, MAX_CMD_NAME);
        
        if (res == EOL) continue; // on empty line, reevaluate while condition
        if (cmdname[0] == '#') continue; // on comment line, do the same
        str_toupper(cmdname);
        
        printf("%s\n", cmdname);
        if (strcmp(cmdname, "GAME") == 0) {
            int res = cmd_game_config(line, &pos);
            if (res != SUCCESS) {
                show_error(res, line_number, pos);
                break; // leave the while
            }
            game_initialized = true;
        }
        else if (strcmp(cmdname, "LEVEL") == 0) {
            int res;
            
            if (!game_initialized) {
                res = ERROR_GAME_NOT_INITIALIZED;
            }
            else {
                res = cmd_level_config(line, &pos);
            }
            if (res != SUCCESS) {
                show_error(res, line_number, pos);
                break; // leave the while
            }
        }
        else if (strcmp(cmdname, "WALL") == 0) {
            // call cmd_wall_config
            int res = cmd_wall_config(line, &pos);
            if (res != SUCCESS) {
                show_error(res, line_number, pos);
                break; // leave the while
            }
        }
        // ...
        else {
            // show invalid command error
            show_error(ERROR_INVALID_CMD, line_number, pos);
            break;
        }
    }
    
    // close the file before return
    fclose(flevels);
}



int main() {
    load_snake_config(LEVELS_FILE_NAME);
    return 0;
}
