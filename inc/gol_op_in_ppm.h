#ifndef GOL_OP_IN_PPM_H
#define GOL_OP_IN_PPM_H

#include "gol_core_data.h"
#include <string.h>

#if OUTPUT_IN_PPM
void buf_clear(void);
void buf_set(int , int , long);
void buf_set_pixel(int , int , long);
void buf_write(void);
void write_ppm_cur_generation(uint32_t, uint8_t **);
#endif /* OUTPUT_IN_PPM */

#endif /* GOL_OP_IN_PPM_H */

