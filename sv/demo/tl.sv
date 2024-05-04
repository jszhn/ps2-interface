module demo_top_level (
    input CLOCK_50,
    // peripherals
    input [3:0] KEY,
    input [9:0] SW,
    output [9:0] LEDR,
    output [6:0] HEX0,
    output [6:0] HEX1,
    output [6:0] HEX2,
    output [6:0] HEX3,
    output [6:0] HEX4,
    output [6:0] HEX5,
    // PS/2
    inout PS2_CLK,
    inout PS2_DAT,
    // VGA
    output [7:0] VGA_R,
    output [7:0] VGA_G,
    output [7:0] VGA_B,
    output VGA_CLK,
    output VGA_HS,
    output VGA_VS,
    output VGA_BLANK_N,
    output VGA_SYNC_N
);
    
endmodule

module hex_decoder (
    input [3:0] val,
    output reg [6:0] disp
);
    always @(*) begin
        case (val)
            4'h0: disp = 7'b1000000;
            4'h1: disp = 7'b1111001;
            4'h2: disp = 7'b0100100;
            4'h3: disp = 7'b0110000;
            4'h4: disp = 7'b0011001;
            4'h5: disp = 7'b0010010;
            4'h6: disp = 7'b0000010;
            4'h7: disp = 7'b1111000;
            4'h8: disp = 7'b0000000;
            4'h9: disp = 7'b0010000;
            4'ha: disp = 7'b0001000;
            4'hb: disp = 7'b0000011;
            4'hc: disp = 7'b1000110;
            4'hd: disp = 7'b0100001;
            4'he: disp = 7'b0000110;
            4'hf: disp = 7'b0001110;
            default: disp = 7'b1111111;
        endcase
    end
endmodule