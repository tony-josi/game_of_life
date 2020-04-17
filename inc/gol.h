#include <stdio.h>
#include <stdint.h>

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <time.h>
#endif

#define MAX_BOARD_DEFAULT_SIZE          (20)

#define DEFAULT_INIT_SETUP              0

#define DEFAULT_SLEEP_TIME              10

#define MAX_NOOF_GENERATIONS            100

#define UNUSED(X)                       (void)X      /* To avoid gcc/g++ warnings */

typedef                                 int (*rule_fptr_t) (uint32_t, uint8_t **, uint8_t **);


typedef enum {
    NEW_BIRTH = 0,
    DEATH_BY_ISOLATION,
    DEATH_BY_OVERCROWDING
} rule_t;

static inline int nearby_life_counter(int i, int j, int size, uint8_t **Buffer) {
    
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

int game_runner_main();
int init_board(uint32_t, uint8_t ***);
int fill_board_init_setup(uint32_t, uint8_t **);
int next_generation(uint32_t, uint8_t **);
int apply_rule(rule_t, uint32_t, uint8_t **, uint8_t ***);
int check_rule_new_births(uint32_t, uint8_t **, uint8_t **);
int check_rule_death_by_isolation(uint32_t, uint8_t **, uint8_t **);
int check_rule_death_by_overcrowding(uint32_t, uint8_t **, uint8_t **);
void print_cur_generation(uint32_t, uint8_t **);
void combine_boards(uint32_t, uint8_t, uint8_t **, uint8_t **);
void free_board(uint32_t, uint8_t ***);
void clear_board(uint32_t, uint8_t, uint8_t **);

