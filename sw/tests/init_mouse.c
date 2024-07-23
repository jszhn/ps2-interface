#include "../nios_asm.h"
#include "../nios_control_register_macros.h"

#include "../ps2.h"
#include "../ps2_nios.h"

int main (void) {
    ps2_init_mouse();
    ps2_enable_interrupts();
}

#include "../ps2.c"
#include "../ps2_nios.c"