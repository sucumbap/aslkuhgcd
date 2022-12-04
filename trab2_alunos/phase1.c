#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "strutils.h"

//Global constants
#define STR_OK 0
#define LEVELS_FILE_NAME "levels.txt"
#define MAX_LINE 256
#define MAX_CMD_NAME 20

//errors constants

#define STATUS_OK 0
#define ERROR_INT_EXPECTED -1
#define ERROR_EOL_EXPECTED -2
#define ERROR_INVALID_CMD -3
#define ERROR_CHAR_EXPECTED -4

//show error function
void show_error(int error , int line, int col){
	printf("error on line %d, col %d: ", line , col);
	switch(error) {
		case ERROR_EOL_EXPECTED:
			printf("end of line expected!\n");
			break;
		case ERROR_INT_EXPECTED:
			printf("int expected!\n");
			break;
		case ERROR_INVALID_CMD:
			printf("int cmd!\n");
			break;
		case ERROR_CHAR_EXPECTED:
			printf("char expected!\n");
			break;
		default:
			printf("unknown error!\n");
			break;
	}
}

bool read_more_error( const char line[] , int *pos){
	//if we can read more from in an error
	char w[2];
	if(str_next(line, pos, w , 2) != EOL) return true;
	else return false;
}

//commands processing

//GAME
int cmd_game_config(const char line[] , int *pos) {
	int window_size_x, window_size_y;
	
	if (str_next_int(line, pos, &window_size_x) != STR_OK)
		return ERROR_INT_EXPECTED;
	
	if (str_next_int(line, pos, &window_size_y) != STR_OK)
		return ERROR_INT_EXPECTED;
		
	if(read_more_error(line, pos)) return ERROR_EOL_EXPECTED;
		
	printf("\twindow_size_x = %d\n", window_size_x);
	printf("\twindow_size_y = %d\n", window_size_y);
	return STATUS_OK;
}

//LEVEL
int cmd_level_config(const char line[] , int *pos) {
	int cells_x, cells_y, target_size, target_timeout;
    char word[7];
	
	if(str_next_int(line, pos, &cells_x) != STR_OK)
		return ERROR_INT_EXPECTED;
        
	if(str_next_int(line, pos, &cells_y) != STR_OK)
		return ERROR_INT_EXPECTED;
    
    if ((str_next(line, pos, word, MAX_CMD_NAME)) != STR_OK){
        return ERROR_INT_EXPECTED;}
        
	if (str_next_int(line, pos, &target_size) != STR_OK)
		return ERROR_INT_EXPECTED;
        
    if(str_next_int(line, pos, &target_timeout) != STR_OK)
		return ERROR_INT_EXPECTED;
	
	if(read_more_error(line, pos)) 
        return ERROR_EOL_EXPECTED;
	
    else {
        printf("\tcells_x = %d\n", cells_x);
        printf("\tcells_y = %d\n", cells_y);
        
        printf("\ttarget_size = %d\n", target_size);
        printf("\ttarget_timeout = %d\n", target_timeout);
    }
	return STATUS_OK;
}

//WALL
int cmd_wall_config(const char line[] , int *pos) {
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
	
	printf("\ttype = %c\n", type);
	printf("\tpos_x = %d\n", pos_x);
	printf("\tpos_y = %d\n", pos_y);
	printf("\tsize = %d\n", size);
	return STATUS_OK;
}

//FOOD
int cmd_food_config(const char line[] , int *pos) {
	int pos_x, pos_y, lifetime, energy;
	
	if(str_next_int(line, pos, &pos_x) != STR_OK)
		return ERROR_CHAR_EXPECTED;
        
	if(str_next_int(line, pos, &pos_y) != STR_OK)
		return ERROR_INT_EXPECTED;
        
	if(str_next_int(line, pos, &lifetime) != STR_OK)
		return ERROR_INT_EXPECTED;
        
	if(str_next_int(line, pos, &energy) != STR_OK)
		return ERROR_INT_EXPECTED;
	
	if(read_more_error(line, pos)) return ERROR_EOL_EXPECTED;
	
	printf("\tpos_x = %d\n", pos_x);
	printf("\tpos_y = %d\n", pos_y);
	
    printf("\tlifetime = %d\n", lifetime);
	printf("\tenergy = %d\n", energy);
	
	return STATUS_OK;
}

//SNAKE
int cmd_snake_config(const char line[] , int *pos) {
	int pos_x, pos_y, time_to_eat, penalty;
	
	if(str_next_int(line, pos, &pos_x) != STR_OK)
		return ERROR_CHAR_EXPECTED;
	
    if(str_next_int(line, pos, &pos_y) != STR_OK)
		return ERROR_INT_EXPECTED;
	
    if(str_next_int(line, pos, &time_to_eat) != STR_OK)
		return ERROR_INT_EXPECTED;
	
    if(str_next_int(line, pos, &penalty) != STR_OK)
		return ERROR_INT_EXPECTED;
	
	if(read_more_error(line, pos)) return ERROR_EOL_EXPECTED;
	
	
	printf("\tpos_x = %d\n", pos_x);
	printf("\tpos_y = %d\n", pos_y);
	
    printf("\ttime_to_eat= %d\n", time_to_eat);
	printf("\tpenalty= %d\n", penalty);
	
	return STATUS_OK;
}


void load_snake_config(const char levels_filename[]) {

	FILE *flevels = fopen(levels_filename, "r");
	
	if(flevels == NULL){
		printf("erro ao abrir o ficheiro de configuração!\n");
		return;
	}
    
	char line[MAX_LINE];
	int line_number = 0; // current line number
	
	while(fgets(line, MAX_LINE, flevels) != NULL){
		char cmdname[MAX_CMD_NAME];
		int pos = 0;
		
		//nova line
		line_number++;
		

		int res = str_next(line, &pos, cmdname, MAX_CMD_NAME);
		
		if(res == EOL) continue; //on empty line read, reeavaluate while
		if(cmdname[0] == '#') continue; //on comment line, do the same

		str_toupper(cmdname);
		
        printf("%s\n", cmdname);
		if(strcmp(cmdname, "GAME") == 0) {
			int res = cmd_game_config(line, &pos);
			if(res != STATUS_OK) {
				show_error(res, pos, line_number);
				break; //leave the while
			}
		}
		
		else if(strcmp(cmdname, "LEVEL") == 0) {
			int res = cmd_level_config(line, &pos);
			if(res != STATUS_OK){
				show_error(res, pos ,line_number);
				break;
			}
		}
		
		else if(strcmp(cmdname, "WALL") == 0) {
			int res = cmd_wall_config(line, &pos);

			if(res != STATUS_OK){
				show_error(res, pos ,line_number);
				break;
			}
		}
		else if(strcmp(cmdname, "FOOD") == 0) {
			int res = cmd_food_config(line, &pos);
			if(res != STATUS_OK){
				show_error(res, pos ,line_number);
				break;
			}
		}
		else if(strcmp(cmdname, "SNAKE") == 0) {
			int res = cmd_snake_config(line, &pos);
			if(res != STATUS_OK){
				show_error(res, pos ,line_number);
				break;
			}
		}
		else {
			//erro cmd invalido
			show_error(ERROR_INVALID_CMD, line_number, pos);
			break;
		}
	}
	
	//close the file before return
	fclose(flevels);
}


int main() {
	load_snake_config(LEVELS_FILE_NAME);
	return 0;
}
