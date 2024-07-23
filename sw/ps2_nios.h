/*
 * PS/2 interrupt utilities for Nios II
 */
#ifndef PS2_NIOS_H
#define PS2_NIOS_H

#include "ps2.h"
#include "nios_control_register_macros.h"

// General-purpose expandable interrupt handler
void nios_interrupt_handler (void);
// PS/2-specific ISR
void ps2_interrupt_service_routine (void);
// Single-use function to enable interrupts. Ideal for use within main()
void ps2_enable_interrupts (void);
// Single-use function to disable interrupts. Ideal for use within main()
void ps2_disable_interrupts (void);

#endif