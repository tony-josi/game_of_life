#include "../inc/gol.h"

/* private functions */
#ifndef _WIN32
    static int sleep_in_ms(long);
#endif

int game_runner_main() {

    int ret_code = 1;
    uint8_t **board;
    int generation_cntr = 0;

    if(!(ret_code = init_board(DEFAULT_INIT_SETUP, &board))) {

        if(!(ret_code = fill_board_init_setup(DEFAULT_INIT_SETUP, board))) {

            print_cur_generation(DEFAULT_INIT_SETUP, board);

            while(!(ret_code = next_generation(DEFAULT_INIT_SETUP, board)) && generation_cntr < MAX_NOOF_GENERATIONS) {

                /* if Windows system */
                #ifdef _WIN32
                    Sleep(DEFAULT_SLEEP_TIME);
                /* UNIX based systems */
                #else
                    sleep_in_ms(DEFAULT_SLEEP_TIME);
                #endif

                print_cur_generation(DEFAULT_INIT_SETUP, board);
                ++generation_cntr;
            
            }
        }
    }

    return ret_code;

}

int init_board(uint32_t size, uint8_t ***Board) {

    uint32_t row_col_size;
    if(size == DEFAULT_INIT_SETUP)
        row_col_size = MAX_BOARD_DEFAULT_SIZE;
    else
        row_col_size = size;

    *Board = (uint8_t **)malloc(row_col_size * sizeof(uint8_t *));

    if(*Board) {
        for (uint32_t i=0; i < row_col_size; i++) {
            (*Board)[i] = (uint8_t *)malloc(row_col_size * sizeof(uint8_t)); 

            if((*Board)[i] == NULL)
                return 1;

        }
    }
    else
        return 1;

    for (uint32_t i = 0; i < row_col_size; i++) 
        for (uint32_t j = 0; j < row_col_size; j++) 
            (*Board)[i][j] = 0;

    return 0;

}

int fill_board_init_setup(uint32_t choice, uint8_t **Board) {

    if(choice == DEFAULT_INIT_SETUP) {
        /* default init for Exploder */
        Board[6][8] = 1;
        Board[7][8] = 1;
        Board[8][8] = 1;
        Board[9][8] = 1;
        Board[10][8] = 1;
        Board[6][10] = 1;
        Board[6][12] = 1;
        Board[7][12] = 1;
        Board[8][12] = 1;
        Board[9][12] = 1;
        Board[10][12] = 1;
        Board[10][10] = 1;
 
    }

    return 0;

}

int next_generation(uint32_t size_arg, uint8_t **Board) {

    int ret_code = 0;
    uint32_t size;
    uint8_t **rule_1_temp, **rule_2_temp, **rule_3_temp;
    
    if(size_arg == DEFAULT_INIT_SETUP)
        size = MAX_BOARD_DEFAULT_SIZE;
    else
        size = size_arg;

    ret_code |= apply_rule(NEW_BIRTH, size, Board, &rule_1_temp);
    ret_code |= apply_rule(DEATH_BY_ISOLATION, size, Board, &rule_2_temp);
    ret_code |= apply_rule(DEATH_BY_OVERCROWDING, size, Board, &rule_3_temp);

    // combine and free ***

    //clear_board(DEFAULT_INIT_SETUP, 0, Board);
    combine_boards(DEFAULT_INIT_SETUP, 0, Board, rule_1_temp);
    combine_boards(DEFAULT_INIT_SETUP, 1, Board, rule_2_temp);
    combine_boards(DEFAULT_INIT_SETUP, 1, Board, rule_3_temp);

    free_board(DEFAULT_INIT_SETUP, &rule_1_temp);
    free_board(DEFAULT_INIT_SETUP, &rule_2_temp);
    free_board(DEFAULT_INIT_SETUP, &rule_3_temp);

    return ret_code;

}


int apply_rule(rule_t rule, uint32_t size_arg, uint8_t **Board, uint8_t ***Result) {

    rule_fptr_t target_func = NULL;

    int ret_code = 0;
    uint32_t size;
    
    if(size_arg == DEFAULT_INIT_SETUP)
        size = MAX_BOARD_DEFAULT_SIZE;
    else
        size = size_arg;

    switch(rule) {
        case NEW_BIRTH:
            target_func = check_rule_new_births;
            break;
        case DEATH_BY_ISOLATION:
            target_func = check_rule_death_by_isolation;
            break;
        case DEATH_BY_OVERCROWDING:
            target_func = check_rule_death_by_overcrowding;
            break;
        default:
            return 1;
    }

    ret_code |= init_board(DEFAULT_INIT_SETUP, Result);
    ret_code |= (*target_func)(size, Board, *Result);

    return ret_code;

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

    clear_board(DEFAULT_INIT_SETUP, 1, Result);

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

    clear_board(DEFAULT_INIT_SETUP, 1, Result);

    for (uint32_t i = 0; i < size; i++) 
        for (uint32_t j = 0; j < size; j++) {
            if(Board[i][j] == 1) {
                if(nearby_life_counter(i, j, size, Board) >= 4)
                    Result[i][j] = 0;
            }
        } 

    return 0;

}



void print_cur_generation(uint32_t size, uint8_t **Board) {
    
    //int row_col_size;
    if(size == DEFAULT_INIT_SETUP) {
        for(int i = 0; i < MAX_BOARD_DEFAULT_SIZE; i++) {
            printf("|-------------------------------------------------------------------------------|\n|");

            for(int j = 0; j < MAX_BOARD_DEFAULT_SIZE; j++) {
                if(Board[i][j] == 1)
                    printf(" # |");
                else
                    printf("   |");
            }

            printf("\n");

        }

        printf("|-------------------------------------------------------------------------------|\n\n\n");

    }
}

void combine_boards(uint32_t size_arg, uint8_t type, uint8_t **Board1, uint8_t **Board2) {

    uint32_t row_col_size;
    
    if(size_arg == DEFAULT_INIT_SETUP)
        row_col_size = MAX_BOARD_DEFAULT_SIZE;
    else
        row_col_size = size_arg;

    for (uint32_t i = 0; i < row_col_size; i++) 
        for (uint32_t j = 0; j < row_col_size; j++) {
            if(type == 0)
                Board1[i][j] |= Board2[i][j];
            else
                Board1[i][j] &= Board2[i][j];
        }

}

void clear_board(uint32_t size_arg, uint8_t val, uint8_t **Board) {

    uint32_t row_col_size;
    uint8_t intlzr;
    
    if(size_arg == DEFAULT_INIT_SETUP)
        row_col_size = MAX_BOARD_DEFAULT_SIZE;
    else
        row_col_size = size_arg;

    if(val == 0)
        intlzr = 0;
    else
        intlzr = 1;


    for (uint32_t i = 0; i < row_col_size; i++) 
        for (uint32_t j = 0; j < row_col_size; j++) 
            Board[i][j] = intlzr;
}

void free_board(uint32_t size_arg, uint8_t ***Board) {

    uint32_t row_col_size;
    
    if(size_arg == DEFAULT_INIT_SETUP)
        row_col_size = MAX_BOARD_DEFAULT_SIZE;
    else
        row_col_size = size_arg;

    for (uint32_t i = 0; i < row_col_size; i++) {
        free((*Board)[i]);
        (*Board)[i] = NULL;
    }

    free(*Board);
    *Board = NULL;

}


#ifndef _WIN32
    static int sleep_in_ms(long ms) {

        struct timespec ts;
        int res;

        ts.tv_sec = ms / 1000;
        ts.tv_nsec = (ms % 1000) * 1000000;

        do {
            res = nanosleep(&ts, &ts);
        } while (res);

        return res;
    }
#endif