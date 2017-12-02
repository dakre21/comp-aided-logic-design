`timescale 1ns / 1ns

// HLS has generated this HDL code with the hlsyn executable
// Author: David Akre

module HLSM (Clk, Rst, Start, Done,   a, b, c, d, zero,    z);
    input Clk, Rst, Start;
    output reg Done;
    reg clk_en;
    input [63:0] a, b, c, d, zero;
     output reg [63:0] z;
      reg [63:0] e, f, g;
      reg gEQz  ;
    localparam WAIT = 0, FINAL = 9999, STATE1 = 1, STATE3 = 3, STATE7 = 7, STATE2 = 2;
    reg div1, div2, div3, alu4, alu;
    reg[4:0] state, next_state;


    // Creating HLSM datapath
    always @(clk_en, div1, div2, div3, alu4, alu) begin
        if (div1) begin
             e <= a / b;
            next_state <= STATE2;
        end
        if (div2) begin
             f <= c / d;
            next_state <= STATE7;
        end
        if (div3) begin
             g <= a % b  ;
            next_state <= FINAL;
        end
        if (alu4) begin
             gEQz <= g == zero;
            next_state <= STATE2;
        end
        if (alu) begin
             z <= gEQz ? e : f ;
            next_state <= STATE3;
        end

    end

    always @(posedge Clk) begin
        clk_en <= 1;
    end

    // Creating HLSM controller logic
    always @(posedge Start) begin
        if (Rst) begin
            state <= WAIT;
             e  <= 0;
             f  <= 0;
             g  <= 0;
             gEQz  <= 0;
             z  <= 0;
         gEQz      <= 0;
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
                div1 <= 1;
                div2 <= 0;
                div3 <= 0;
                alu4 <= 1;
                alu <= 0;
            end
            STATE3: begin
                div1 <= 0;
                div2 <= 1;
                div3 <= 0;
                alu4 <= 0;
                alu <= 0;
            end
            STATE7: begin
                div1 <= 0;
                div2 <= 0;
                div3 <= 1;
                alu4 <= 0;
                alu <= 0;
            end
            STATE1: begin
                div1 <= 1;
                div2 <= 0;
                div3 <= 0;
                alu4 <= 1;
                alu <= 0;
            end
            STATE2: begin
                div1 <= 0;
                div2 <= 0;
                div3 <= 0;
                alu4 <= 0;
                alu <= 1;
            end
        endcase
    end


endmodule
