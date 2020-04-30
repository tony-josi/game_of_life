#ifndef GOL_OP_IN_TEXT_H
#define GOL_OP_IN_TEXT_H

#include "gol_core_data.h"

#if !(OUTPUT_IN_PPM)
void print_cur_generation(uint32_t, uint8_t **);
void align_string(uint32_t, char *);
#endif /* OUTPUT_IN_PPM */

#endif /* GOL_OP_IN_TEXT_H */
