## ps2-de1-soc
PS/2 protocol interface utilities and functions. Built for Terasic's DE1-SoC development platform, with an Altera Cyclone V FPGA. May not work for other development platforms (i.e., DE10, DE2) though hardware interface may work with some minor changes. This repository includes:
* SystemVerilog hardware interface
* C embedded software interface with Nios II interrupt support

Contributions are welcome, as always. This is an active work in progress!

### Credits
* Nios II control register access functions are derived and modified from Altera's documentation for the DE1-SoC.
* Graphics utilities in the demo are from this great [VGA API for the DE1-SoC](https://github.com/nbiancolin/DE1SOC-VideoApi) written by Nick Biancolin. Check it out!
