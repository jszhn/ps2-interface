module ps2_read_data (
    input wire clk,
    inout wire ps2_clock,
    inout wire ps2_data,
    input wire read_enable,
    output logic [7:0] data,
    output logic data_valid,
    output logic data_ready
);
    // local registers
    reg [3:0] full_count; // 0-11 for full packet sent
    reg parity = 1'b0;
    reg [10:0] packet;

    // read from data line
    always @(negedge ps2_clock) begin
        if (read_enable == 1'b1) begin // ensures that this doesn't conflict with sending commands
            if (full_count == 4'hb) packet = 0;
            packet[full_count] = ps2_data;
            full_count--; // to prepare for next bit
        end
    end

    // set output values
    always @(posedge clk) begin
        if (full_count == 4'h0) begin // if we've read 11 bits, set valid bit for 1 clock cycle
            if (data_ready == 0) begin
                data <= packet[8:1]; // removes start and end bits
                data_ready <= 1;

                for (int i = 1; i < 9; i++) parity ^= packet[i]; // checks for odd parity
                data_valid <= (packet[0] == ~packet[10]) & parity; // error checking
            end
            else begin // reset variables
                data_ready <= 0;
                data_valid <= 0;
                parity <= 1'b0;
                count <= 4'hb;
            end
        end
    end
endmodule