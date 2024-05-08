/*
 * General-purpose asm subroutines
 * #include this file within your main file only
 */
#ifndef PS2_NIOS_ASM_H
#define PS2_NIOS_ASM_H

#include "ps2_nios.h"

void nios_reset_processor (void)__attribute__ ((section (".reset")));
void nios_reset_processor (void) {
    // derived from Altera's DE1-SoC Nios II documentation
    asm(".set noat"); // compiler magic
    asm(".set nobreak");
    asm("movia r2, main"); // move main function address to r2
    asm("jmp r2"); // call function
}

void nios_exception_processor (void)__attribute__((section(".exceptions")));
void nios_exception_processor (void) {
    // derived from Altera's DE1-SoC Nios II documentation
    asm(".set noat"); // compiler magic
    asm(".set nobreak");

    // allocate space on the stack
    asm("subi sp, sp, 128");
    asm("stw et, 96(sp)");
    asm("rdctl et, ctl4");
    asm("beq et, r0, SKIP_EA_DEC"); // checks if interrupt is not external
    asm("subi ea, ea, 4"); // standard decrement so next instruction is properly run
    asm("SKIP_EA_DEC:");

    // save all registers on the stack
    asm("stw r1, 4(sp)");
    asm("stw r2, 8(sp)");
    asm("stw r3, 12(sp)");
    asm("stw r4, 16(sp)");
    asm("stw r5, 20(sp)");
    asm("stw r6, 24(sp)");
    asm("stw r7, 28(sp)");
    asm("stw r8, 32(sp)");
    asm("stw r9, 36(sp)");
    asm("stw r10, 40(sp)");
    asm("stw r11, 44(sp)");
    asm("stw r12, 48(sp)");
    asm("stw r13, 52(sp)");
    asm("stw r14, 56(sp)");
    asm("stw r15, 60(sp)");
    asm("stw r16, 64(sp)");
    asm("stw r17, 68(sp)");
    asm("stw r18, 72(sp)");
    asm("stw r19, 76(sp)");
    asm("stw r20, 80(sp)");
    asm("stw r21, 84(sp)");
    asm("stw r22, 88(sp)");
    asm("stw r23, 92(sp)");
    asm("stw r24, 96(sp)");
    asm("stw r25, 100(sp)");
    asm("stw r26, 104(sp)");
    asm("stw r28, 112(sp)");
    asm("stw r29, 116(sp)");
    asm("stw r30, 120(sp)");
    asm("stw r31, 124(sp)");
    asm("addi fp, sp, 128");

    asm ("call nios_interrupt_handler"); // call C-lang interrupt handler

    // restore registers from stack
    asm("ldw r1, 4(sp)");
    asm("ldw r2, 8(sp)");
    asm("ldw r3, 12(sp)");
    asm("ldw r4, 16(sp)");
    asm("ldw r5, 20(sp)");
    asm("ldw r6, 24(sp)");
    asm("ldw r7, 28(sp)");
    asm("ldw r8, 32(sp)");
    asm("ldw r9, 36(sp)");
    asm("ldw r10, 40(sp)");
    asm("ldw r11, 44(sp)");
    asm("ldw r12, 48(sp)");
    asm("ldw r13, 52(sp)");
    asm("ldw r14, 56(sp)");
    asm("ldw r15, 60(sp)");
    asm("ldw r16, 64(sp)");
    asm("ldw r17, 68(sp)");
    asm("ldw r18, 72(sp)");
    asm("ldw r19, 76(sp)");
    asm("ldw r20, 80(sp)");
    asm("ldw r21, 84(sp)");
    asm("ldw r22, 88(sp)");
    asm("ldw r23, 92(sp)");
    asm("ldw r24, 96(sp)");
    asm("ldw r25, 100(sp)");
    asm("ldw r26, 104(sp)");
    asm("ldw r28, 112(sp)");
    asm("ldw r29, 116(sp)");
    asm("ldw r30, 120(sp)");
    asm("ldw r31, 124(sp)");

    asm("addi sp, sp, 128"); // clear allocated space
    asm("eret"); // return from exception processor
}

#endif