module ps2_read_data (
    input wire clk, // do i even need this?
    inout wire ps2_clock,
    inout wire ps2_data,
    output wire data_valid,
    output wire data_ready
);

    always @(posedge ps2_clock) begin
      
    end

endmodule