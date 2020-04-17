#include "inc/gol.h"

int main() {

    int ret_val = game_runner_main();

    if(ret_val == 0)       
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;

}
