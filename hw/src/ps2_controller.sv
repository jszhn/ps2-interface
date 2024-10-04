module ps2_controller (
    input wire clk,  // CLOCK50
    input wire reset,
    inout wire ps2_clock,  // PS2_CLK
    inout wire ps2_data,  // PS2_DAT
    input wire command_send,
    input wire [7:0] command,
    output wire [7:0] data,
    output wire data_valid,
    output wire data_ready
);
  // data output instantiation
  ps2_read_data din (
      .clk(clk),
      .ps2_clock(ps2_clock),
      .ps2_data(ps2_data),
      .data(data),
      .data_valid(data_valid),
      .data_ready(data_ready)
  );

  // command input instantiation
  ps2_command cmd (
      .ps2_clock(ps2_clock),
      .ps2_data(ps2_data),
      .command_send(command_send),
      .command(command),
  );

endmodule

/*
    Optional top-level wrapper for the PS/2 controller to better match standard 3-packet outputs.
*/
module ps2_mouse_controller (
    input wire clk,  // CLOCK50
    input wire reset,
    inout wire ps2_clock,  // PS2_CLK
    inout wire ps2_data,  // PS2_DAT
    input wire command_send,
    input wire [7:0] command,
    output reg [7:0] byte1,
    output reg [7:0] byte2,
    output reg [7:0] byte3,
    output wire data_valid,
    output reg data_ready
);
  // local FSM parameters
  typedef enum logic [1:0] {
    IDLE,
    BYTE1,
    BYTE2,
    BYTE3
  } state;
  logic [1:0] curr_state;
  reg [1:0] valid_count;

  // controller instantiation
  wire [7:0] data_out;
  wire controller_data_ready;
  ps2_controller cont (
      .clk(clk),
      .reset(reset),
      .ps2_clock(ps2_clock),
      .ps2_data(ps2_data),
      .command_send(command_send),
      .command(command),
      .data(data_out),
      .data_valid(data_valid),
      .data_ready(controller_data_ready)
  );

  // finite state machine to read each byte packet
  always @(posedge controller_data_ready) begin
    case (curr_state)
      IDLE: begin  // read first byte
        byte1 = data_out;
        curr_state = BYTE1;
        if (data_valid) valid_count++;
      end
      BYTE1: begin  // read second byte
        byte2 = data_out;
        curr_state = BYTE2;
        if (data_valid) valid_count++;
      end
      BYTE2: begin  // read third byte
        byte3 = data_out;
        if (data_valid) valid_count++;

        if (valid_count == 3) data_ready = 1;
        else data_ready = 0;

        curr_state = IDLE;  // back to idle after this
      end
      default: begin
        curr_state  = IDLE;
        valid_count = 0;
        data_ready  = 0;
      end
    endcase
  end

  // flip data ready bit for one clock cycle
  always @(posedge clk) begin
    if (data_ready) begin
      if (valid_count == 3) valid_count = 0;
      else if (valid_count == 0) begin
        data_ready = ~data_ready;
      end
    end
  end

endmodule
