#ifndef GOL_CORE_UTILS_H
#define GOL_CORE_UTILS_H

#include "gol_core_data.h"
#include "gol_core.h"


#ifndef _WIN32
    int sleep_in_ms(long);
#endif

int init_board(uint32_t, uint8_t ***);
int fill_board_init_setup(uint32_t, uint8_t **);
void free_board(uint32_t, uint8_t ***);
void clear_board(uint32_t, uint8_t, uint8_t **);
int init_temp_board(tboard_t *);
void free_temp_board(tboard_t *);

#endif /* GOL_CORE_UTILS_H */
