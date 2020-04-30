#include "inc/gol_core.h"

int main() {

    clock_t begin = clock();

    int ret_val = game_runner_main();

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("TIME_OF_EXE: %f\n", time_spent);

    if(ret_val == 0)       
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;

}
