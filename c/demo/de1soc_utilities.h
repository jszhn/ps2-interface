//
// Created by wikid on 15/05/2024.
//

#ifndef DE1SOC_UTILITIES_H
#define DE1SOC_UTILITIES_H

#include "../types.h"

typedef struct FB_t {
    vuint_16 pixels[256][512];
} FB_t;

typedef struct PIXEL_t {
    FB_t *volatile BUFFER;
    FB_t *volatile BACK_BUFFER;
    vuint_32 RES;
    vuint_32 STATUS;
} PIXEL_t;

// VGA memory addresses
#define RGB_RESAMPLER_BASE 0xFF203010
#define PIXEL_BUF_CTRL_BASE 0xFF203020
#define CHAR_BUF_CTRL_BASE 0xFF203030

// Other device memory addresses
#define HEX3_HEX0_BASE 0xFF200020
#define HEX5_HEX4_BASE 0xFF200030

extern uint_32 x_previous, y_previous;

/*
 * Device utilities
 */
void hex_write_single (uint_8 display_num, uint_32 write_value);
void hex_write_group (uint_8 group_num, uint_32 write_value);
void hex_write_full (uint_32 write_value);

/*
 * VGA utilities
 *  Many graphics functions from this great API by Nick Biancolin
 *      https://github.com/nbiancolin/DE1SOC-VideoApi
 */
void vga_wait_vsync (void);
inline void vga_draw_pixel (int x, int y, uint_16 colour);
inline uint_16 vga_colour_from_rgb (uint_8 r, uint_8 g, uint_8 b);

#endif
