#include "ps2.h"

PS2_t *const PS2_b = (PS2_t*) PS2_BASE;
PS2_t *const PS2_dp = (PS2_t*) PS2_DUAL_PORT; // unused here

uint_8 intellimouse; // for special PS/2 mice with scroll wheels

// these are mouse parameters set depending on application
const uint_8 kResolution = 0x02; // 2 counts per mm
const uint_8 kSampleRate = 40;

void ps2_read_mouse (uint_8* byte1, uint_8* byte2, uint_8* byte3, uint_8* byte4) {
    while (PS2_b->RAVAIL < 3); // wait for three bytes
    *byte1 = PS2_b->DATA;
    *byte2 = PS2_b->DATA;
    *byte3 = PS2_b->DATA;
    if (intellimouse & 0x1) {
        while (PS2_b->RAVAIL < 1); // wait for fourth byte
        *byte4 = PS2_b->DATA;
    } else return;
}

void ps2_init_mouse (void) {
    // in general this assumes that hardware problems are not our problem (no ACK check, etc.)

    // reset mouse
    PS2_b->DATA = PS2_RESET;
    while (ps2_is_fifo_empty()); // we must poll for an ACK signal
    uint_8 read_byte = PS2_b->DATA;
    while (ps2_is_fifo_empty());
    if (PS2_b->DATA == PS2_STF) return; // self-test failed

    // check for intellimouse hardware
    PS2_b->DATA = PS2_SSR;
    PS2_b->DATA = 0xC8; // rate == 200
    PS2_b->DATA = PS2_SSR;
    PS2_b->DATA = 0x64; // rate == 100
    PS2_b->DATA = PS2_SSR;
    PS2_b->DATA = 0x50; // rate == 80
    ps2_clear_fifo();
    PS2_b->DATA = PS2_ID;
    while (PS2_b->RAVAIL < 2); // wait for two bytes
    if (PS2_b->DATA != PS2_ACK) return;
    read_byte == PS2_b->DATA;
    if (read_byte == 0x03)
        intellimouse = 1;
    else intellimouse = 0;

    // set sample rate
    PS2_b->DATA = PS2_SSR;
    PS2_b->DATA = kSampleRate;

    // set resolution
    PS2_b->DATA = 0xE8;
    PS2_b->DATA = kResolution;

    // enable data reporting and clear output FIFO
    PS2_b->DATA = PS2_EN;
    while (!ps2_is_fifo_empty()) {
        ps2_clear_fifo();
    }
}

inline uint_8 ps2_is_fifo_empty (void) {
    return (PS2_b->RVALID & 0b10000000) == 0;
}

void ps2_clear_fifo (void) {
    uint_8 input_byte;
    while (ps2_is_fifo_empty())
        input_byte = PS2_b->DATA;
}