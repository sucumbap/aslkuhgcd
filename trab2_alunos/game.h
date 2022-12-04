#include "include/pglib.h"
 
// ERROR CODES

#define SUCCESS                              0
#define ERROR_INT_EXPECTED                  -1
#define ERROR_EOL_EXPECTED                  -2
#define ERROR_INVALID_CMD                   -3


#define ERROR_NO_MORE_LEVELS_PERMITTED      -50
#define ERROR_GAME_NOT_INITIALIZED         -51

// ENTITIES
 
 
typedef struct {
    Point pos;                  // head position on grid coordinates
    int time_to_eat;            // a penalty occurrs if snake doesn't eat before this time
    int penalty;                // the penalty size if the snake doesn't eat in time
} Snake;


#define HORIZONTAL  1           // horizontal wall
#define VERTICAL    2           // vertical wall

typedef struct {
    Point start;                // wall start location
    int type;                   // horizontal or vertical wall
    int size;                   // wall size
} Wall;


typedef struct {
    Point pos;
    int energy;                 // define the snake grow if eaten
                                // if negative tell the snake reduction if eaten
    int lifetime;               // time to life in seconds
} Food;


#define MAX_WALLS  15
#define MAX_FOOD 4
typedef struct {
    int cells_x;                // width cells number
    int cells_y;                // height cells number
    int target_size;            // snake size to reach in level
    int target_timeout;         // max time to reach target
    int  nwalls;                // number of level walls
    Wall walls[MAX_WALLS];
    int  nfood;                 // number of level food items
    Food food[MAX_FOOD];
   
    Snake snake;                // the snake
} Level;


#define MAX_LEVELS 10
typedef struct {
    int nlevels;                // number of game levels
    Level levels[MAX_LEVELS];   // the levels
    int window_width;           // the game window width  
    int window_height;          // the game windows height
} Game;


// game functions

void game_init(int window_size_x, int window_size_y);

int game_add_level( int cells_x, int cells_y, 
                    int target_size, int target_timeout);

Level *game_curr_level(const char line[] , int *pos);



// level functions

void level_init(Level *level, int cells_x, int cells_y, 
                    int target_size, int target_timeout); 

int level_add_wall(Level* level, int type, int pos_x, int pos_y, int size);
