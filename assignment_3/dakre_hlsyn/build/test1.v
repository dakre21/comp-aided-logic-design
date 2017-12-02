`timescale 1ns / 1ns

// HLS has generated this HDL code with the hlsyn executable
// Author: David Akre

module HLSM (Clk, Rst, Start, Done,   a, b, c,    z, x);
    input Clk, Rst, Start;
    output reg Done;
    reg clk_en;
    input [31:0] a, b, c;
     output reg [31:0] z, x;
      reg [31:0] d, f, g, zrin;
    localparam WAIT = 0, FINAL = 9999, STATE2 = 2, STATE0 = 0, STATE1 = 1, STATE4 = 4, STATE3 = 3;
    reg alu1, alu2, alu3, alu4, alu5, mul6, alu7, alu8;
    reg[5:0] state, next_state;


    // Creating HLSM datapath
    always @(clk_en, alu1, alu2, alu3, alu4, alu5, mul6, alu7, alu8) begin
        if (alu1) begin
             d = a + b;
            next_state <= STATE3;
        end
        if (alu2) begin
             g = a < b;
            next_state <= STATE1;
        end
        if (alu3) begin
             zrin = a + c;
            next_state <= STATE3;
        end
        if (alu4) begin
             g = a < b;
            next_state <= STATE2;
        end
        if (alu5) begin
             zrin = a + c;
            next_state <= STATE3;
        end
        if (mul6) begin
             f = a * c;
            next_state <= STATE2;
        end
        if (alu7) begin
             x = f - d  ;
            next_state <= FINAL;
        end
        if (alu8) begin
             z = zrin + f;
            next_state <= STATE4;
        end

    end

    always @(posedge Clk) begin
        clk_en <= 1;
    end

    // Creating HLSM controller logic
    always @(posedge Start) begin
        if (Rst) begin
            state <= WAIT;
             d  <= 0;
             g  <= 0;
             zrin  <= 0;
             g  <= 0;
             zrin  <= 0;
             f  <= 0;
             x  <= 0;
             z  <= 0;
              d<= 0;
             f<= 0;
             g<= 0;
             zrin    <= 0;
            Done <= 0;
            clk_en <= 0;
        end else begin
            next_state <= STATE0;
            state <= next_state;
        end
    end

    // C to HLSM states below based on FDS scheduling
    always @(state) begin
        case (state)
            WAIT: begin
                Done <= 0;
            end
            FINAL: begin
                Done <= 1;
                next_state <= WAIT;
            end
            STATE2: begin
                alu1 <= 1;
                alu2 <= 0;
                alu3 <= 1;
                alu4 <= 0;
                alu5 <= 1;
                mul6 <= 0;
                alu7 <= 0;
                alu8 <= 0;
            end
            STATE2: begin
                alu1 <= 1;
                alu2 <= 0;
                alu3 <= 1;
                alu4 <= 0;
                alu5 <= 1;
                mul6 <= 0;
                alu7 <= 0;
                alu8 <= 0;
            end
            STATE1: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu4 <= 1;
                alu5 <= 0;
                mul6 <= 1;
                alu7 <= 0;
                alu8 <= 0;
            end
            STATE2: begin
                alu1 <= 1;
                alu2 <= 0;
                alu3 <= 1;
                alu4 <= 0;
                alu5 <= 1;
                mul6 <= 0;
                alu7 <= 0;
                alu8 <= 0;
            end
            STATE1: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu4 <= 1;
                alu5 <= 0;
                mul6 <= 1;
                alu7 <= 0;
                alu8 <= 0;
            end
            STATE4: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu4 <= 0;
                alu5 <= 0;
                mul6 <= 0;
                alu7 <= 1;
                alu8 <= 0;
            end
            STATE3: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu4 <= 0;
                alu5 <= 0;
                mul6 <= 0;
                alu7 <= 0;
                alu8 <= 1;
            end
        endcase
    end


endmodule
