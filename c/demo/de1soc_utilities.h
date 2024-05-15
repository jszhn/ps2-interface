//
// Created by wikid on 15/05/2024.
//

#ifndef DE1SOC_UTILITIES_H
#define DE1SOC_UTILITIES_H

#include "../types.h"

typedef struct PIXEL_t {
    vuint_32 BUFFER;
    vuint_32 BACK_BUFFER;
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

/*
 * Device utilities
 */
void hex_write_single (uint_8 display_num, uint_32 write_value);
void hex_write_group (uint_8 group_num, uint_32 write_value);
void hex_write_full (uint_32 write_value);

/*
 * VGA utilities
 */
void vga_wait_vsync (void);

#endif
