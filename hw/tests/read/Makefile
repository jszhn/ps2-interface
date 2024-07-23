# defaults
SIM ?= modelsim
TOPLEVEL_LANG ?= verilog

VERILOG_SOURCES += $(PWD)/../../ps2_read.sv

TOPLEVEL = ps2_read_data
MODULE = test_ps2_read_data

# include cocotb's make rules to take care of the simulator setup
include $(shell cocotb-config --makefiles)/Makefile.sim