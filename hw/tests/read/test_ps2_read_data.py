# cocotb imports
import cocotb
from cocotb.clock import Clock
import cocotb.simulator
from cocotb.triggers import Edge, RisingEdge, FallingEdge, Timer
import cocotb.handle as handle

packet_hex = [0x2E, 0x3B, 0xE0, 0xF0, 0x6C]  # 5, J, <spec>, <brk>, 6C
packet_values = [
    0b00111010011,
    0b01101110001,
    0b00000011101,
    0b00000111111,
    0b00011011011,
]


async def drive_de1_soc_clk(dut):
    """
    Drives DE1-SoC clk line. 20 ns period, 50 MHz freq
    """
    half = Timer(20, units="ns")
    while True:
        dut.clk.value = 1
        await half
        dut.clk.value = 0
        await half


async def drive_ps2(dut, num_packets, report_val: bool = False):
    """
    Drives both PS/2 clock and data lines
    """
    for i, packet in enumerate(packet_values):
        if i == num_packets:
            break

        dut.ps2_clock._log.info(f"Writing packet {hex(packet_hex[i])}")
        c = Clock(dut.ps2_clock, 90, "ns")
        await cocotb.start(c.start(cycles=11, start_high=False))
        ps2_period = Timer(90, units="ns")
        for i in range(10, -1, -1):  # iterate from MSB to LSB
            bit = (packet >> i) & 1
            dut.ps2_data.value = bit
            if report_val:
                dut.data._log.info(
                    f"Current packet value {dut.packet.value}, count value {dut.full_count.value}"
                )
            await ps2_period

        dut.ps2_clock.value = 1
        await Timer(180, units="ns")


@cocotb.test(timeout_time=10, timeout_unit="sec")
async def basic_read_test(dut):
    """
    Drives the PS2 clock line with a single data packet. Assumes correct packet input.
    Only checks for correct packet reading and ready flag setting.
    """
    # test initialisation
    await cocotb.start(drive_de1_soc_clk(dut))  # start clk
    dut.read_enable.value = 1
    dut.ps2_clock.value = 1

    # drive line
    await cocotb.start(drive_ps2(dut, 1, False))

    # wait for ready bit
    trigger = RisingEdge(dut.data_ready)
    await trigger

    # log and check values
    dut.data_ready._log.info(
        f"Ready bit asserted at time, {cocotb.simulator.get_sim_time()}"
    )
    dut.data._log.info(f"Final packet value {dut.packet.value}")
    dut.packet._log.info(f"Final data value {dut.data.value}")
    assert int(dut.data.value) == packet_hex[0] and int(dut.packet.value) == int(
        bin(packet_values[0])[2:].zfill(11)[::-1], 2
    )
    await Timer(100, "ns")


@cocotb.test(timeout_time=10, timeout_unit="sec")
async def read_test(dut):
    """
    Drives the PS2 clock line with a sequential list of data packets. Assumes correct packet inputs.
    Only checks for correct packet reading and ready flag setting.
    """
    # initialise packets

    # test initialisation
    await cocotb.start(drive_de1_soc_clk(dut))  # start clk
    dut.read_enable.value = 1
    dut.ps2_clock.value = 1

    # drive line
    await cocotb.start(drive_ps2(dut, len(packet_values), False))

    # wait for ready bit
    trigger = RisingEdge(dut.data_ready)
    for i, packet in enumerate(packet_hex):
        await trigger
        dut.data_ready._log.info(
            f"Ready bit asserted at time, {cocotb.simulator.get_sim_time()}"
        )
        dut.data._log.info(f"Final packet value {dut.packet.value}")
        dut.packet._log.info(f"Final data value {dut.data.value}")
        assert int(dut.data.value) == packet and int(dut.packet.value) == int(
            bin(packet_values[i])[2:].zfill(11)[::-1], 2
        )
    await Timer(100, "ns")


@cocotb.test(timeout_time=10, timeout_unit="sec")
async def valid_test(dut):
    """
    Checks for valid bit. Should be valid for every packet in this test
    """
    # test initialisation
    await cocotb.start(drive_de1_soc_clk(dut))  # start clk
    dut.read_enable.value = 1
    dut.ps2_clock.value = 1

    # drive line
    await cocotb.start(drive_ps2(dut, len(packet_values), False))

    # wait for ready bit
    trigger = RisingEdge(dut.data_ready)
    for _ in packet_hex:
        await trigger
        dut.data_ready._log.info(
            f"Ready bit asserted at time, {cocotb.simulator.get_sim_time()}"
        )
        dut.packet._log.info(
            f"Final packet value {dut.packet.value}, parity {dut.parity.value}"
        )
        assert bool(dut.data_valid.value) == True
    await Timer(100, "ns")


@cocotb.test(timeout_time=10, timeout_unit="sec")
async def invalid_test(dut):
    """
    Checks if valid flag remains de-asserted for an invalid PS/2 data packet.
    """
    # test initialisation
    await cocotb.start(drive_de1_soc_clk(dut))  # start clk
    dut.read_enable.value = 1
    dut.ps2_clock.value = 1

    packet_values[0], packet_values[1] = 0b01111010011, 0b00101110001

    # drive line
    await cocotb.start(drive_ps2(dut, 2, False))

    # wait for ready bit
    trigger = RisingEdge(dut.data_ready)
    for _ in range(2):
        await trigger
        dut.data_ready._log.info(
            f"Ready bit asserted at time, {cocotb.simulator.get_sim_time()}"
        )
        assert bool(dut.data_valid.value) == False
    await Timer(100, "ns")
