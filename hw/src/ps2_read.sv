module ps2_read_data (
    input wire clk,
    inout wire ps2_clock,
    inout wire ps2_data,
    input wire read_enable,
    output logic [7:0] data,
    output logic data_valid,
    output logic data_ready
);
  // constants
  localparam int START_VAL = 4'h0;
  localparam int END_VAL = 4'hb;

  // local registers
  reg [3:0] full_count = START_VAL;  // 0-11 for full packet sent
  reg parity = 1'b0;
  reg [10:0] packet = 10'b0;

  // read from data line
  always @(negedge ps2_clock) begin
    if (read_enable) begin  // to avoid conflict with sending commands
      if (full_count == START_VAL) packet = 0;

      packet[full_count] = ps2_data;
      full_count = full_count + 1;  // to prepare for next bit
    end
  end

  // set output values
  always @(posedge clk) begin
    if (read_enable) begin
      if (full_count == END_VAL) begin  // if we've read 11 bits, set ready bit for 1 FPGA clock cycle
        if (!data_ready) begin
          data <= packet[8:1];  // removes START_VAL and end bits
          data_ready <= 1;

          parity = ^packet[8:1];  // checks for odd parity
          data_valid = (packet[0] == ~packet[10]) & (parity == ~packet[9]);  // error checking
        end else begin  // reset variables
          data_ready <= 0;
          data_valid <= 0;
          parity <= 1'b0;
          full_count <= START_VAL;
        end
      end else begin
        data_ready <= 0;
        data_valid <= 0;
      end
    end
  end
endmodule
