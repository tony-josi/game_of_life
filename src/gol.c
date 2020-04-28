#include "../inc/gol.h"

/* private functions */
#ifndef _WIN32
    static int sleep_in_ms(long);
#endif

static long colors[] = {0xFF0000, 0x00FF00, 0x0000FF};

static unsigned char buf[3L*PPM_SIZE*PPM_SIZE];

static void align_string(uint32_t, char *);
static int init_temp_board(tboard_t *);
static void free_temp_board(tboard_t *);
static void buf_clear(void);
static void buf_set(int , int , long);
static void buf_set_pixel(int , int , long);
static void buf_write(void);

int game_runner_main() {

    int ret_code = 1;
    uint8_t **board;
    int generation_cntr = 0;
    tboard_t temp_boards;

    if((ret_code = init_temp_board(&temp_boards))) {
        printf("ERR: INIT ERR\n");
        return ret_code;
    }

    if(!(ret_code = init_board(DEFAULT_INIT_SETUP, &board))) {

        if(!(ret_code = fill_board_init_setup(DEFAULT_INIT_SETUP, board))) {

            write_ppm_cur_generation(DEFAULT_INIT_SETUP, board);

            while(!(ret_code = next_generation(DEFAULT_INIT_SETUP, board, temp_boards)) 
            && generation_cntr < MAX_NOOF_GENERATIONS) {

                /* if Windows system */
                #ifdef _WIN32
                    Sleep(DEFAULT_SLEEP_TIME);
                /* UNIX based systems */
                #else
                    sleep_in_ms(DEFAULT_SLEEP_TIME);
                #endif

                write_ppm_cur_generation(DEFAULT_INIT_SETUP, board);
                ++generation_cntr;
            
            }
        }
    }

    free_temp_board(&temp_boards);
    free_board(DEFAULT_INIT_SETUP, &board);

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
        /*
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
        */

        /* default init for Small Exploder */
        /*
        Board[9][8] = 1;
        Board[9][9] = 1;
        Board[9][10] = 1;
        Board[8][9] = 1;
        Board[10][8] = 1;
        Board[10][10] = 1;
        Board[11][9] = 1;
        */

        /* default init for 10 Cell Row */
        /*
        Board[10][5] = 1;
        Board[10][6] = 1;        
        Board[10][7] = 1;
        Board[10][8] = 1;        
        Board[10][9] = 1;
        Board[10][10] = 1;
        Board[10][11] = 1;
        Board[10][12] = 1;        
        Board[10][13] = 1;
        Board[10][14] = 1;
        */

        /* default init for Lightweight Spaceship */
        /*
        Board[8][8] = 1;
        Board[8][9] = 1;        
        Board[8][10] = 1;
        Board[8][11] = 1;        
        Board[9][7] = 1;
        Board[9][11] = 1;
        Board[10][11] = 1;
        Board[11][7] = 1;        
        Board[11][10] = 1;
        */

       /* default init for Gosper Glider Gun */
       /* NOTE: Increase the MAX_BOARD_DEFAULT_SIZE in gol.h to 80 or above 
       also increase MAX_NOOF_GENERATIONS to 200 or above */
       /*
       // left square 
       Board[10][10] = 1;
       Board[10][11] = 1;
       Board[11][10] = 1;
       Board[11][11] = 1;
       // left diamond 
       Board[10][19] = 1;
       Board[10][20] = 1;
       Board[11][18] = 1;
       Board[11][20] = 1;
       Board[12][18] = 1;
       Board[12][19] = 1;
       // glidr b/w diamonds 
       Board[12][26] = 1;
       Board[12][27] = 1;
       Board[13][26] = 1;
       Board[13][28] = 1;
       Board[14][26] = 1;
       // right diamond 
       Board[8][33] = 1;
       Board[8][34] = 1;
       Board[9][32] = 1;
       Board[9][34] = 1;
       Board[10][32] = 1;
       Board[10][33] = 1;
       // bottum glidr 
       Board[20][34] = 1;
       Board[20][35] = 1;
       Board[20][36] = 1;
       Board[21][34] = 1;
       Board[22][35] = 1;
       // right square 
       Board[8][44] = 1;
       Board[8][45] = 1;
       Board[9][44] = 1;
       Board[9][45] = 1;
       // glidr below right square 
       Board[15][45] = 1;
       Board[15][46] = 1;
       Board[16][45] = 1;
       Board[16][47] = 1;
       Board[17][45] = 1;
       */

       /* default init for random live cells */
       
        srand(time(0)); 
        for (uint32_t i = 0; i < MAX_BOARD_DEFAULT_SIZE; i++) 
            for (uint32_t j = 0; j < MAX_BOARD_DEFAULT_SIZE; j++) 
                Board[i][j] = RAND_GEN(2);
        
        
    }
    return 0;

}

int next_generation(uint32_t size_arg, uint8_t **Board, tboard_t tboard) {

    int ret_code = 0;
    uint32_t size;
    
    if(size_arg == DEFAULT_INIT_SETUP)
        size = MAX_BOARD_DEFAULT_SIZE;
    else
        size = size_arg;

    clear_board(DEFAULT_INIT_SETUP, INIT_WITH_ZERO, tboard.rule_1_temp_board);
    clear_board(DEFAULT_INIT_SETUP, INIT_WITH_ONE, tboard.rule_2_temp_board);
    clear_board(DEFAULT_INIT_SETUP, INIT_WITH_ONE, tboard.rule_3_temp_board);

    ret_code |= apply_rule(NEW_BIRTH, size, Board, tboard.rule_1_temp_board);
    ret_code |= apply_rule(DEATH_BY_ISOLATION, size, Board, tboard.rule_2_temp_board);
    ret_code |= apply_rule(DEATH_BY_OVERCROWDING, size, Board, tboard.rule_3_temp_board);

    // combine ***
    combine_boards(DEFAULT_INIT_SETUP, DO_LOGICAL_OR_OP, Board, tboard.rule_1_temp_board);
    combine_boards(DEFAULT_INIT_SETUP, DO_LOGICAL_AND_OP, Board, tboard.rule_2_temp_board);
    combine_boards(DEFAULT_INIT_SETUP, DO_LOGICAL_AND_OP, Board, tboard.rule_3_temp_board);

    return ret_code;

}


int apply_rule(rule_t rule, uint32_t size_arg, uint8_t **Board, uint8_t **Result) {

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

    ret_code |= (*target_func)(size, Board, Result);

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


void print_cur_generation(uint32_t size, uint8_t **Board) {

    char index[5];
    char rw_index[5];
    
    //int row_col_size;
    if(size == DEFAULT_INIT_SETUP) {

        printf("   |");
        for(int i = 0; i < MAX_BOARD_DEFAULT_SIZE; i++) {
            sprintf(rw_index, "%d", i);
            align_string(5, rw_index);
            printf("%s|", rw_index);
        }
        printf("\n");
        
        for(int i = 0; i < MAX_BOARD_DEFAULT_SIZE; i++) {
            
            sprintf(index, "%d", i);
            align_string(5, index);
//            printf("%s|-------------------------------------------------------------------------------|\n   |", index);

            printf("%s|", index);


            for(int j = 0; j < MAX_BOARD_DEFAULT_SIZE; j++) {
                if(Board[i][j] == 1)
                    printf("\u2588\u2588\u2588 ");
                else
                    printf("    ");
            }

            printf("\n");

        }

        //printf("   |-------------------------------------------------------------------------------|\n\n\n");
        printf("\n\n\n");
    }
}


void write_ppm_cur_generation(uint32_t size, uint8_t **Board) {

    buf_clear();
    
    if(size == DEFAULT_INIT_SETUP) {
        
        for(int i = 0; i < MAX_BOARD_DEFAULT_SIZE; i++) {
            for(int j = 0; j < MAX_BOARD_DEFAULT_SIZE; j++) {
                if(Board[i][j] == 1)
                    buf_set_pixel(j * PIXEL_SIZE, i * PIXEL_SIZE, colors[0]);
                else
                    buf_set_pixel(j * PIXEL_SIZE, i * PIXEL_SIZE, 0x000000);
            }

        }

    }

    buf_write();
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
        memset(Board[i], intlzr, row_col_size);

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

static void align_string(uint32_t size, char *str) {

    uint32_t i = 0;
    while(i < (size - 1)) {
        i++;
        if(*str == '\0') {
            *str = ' ';
            break;
        }
        str++;
    }

    while(i < (size - 1)) {
        i++;
        *str = ' ';
        str++;
    }

    *str = '\0';
}

static int init_temp_board(tboard_t *tboard) {

    int ret_code = 0;

    ret_code |= init_board(DEFAULT_INIT_SETUP, &(tboard->rule_1_temp_board));
    ret_code |= init_board(DEFAULT_INIT_SETUP, &(tboard->rule_2_temp_board));
    ret_code |= init_board(DEFAULT_INIT_SETUP, &(tboard->rule_3_temp_board));

    return ret_code;

}

static void free_temp_board(tboard_t *tboard) {

    free_board(DEFAULT_INIT_SETUP, &(tboard->rule_1_temp_board));
    free_board(DEFAULT_INIT_SETUP, &(tboard->rule_2_temp_board));
    free_board(DEFAULT_INIT_SETUP, &(tboard->rule_3_temp_board));

}

static void buf_clear(void)
{
    memset(buf, 0, sizeof(buf));
}

static void buf_set(int x, int y, long color)
{
    if (x >= 0 && x < PPM_SIZE && y >= 0 && y < PPM_SIZE) {
        buf[y*3L*PPM_SIZE + x*3L + 0] = color >> 16;
        buf[y*3L*PPM_SIZE + x*3L + 1] = color >>  8;
        buf[y*3L*PPM_SIZE + x*3L + 2] = color >>  0;
    }
}

static void buf_set_pixel(int x, int y, long color) {

    for(int m = -(PIXEL_SIZE); m < PIXEL_SIZE; m++)
        for(int n = -(PIXEL_SIZE); n < PIXEL_SIZE; n++)
            buf_set(x + m, y + n, color);

}

static void buf_write(void) {
    printf("P6\n%d %d\n255\n", PPM_SIZE, PPM_SIZE);
    fwrite(buf, sizeof(buf), 1, stdout);
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
