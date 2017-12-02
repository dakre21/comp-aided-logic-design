`timescale 1ns / 1ns

// HLS has generated this HDL code with the hlsyn executable
// Author: David Akre

module HLSM (Clk, Rst, Start, Done,   a, b, c, d, e, f, g,    k, l);
    input Clk, Rst, Start;
    output reg Done;
    reg clk_en;
    input [15:0] a, b, c, d, e, f, g;
      reg [15:0] h, i, j;
     output reg [15:0] k, l;
    localparam WAIT = 0, FINAL = 9999, STATE1 = 1, STATE2 = 2, STATE3 = 3, STATE7 = 7;
    reg mul1, mul2, alu3, div4, div5;
    reg[4:0] state, next_state;


    // Creating HLSM datapath
    always @(clk_en, mul1, mul2, alu3, div4, div5) begin
        if (mul1) begin
             h <= a * b;
            next_state <= STATE2;
        end
        if (mul2) begin
             i <= c * d;
            next_state <= STATE3;
        end
        if (alu3) begin
             j <= h + i;
            next_state <= STATE2;
        end
        if (div4) begin
             k <= j / e;
            next_state <= STATE7;
        end
        if (div5) begin
             l <= f / g;
            next_state <= FINAL;
        end

    end

    always @(posedge Clk) begin
        clk_en <= 1;
    end

    // Creating HLSM controller logic
    always @(posedge Start) begin
        if (Rst) begin
            state <= WAIT;
             h  <= 0;
             i  <= 0;
             j  <= 0;
             k  <= 0;
             l  <= 0;
         h<= 0;
             i<= 0;
             j    <= 0;
            Done <= 0;
            clk_en <= 0;
        end else begin
            next_state <= STATE1;
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
            STATE1: begin
                mul1 <= 1;
                mul2 <= 0;
                alu3 <= 1;
                div4 <= 0;
                div5 <= 0;
            end
            STATE2: begin
                mul1 <= 0;
                mul2 <= 1;
                alu3 <= 0;
                div4 <= 0;
                div5 <= 0;
            end
            STATE1: begin
                mul1 <= 1;
                mul2 <= 0;
                alu3 <= 1;
                div4 <= 0;
                div5 <= 0;
            end
            STATE3: begin
                mul1 <= 0;
                mul2 <= 0;
                alu3 <= 0;
                div4 <= 1;
                div5 <= 0;
            end
            STATE7: begin
                mul1 <= 0;
                mul2 <= 0;
                alu3 <= 0;
                div4 <= 0;
                div5 <= 1;
            end
        endcase
    end


endmodule
