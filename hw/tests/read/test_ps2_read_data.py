# cocotb imports
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, FallingEdge, Timer
import cocotb.handle as handle

async def generate_ps2_clk (dut):
    """
    Drives the PS/2 clock line. Has a 15 ns start-up time before oscillations begin.
    """
    clk = dut.ps2_clock
    clk.value = handle.Release()
    clk.value = 1 # start-up before oscillations
    await Timer (15, units="ns")

    for cycle in range(12):
        clk.value = 0
        await Timer (15, units="ns")
        clk.value = 1
        await Timer (15, units="ns")
    
    clk.value = handle.Freeze()