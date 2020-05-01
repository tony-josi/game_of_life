#include "../inc/gol_core.h"
#include "../inc/gol_core_utils.h"

static int next_generation(uint32_t, uint8_t **, tboard_t);
static int apply_rule(rule_t, uint32_t, uint8_t **, uint8_t **);
static void combine_boards(uint32_t, uint8_t, uint8_t **, uint8_t **);
static void output_cur_generation(uint32_t, uint8_t **);
static void sleep_ms();

int game_runner_main() {

    int ret_code = 1;
    uint8_t **board;
    int generation_cntr = 0;
    tboard_t temp_boards;
    UNUSED(sleep_ms);

    if((ret_code = init_temp_board(&temp_boards))) {
        printf("ERR: INIT ERR\n");
        return ret_code;
    }

    if(!(ret_code = init_board(DEFAULT_INIT_SETUP, &board))) {
        if(!(ret_code = fill_board_init_setup(DEFAULT_INIT_SETUP, board))) {
            output_cur_generation(DEFAULT_INIT_SETUP, board);

            while(!(ret_code = next_generation(DEFAULT_INIT_SETUP, board, temp_boards)) 
            && generation_cntr < MAX_NOOF_GENERATIONS) {

                #if DEFAULT_SLEEP_TIME
                sleep_ms();
                #endif

                output_cur_generation(DEFAULT_INIT_SETUP, board);                
                ++generation_cntr;
            }
        }
    }
    free_temp_board(&temp_boards);
    free_board(DEFAULT_INIT_SETUP, &board);
    return ret_code;
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

static void output_cur_generation(uint32_t size, uint8_t **Board) {

    #if OUTPUT_IN_PPM
        write_ppm_cur_generation(size, Board);
    #else
        print_cur_generation(size, Board);
    #endif /* OUTPUT_IN_PPM */
}

static void sleep_ms() {

    /* if Windows system */
    #ifdef _WIN32
        Sleep(DEFAULT_SLEEP_TIME);
    /* UNIX based systems */
    #else
        sleep_in_ms(DEFAULT_SLEEP_TIME);
    #endif
}
