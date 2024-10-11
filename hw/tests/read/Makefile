# defaults
SIM ?= questa
TOPLEVEL_LANG ?= verilog
HDL_TIMEPRECISION = ns
HDL_TIMEUNIT = 10

# test-specific variables
VERILOG_SOURCES += $(PWD)/../../src/ps2_read.sv
TOPLEVEL = ps2_read_data
MODULE = test_ps2_read_data

include $(shell cocotb-config --makefiles)/Makefile.sim
