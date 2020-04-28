#ifndef GOL_H
#define GOL_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #include <Windows.h>
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS                    0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE                    (-1)
#endif

#define MAX_BOARD_DEFAULT_SIZE          108

#define DEFAULT_INIT_SETUP              0

#define DEFAULT_SLEEP_TIME              0

#define MAX_NOOF_GENERATIONS            200

#define INIT_WITH_ONE                   (1u)

#define INIT_WITH_ZERO                  (0u)

#define DO_LOGICAL_OR_OP                (0u)

#define DO_LOGICAL_AND_OP               (1u)

#define PIXEL_SIZE                      10

#define PPM_SIZE                        (MAX_BOARD_DEFAULT_SIZE * PIXEL_SIZE)

#define UNUSED(X)                       (void)X      /* To avoid gcc/g++ warnings */

#define RAND_GEN(N)                     (int)((double)rand() / ((double)RAND_MAX + 1) * N)

typedef                                 int (*rule_fptr_t) (uint32_t, uint8_t **, uint8_t **);

typedef struct temp_board {
    uint8_t **rule_1_temp_board;
    uint8_t **rule_2_temp_board;
    uint8_t **rule_3_temp_board;
} tboard_t;

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

#endif /* GOL_H */

