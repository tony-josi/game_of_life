#ifndef GOL_RULES_H
#define GOL_RULES_H

#include "gol_core_data.h"

int nearby_life_counter(int , int , int , uint8_t **);
int check_rule_new_births(uint32_t, uint8_t **, uint8_t **) __attribute__((flatten));
int check_rule_death_by_isolation(uint32_t, uint8_t **, uint8_t **) __attribute__((flatten));
int check_rule_death_by_overcrowding(uint32_t, uint8_t **, uint8_t **) __attribute__((flatten));

#endif /* GOL_RULES_H */
