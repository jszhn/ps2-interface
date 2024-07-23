# PS/2 interface for the DE1-SoC
Software and hardware-based utilities and functions for the PS/2 protocol, built specifically for Terasic's DE1-SoC development platform.

The hardware platform is written in SystemVerilog and targets an Altera Cyclone V FPGA, with broad compatability for other FPGA platforms (i.e., the DE10, DE2). Other FPGA boards may require some minor changes, especially with respect to clock domains. Testbenches are written in cocotb, intended for the Intel Questa simulator.

The software interface is written in C, with support for Nios II-based interrupts. ARM or RISC-V processors are not supported.

Contributions are welcome, as always. This is an active work in progress!

## Credits
* Nios II control register access functions are derived and modified from Altera's documentation for the DE1-SoC.
* Graphics utilities in the demo are from this great [VGA API for the DE1-SoC](https://github.com/nbiancolin/DE1SOC-VideoApi) written by Nick Biancolin. Check it out!
