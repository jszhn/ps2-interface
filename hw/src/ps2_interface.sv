module ps2_interface #(parameter MOUSE_EN = 0) (
    input wire CLOCK_50,
    input wire reset,
    inout PS2_CLK,
    inout PS2_DAT,
    output wire [7:0] data_out,
    output logic [2:0] packet_number,
    output wire [2:0] key_pressed
);
   // conditional module instantiation
    generate
        if (MOUSE_EN == 1) begin // mouse decoder
            wire [7:0] command;
            wire data_valid;
            wire data_ready;
            wire [7:0] byte1;
            wire [7:0] byte2;
            wire [7:0] byte3;

            logic is_mouse_enabled = 0;
            typedef enum logic {
                ENUM1,
                ENUM2
            } mouse_setup_state;

            ps2_mouse_controller mouse (
                .clk(CLOCK_50),
                .reset(reset),
                .ps2_clock(PS2_CLK),
                .ps2_data(PS2_DAT),
                .command_send(command_send),
                .command(command),
                .data_valid(data_valid),
                .data_ready(data_ready),
                .byte1(byte1),
                .byte2(byte2),
                .byte3(byte3)
            );

            // mouse setup
            always @(posedge PS2_CLK) begin
                if (is_mouse_enabled == 0) begin

                end
            end
        end
        else begin // keyboard decoder
            ps2_keyboard dc (
                .clk(CLOCK_50),
                .reset(reset),
                .data(data),
                .data_valid(data_valid),
                .data_ready(data_ready),
                .data_out(data_out),
                .key_pressed(key_pressed[0])
            );

            ps2_controller kb (
              .clk(CLOCK_50),
              .reset(reset),
              .ps2_clock(PS2_CLK),
              .ps2_data(PS2_DAT),
              .command_send(command_send),
              .command(command),
              .data(data),
              .data_valid(data_valid),
              .data_ready(data_ready)
            );
        end
    endgenerate

    always_comb begin
        if (~MOUSE_EN) packet_number = 3'b000;
    end
endmodule

module ps2_keyboard ( // todo import
    input clk, // CLOCK_50
    input reset,
    input [7:0] data,
    input data_valid,
    input data_ready,
    output logic [7:0] data_out,
    output logic key_pressed
);
    localparam BREAK = 8'hF0;
    reg [7:0] previous_byte;

    always @(posedge clk) begin
        if (reset) begin
            data_out <= 'b0;
            previous_byte <= 'b0;
            key_pressed <= 0;
        end
        else begin
            if (data == BREAK | ~data_valid) begin
                data_out <= 'b0;
                key_pressed <= 'b0;
            end
            else if (data_ready & data != previous_byte) begin // prevents re-outputting unpressed key
                previous_byte <= data;
                key_pressed <= 1;
            end

            if (key_pressed) begin
                if (previous_byte == 0) data_out <= 'b0;
                else data_out <= data;
            end
        end
    end
endmodule