#include "../inc/gol_rules.h"

int nearby_life_counter(int i, int j, int size, uint8_t **Buffer) {
    
    int cntr = 0;

    if((i - 1) >= 0) {
        if(Buffer[i - 1][j] == 1)   cntr++;
        if((j - 1) >= 0) 
            if(Buffer[i - 1][j - 1] == 1) cntr++;
        if((j + 1) < size) 
            if(Buffer[i - 1][j + 1] == 1) cntr++;
    }

    if((i + 1) < size) {
        if(Buffer[i + 1][j] == 1)   cntr++;
        if((j - 1) >= 0) 
            if(Buffer[i + 1][j - 1] == 1) cntr++;
        if((j + 1) < size) 
            if(Buffer[i + 1][j + 1] == 1) cntr++;
    }

    if((j - 1) >= 0)
        if(Buffer[i][j - 1] == 1) cntr++;
    if((j + 1) < size)
        if(Buffer[i][j + 1] == 1) cntr++;

    return cntr;
}

int check_rule_new_births(uint32_t size, uint8_t **Board, uint8_t **Result) {

    for (uint32_t i = 0; i < size; i++) 
        for (uint32_t j = 0; j < size; j++) {
            if(Board[i][j] == 0) {
                if(nearby_life_counter(i, j, size, Board) == 3)
                    Result[i][j] = 1;
            }
        } 

    return 0;

}

int check_rule_death_by_isolation(uint32_t size, uint8_t **Board, uint8_t **Result) {

    //clear_board(DEFAULT_INIT_SETUP, 1, Result);

    for (uint32_t i = 0; i < size; i++) 
        for (uint32_t j = 0; j < size; j++) {
            if(Board[i][j] == 1) {
                if(nearby_life_counter(i, j, size, Board) <= 1)
                    Result[i][j] = 0;
            }
        } 

    return 0;

}

int check_rule_death_by_overcrowding(uint32_t size, uint8_t **Board, uint8_t **Result) {

    //clear_board(DEFAULT_INIT_SETUP, 1, Result);

    for (uint32_t i = 0; i < size; i++) 
        for (uint32_t j = 0; j < size; j++) {
            if(Board[i][j] == 1) {
                if(nearby_life_counter(i, j, size, Board) >= 4)
                    Result[i][j] = 0;
            }
        } 

    return 0;

}
