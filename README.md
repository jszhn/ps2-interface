## ps2-de1-soc
PS/2 protocol interface utilities and functions. Built for Terasic's DE1-SoC development platform, with an Altera Cyclone V FPGA. May not work for other development platforms (i.e., DE10, DE2). Verilog may work with some minor changes. This repository includes:
* SystemVerilog hardware interface
* C embedded software interface
* Nios II interrupt-based interface

Contributions are welcome, as always.

This is an active work in progress! The SV interface isn't finished, nor is the embedded C/Nios code.

### Credits
* Nios II control register access functions are derived and modified from Altera's documentation for the DE1-SoC.
* Graphics utilities in the demo are from this great [VGA API for the DE1-SoC](https://github.com/nbiancolin/DE1SOC-VideoApi) written by Nick Biancolin. Check it out!
