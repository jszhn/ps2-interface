module ps2_controller (
    input wire clk, // CLOCK50
    input wire reset,
    inout wire ps2_clock, // PS2_CLK
    inout wire ps2_data, // PS2_DAT
    input wire command_send,
    input wire [7:0] command,
    output wire [7:0] data,
    output wire data_valid,
    output wire data_ready
);
    // output instantiation
    ps2_read_data din (
        .clk(clk),
        .ps2_clock(ps2_clock),
        .ps2_data(ps2_data),
        .data_valid(data_valid),
        .data_ready(data_ready)
    );

endmodule

/*
    Optional top-level wrapper for the PS/2 controller to better match standard data packet outputs.
*/
module ps2_mouse_controller (
    input wire clk, // CLOCK50
    input wire reset,
    inout wire ps2_clock, // PS2_CLK
    inout wire ps2_data, // PS2_DAT
    input wire command_send,
    input wire [7:0] command,
    output reg [7:0] byte1,
    output reg [7:0] byte2,
    output reg [7:0] byte3,
    output wire data_valid,
    output reg data_ready
);
    // local parameters
    typedef enum logic [1:0] {IDLE, BYTE1, BYTE2, BYTE3} state;
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
    always @(posedge data_ready) begin
        case (curr_state)
            IDLE: begin
                byte1 = data_out;
                curr_state = BYTE1;
            end
            BYTE1: begin
                byte2 = data_out;
                curr_state = BYTE2;
            end
            BYTE2: begin
                byte3 = data_out;
                curr_state = BYTE3;
            end
            BYTE3: begin
                curr_state = IDLE;
                valid_count = 0;
                data_ready = 0;
            end
            default: begin
                curr_state = IDLE;
                valid_count = 0;
                data_ready = 0;
            end
        endcase
    end

endmodule