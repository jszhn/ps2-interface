#include "ps2_nios.h"

void nios_interrupt_handler (void) {
    int ipending = NIOS2_READ_IPENDING();
    if (ipending & 0b10000000) // PS/2 interrupt service routine
        ps2_interrupt_service_routine();
    // for your own interrupts, add your else if statements here
}

void ps2_interrupt_service_routine (void) {
    // TODO: finish this
    // at the end of the ISR, check if interrupt is still pending
    if (PS2_b->CTRL & 0x200) ps2_clear_fifo();
}

inline void ps2_enable_interrupts (void) {
    PS2_b->CTRL = 0x1; // enable on device side
    NIOS2_WRITE_IENABLE(NIOS2_READ_IENABLE() | 0x80); // to avoid disabling interrupts for other devices
    NIOS2_WRITE_STATUS(1); // enable computer-wide interrupts
}

inline void ps2_disable_interrupts (void) {
    PS2_b->CTRL = 0x0; // disable on device side
    NIOS2_WRITE_IENABLE(NIOS2_READ_IENABLE() & 0xFFFFFF7F); // to avoid disabling interrupts for other devices
}