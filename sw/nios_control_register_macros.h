/*
 * Derived from Altera's DE1-SoC Nios II documentation
 *      See https://www-ug.eecg.toronto.edu/desl/handouts/DE1-SoC_Computer_Nios.pdf
 *      - In general not sure why there's single-run do-while loops here
 *      - Not inlining bc compiler problems
 */
#ifndef NIOS_CONTROL_REGISTER_MACROS_H
#define NIOS_CONTROL_REGISTER_MACROS_H

int NIOS2_READ_STATUS (void) {
    int i;
    do {
        i = __builtin_rdctl(0);
    } while (0);
    return i;
}

int NIOS2_READ_ESTATUS (void) {
    int i;
    do {
        i = __builtin_rdctl(1);
    } while (0);
    return i;
}

int NIOS2_READ_BSTATUS (void) {
    int i;
    do {
        i = __builtin_rdctl(2);
    } while (0);
    return i;
}

int NIOS2_READ_IENABLE (void) {
    int i;
    do {
        i = __builtin_rdctl(3);
    } while (0);
    return i;
}

int NIOS2_READ_IPENDING (void) {
    int i;
    do {
        i = __builtin_rdctl(4);
    } while (0);
    return i;
}

int NIOS2_READ_CPUID (void) {
    int i;
    do {
        i = __builtin_rdctl(5);
    } while (0);
    return i;
}

void NIOS2_WRITE_STATUS (int src) {
    do {
        __builtin_wrctl (0, src);
    } while (0);
}

void NIOS2_WRITE_IENABLE (int src) {
    do {
        __builtin_wrctl (3, src);
    } while (0);
}

#endif
