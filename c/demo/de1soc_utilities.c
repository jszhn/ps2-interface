#include "de1soc_utilities.h"

// local function definitions
static uint_8 hex_value_from_number (uint_8 write_value);

// local variables
vuint_32 *const HEX30 = (vuint_32*) HEX3_HEX0_BASE;
vuint_32 *const HEX54 = (vuint_32*) HEX5_HEX4_BASE;
PIXEL_t *const PixBuf = (PIXEL_t*) PIXEL_BUF_CTRL_BASE;

uint_32 x_previous = 0, y_previous = 0;

void hex_write_single (uint_8 display_num, uint_32 write_value) {
    // display number ranges from 0-5
    write_value &= 0b11111111; // truncate write value to ensure no interference
    vuint_32* display_addr;

    if (display_num > 5) display_num = 5;
    else if (display_num < 0) display_num = 0;

    if (display_num > 3) {
        display_addr = HEX54;
        display_num -= 4;
    } else
        display_addr = HEX30;

    write_value = hex_value_from_number(write_value);
    uint_32 temp = *display_addr & (0xFFFFFFFF ^ (0b11111111 << (display_num * 8))); // selectively clears a single display
    *display_addr = temp | (write_value << (display_num * 8)); // writes to HEX display
}

void hex_write_group (uint_8 group_num, uint_32 write_value) {
    if (group_num > 2) group_num = 2;
    else if (group_num < 0) group_num = 0;

    hex_write_single(group_num * 2, write_value % 16);
    hex_write_single(group_num * 2 + 1, (write_value / 16) % 16);
}

void hex_write_full (uint_32 write_value) {
    uint_32 count = 0;
    while (count <= 5) { // iterates through each display
        hex_write_single(count, write_value % 16);
        write_value /= 16; // updates value
        count++;
    }
}

static uint_8 hex_value_from_number (uint_8 write_value) {
    switch (write_value) {
        case 1: return 0b0000110;
        case 2: return 0b1011011;
        case 3: return 0b1001111;
        case 4: return 0b1100110;
        case 5: return 0b1101101;
        case 6: return 0b1111101;
        case 7: return 0b0000111;
        case 8: return 0b1111111;
        case 9: return 0b1101111;
        case 10: return 0b1110111; // A
        case 11: return 0b1111100; // B
        case 12: return 0b0111001; // C
        case 13: return 0b1011110; // D
        case 14: return 0b1111001; // E
        case 15: return 0b1110001; // F
        default: return 0b0111111; // 0
    }
}

/*
 *  Many graphics functions from this great API by Nick Biancolin
 *      https://github.com/nbiancolin/DE1SOC-VideoApi
 *      MIT license
 */
void vga_wait_vsync (void) {
    uint_32 status;
    PixBuf->BUFFER = 1; // start the synchronization process; write 1 into front buffer addr register
    status = PixBuf->STATUS; // read status register
    while (status & 0x1) status = PixBuf->STATUS; // polling loop to wait for S bit to go to 0
}

inline void vga_draw_pixel (int x, int y, uint_16 colour) {
    PixBuf->BUFFER->pixels[y][x] = colour;
}

inline uint_16 vga_colour_from_rgb (uint_8 r, uint_8 g, uint_8 b) {
    return (r << 11) | (g << 5) | b;
}