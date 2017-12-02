`timescale 1ns / 1ns

// HLS has generated this HDL code with the hlsyn executable
// Author: David Akre

module HLSM (Clk, Rst, Start, Done);
    input Clk, Rst, Start;
    output reg Done;
    reg done, clk_en;
     reg [15:0] a, b, c;
      reg [7:0] z;
      reg [15:0] x;
      reg [7:0] d, e, f, g;
    localparam WAIT = 0, FINAL = 9999, STATE2 = 2, STATE3 = 3, STATE4 = 4, STATE1 = 1, STATE5 = 5;
    reg alu1, alu2, alu3, alu, mul5, alu6;
    reg[5:0] state, next_state;


    // Creating HLSM datapath
    always @(clk_en, done, alu1, alu2, alu3, alu, mul5, alu6) begin
        if (done) begin
            next_state <= FINAL;
        end
        if (alu1) begin
             d = a + b;
            next_state <= STATE2;
        end
        if (alu2) begin
             e = a + c;
            next_state <= STATE2;
        end
        if (alu3) begin
             g = d > e;
            next_state <= STATE3;
        end
        if (alu) begin
             z = g ? d : e;
            next_state <= STATE4;
        end
        if (mul5) begin
             f = a * c;
            next_state <= STATE1;
        end
        if (alu6) begin
             x = f - d  ;
            next_state <= STATE5;
        end

    end

    always @(posedge Clk) begin
        clk_en <= 1;
    end

    // Creating HLSM controller logic
    always @(posedge Start) begin
        if (Rst) begin
            state <= WAIT;
        end else begin
            state <= next_state;
        end
    end

    // C to HLSM states below based on FDS scheduling
    always @(state) begin
        case (state)
            WAIT: begin
                // Do nothing
            end
            FINAL: begin
                Done <= 1;
            end
            STATE2: begin
                alu1 <= 1;
                alu2 <= 1;
                alu3 <= 0;
                alu <= 0;
                mul5 <= 0;
                alu6 <= 0;
            end
            STATE2: begin
                alu1 <= 1;
                alu2 <= 1;
                alu3 <= 0;
                alu <= 0;
                mul5 <= 0;
                alu6 <= 0;
            end
            STATE3: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 1;
                alu <= 0;
                mul5 <= 0;
                alu6 <= 0;
            end
            STATE4: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu <= 1;
                mul5 <= 0;
                alu6 <= 0;
            end
            STATE1: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu <= 0;
                mul5 <= 1;
                alu6 <= 0;
            end
            STATE5: begin
                done <= 1;
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu <= 0;
                mul5 <= 0;
                alu6 <= 1;
            end
        endcase
    end


endmodule
