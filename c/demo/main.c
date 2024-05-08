#include "nios_control_register_macros.h"
#include "ps2.h"
#include "ps2_nios.h"

/*
 * If we're working on CPUlator, we can concatenate into a single file with
 *      gcc -save-temps -CC -Wall -S demo/main.c
 * Make sure the definition below isn't commented out
 * Use main.i in CPUlator
 */
// #define CPULATOR

int main (int argc, char **argv) {

}

#ifdef CPULATOR

#include "ps2.c"
#include "ps2_nios.c"

#endif