#include "../inc/gol_op_in_ppm.h"
#include "../inc/gol_core.h"

#if OUTPUT_IN_PPM

static long colors[] = {0xFF0000, 0x00FF00, 0x0000FF};
static unsigned char buf[3L * PPM_SIZE * PPM_SIZE];

void write_ppm_cur_generation(uint32_t size, uint8_t **Board) {

    buf_clear();
    
    if(size == DEFAULT_INIT_SETUP) {
        
        for(int i = 0; i < MAX_BOARD_DEFAULT_SIZE; i++) {
            for(int j = 0; j < MAX_BOARD_DEFAULT_SIZE; j++) {
                if(Board[i][j] == 1)
                    buf_set_pixel(j * PIXEL_SIZE, i * PIXEL_SIZE, colors[0]);
                else
                    buf_set_pixel(j * PIXEL_SIZE, i * PIXEL_SIZE, 0x000000);
            }

        }

    }

    buf_write();
}

void buf_clear(void)
{
    memset(buf, 0, sizeof(buf));
}

void buf_set(int x, int y, long color)
{
    if (x >= 0 && x < (PPM_SIZE) && y >= 0 && y < (PPM_SIZE)) {
        buf[y*3L*PPM_SIZE + x*3L + 0] = color >> 16;
        buf[y*3L*PPM_SIZE + x*3L + 1] = color >>  8;
        buf[y*3L*PPM_SIZE + x*3L + 2] = color >>  0;
    }
}

void buf_set_pixel(int x, int y, long color) {

    for(int m = -(PIXEL_SIZE); m < PIXEL_SIZE; m++)
        for(int n = -(PIXEL_SIZE); n < PIXEL_SIZE; n++)
            buf_set(x + m, y + n, color);

}

void buf_write(void) {
    printf("P6\n%d %d\n255\n", PPM_SIZE, PPM_SIZE);
    fwrite(buf, sizeof(buf), 1, stdout);
}
#endif /* OUTPUT_IN_PPM */

