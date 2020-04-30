#ifndef GOL_CORE_H
#define GOL_CORE_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "gol_rules.h"
#include "gol_op_in_text.h"
#include "gol_op_in_ppm.h"

#ifdef _WIN32
    #include <Windows.h>
#endif

#define INIT_WITH_ONE                   (1u)

#define INIT_WITH_ZERO                  (0u)

#define DO_LOGICAL_OR_OP                (0u)

#define DO_LOGICAL_AND_OP               (1u)

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS                    0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE                    (-1)
#endif

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

int game_runner_main();

#endif /* GOL_CORE_H */

