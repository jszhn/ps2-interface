module ps2_command (
    input clk,
    input reset,
    input read_enable,
    inout logic ps2_clock,
    inout logic ps2_data,
    input wire command_send,
    input wire [7:0] command
);
    // TODO: parameters for clock count (probably have to hardcode)

    always @(posedge clk) begin
        if (read_enable == 1'b0) begin // ensure that read enable is off before sending command
            ps2_data = command[0];
            ps2_clock = 1'b0;
        end
    end

endmodule