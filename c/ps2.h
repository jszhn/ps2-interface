/*
 * PS/2 utilities for the DE1-SoC computer
 */
#ifndef PS2_H
#define PS2_H

#include "types.h"

// Base address for the PS2 port
#define PS2_BASE 0xFF200100
// Base address for the PS2 dual port
#define PS2_DUAL_PORT 0xFF200108

// Register types
typedef struct PS2_t {
    vuint_8 DATA;
    vuint_8 RVALID; // only MSB is used
    vuint_16 RAVAIL;
    vuint_32 CTRL;
} PS2_t;

// Global vars, for use with interrupt code
extern PS2_t* const PS2_b;
extern uint_8 mouse_enabled;
extern uint_32 mouse_x, mouse_y, mouse_z;

/*
 * Mouse functions
 */
// Reads mouse data
void ps2_read_mouse (uint_8* byte1, uint_8* byte2, uint_8* byte3, uint_8* byte4);
// Initialises mouse with packet commands
void ps2_init_mouse (void);

/*
 * Multipurpose functions
 */
// Checks if PS2 FIFO is empty: returns 1 if empty, 0 otherwise
uint_8 ps2_is_fifo_empty (void);
// Clears PS2 FIFO
void ps2_clear_fifo (void);

/*
 * Scan codes
 */
#define PS2_BREAK 0xF0

#define PS2_ESC 0x76
#define PS2_TAB 0x0D
#define PS2_CAPS 0x58
#define PS2_LSHIFT 0x12
#define PS2_LCTRL 0x14
#define PS2_SPACE 0x29
#define PS2_BKSPC 0x66
#define PS2_ENTER 0x5A

#define PS2_W 0x1D
#define PS2_A 0x1C
#define PS2_S 0x1B
#define PS2_D 0x23

#define PS2_SPEC 0xE0
#define PS2_UP 0x75
#define PS2_LEFT 0x6B
#define PS2_DOWN 0x72
#define PS2_RIGHT 0x74

// mouse-to-host packets
#define PS2_ACK 0xFA
#define PS2_STP 0xAA // self-test passed
#define PS2_STF 0xFC // self-test failed
#define PS2_ID 0xF2

// keyboard-to-host packets
#define PS2_ECHO 0xEE
#define PS2_RESEND 0xFE

// host-to-mouse packets
#define PS2_RESET 0xFF
#define PS2_EN 0xF4 // enable device
#define PS2_DIS 0xF5 // disable device
#define PS2_SSR 0xF3 // set sample rate

// host-to-keyboard packets
#define PS2k_STATUS 0xED
#define PS2k_SCS 0xF0

#endif