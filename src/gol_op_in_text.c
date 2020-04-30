#include "../inc/gol_op_in_text.h"

#if !(OUTPUT_IN_PPM)

void print_cur_generation(uint32_t size, uint8_t **Board) {

    char index[5];
    char rw_index[5];
    
    //int row_col_size;
    if(size == DEFAULT_INIT_SETUP) {

        printf("   |");
        for(int i = 0; i < MAX_BOARD_DEFAULT_SIZE; i++) {
            sprintf(rw_index, "%d", i);
            align_string(5, rw_index);
            printf("%s|", rw_index);
        }
        printf("\n");
        
        for(int i = 0; i < MAX_BOARD_DEFAULT_SIZE; i++) {
            
            sprintf(index, "%d", i);
            align_string(5, index);
//            printf("%s|-------------------------------------------------------------------------------|\n   |", index);

            printf("%s|", index);


            for(int j = 0; j < MAX_BOARD_DEFAULT_SIZE; j++) {
                if(Board[i][j] == 1)
                    printf("\u2588\u2588\u2588 ");
                else
                    printf("    ");
            }

            printf("\n");

        }

        //printf("   |-------------------------------------------------------------------------------|\n\n\n");
        printf("\n\n\n");
    }
}

void align_string(uint32_t size, char *str) {

    uint32_t i = 0;
    while(i < (size - 1)) {
        i++;
        if(*str == '\0') {
            *str = ' ';
            break;
        }
        str++;
    }

    while(i < (size - 1)) {
        i++;
        *str = ' ';
        str++;
    }

    *str = '\0';
}

#endif /* OUTPUT_IN_PPM */
