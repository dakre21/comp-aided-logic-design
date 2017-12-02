`timescale 1ns / 1ns

// HLS has generated this HDL code with the hlsyn executable
// Author: David Akre

module HLSM (Clk, Rst, Start, Done,   x0, x1, x2, x3, y0, c0, five, ten,    d1, d2, e, f, g, h);
    input Clk, Rst, Start;
    output reg Done;
    reg clk_en;
    input [31:0] x0, x1, x2, x3, y0, c0, five, ten;
     output reg [31:0] d1, d2, e, f, g, h;
      reg [31:0] t1, t2, t3, vd1, ve, vf, vg;
    localparam WAIT = 0, FINAL = 9999, STATE2 = 2, STATE1 = 1, STATE3 = 3, STATE4 = 4, STATE5 = 5, STATE6 = 6, STATE7 = 7;
    reg alu1, mul2, mul3, mul4, alu5, alu6, mul7, mul8, mul9, mul10, alu11, alu12, alu13;
    reg[7:0] state, next_state;


    // Creating HLSM datapath
    always @(clk_en, alu1, mul2, mul3, mul4, alu5, alu6, mul7, mul8, mul9, mul10, alu11, alu12, alu13) begin
        if (alu1) begin
             t1 <= x0 + x1;
            next_state <= STATE3;
        end
        if (mul2) begin
             d1 <= t1 * c0;
            next_state <= STATE2;
        end
        if (mul3) begin
             vd1 <= t1 * c0;
            next_state <= STATE4;
        end
        if (mul4) begin
             d2 <= vd1 * five;
            next_state <= STATE5;
        end
        if (alu5) begin
             t2 <= x1 + x2;
            next_state <= STATE3;
        end
        if (alu6) begin
             t3 <= x3 + c0;
            next_state <= STATE4;
        end
        if (mul7) begin
             e <= t2 * t3;
            next_state <= STATE3;
        end
        if (mul8) begin
             ve <= t2 * t3;
            next_state <= STATE6;
        end
        if (mul9) begin
             f <= ve * y0;
            next_state <= STATE7;
        end
        if (mul10) begin
             vf <= ve * y0;
            next_state <= FINAL;
        end
        if (alu11) begin
             g <= x0 - ten;
            next_state <= STATE5;
        end
        if (alu12) begin
             vg <= x0 - ten;
            next_state <= STATE6;
        end
        if (alu13) begin
             h <= vf + vg;
            next_state <= STATE7;
        end

    end

    always @(posedge Clk) begin
        clk_en <= 1;
    end

    // Creating HLSM controller logic
    always @(posedge Start) begin
        if (Rst) begin
            state <= WAIT;
             t1  <= 0;
             d1  <= 0;
             vd1  <= 0;
             d2  <= 0;
             t2  <= 0;
             t3  <= 0;
             e  <= 0;
             ve  <= 0;
             f  <= 0;
             vf  <= 0;
             g  <= 0;
             vg  <= 0;
             h  <= 0;
         t1<= 0;
             t2<= 0;
             t3<= 0;
             vd1<= 0;
             ve<= 0;
             vf<= 0;
             vg    <= 0;
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
            STATE2: begin
                alu1 <= 1;
                mul2 <= 0;
                mul3 <= 0;
                mul4 <= 0;
                alu5 <= 1;
                alu6 <= 0;
                mul7 <= 1;
                mul8 <= 0;
                mul9 <= 0;
                mul10 <= 0;
                alu11 <= 0;
                alu12 <= 0;
                alu13 <= 0;
            end
            STATE1: begin
                alu1 <= 0;
                mul2 <= 1;
                mul3 <= 0;
                mul4 <= 0;
                alu5 <= 0;
                alu6 <= 0;
                mul7 <= 0;
                mul8 <= 0;
                mul9 <= 0;
                mul10 <= 0;
                alu11 <= 0;
                alu12 <= 0;
                alu13 <= 0;
            end
            STATE3: begin
                alu1 <= 0;
                mul2 <= 0;
                mul3 <= 1;
                mul4 <= 0;
                alu5 <= 0;
                alu6 <= 1;
                mul7 <= 0;
                mul8 <= 0;
                mul9 <= 0;
                mul10 <= 0;
                alu11 <= 0;
                alu12 <= 0;
                alu13 <= 0;
            end
            STATE4: begin
                alu1 <= 0;
                mul2 <= 0;
                mul3 <= 0;
                mul4 <= 1;
                alu5 <= 0;
                alu6 <= 0;
                mul7 <= 0;
                mul8 <= 0;
                mul9 <= 0;
                mul10 <= 0;
                alu11 <= 1;
                alu12 <= 0;
                alu13 <= 0;
            end
            STATE2: begin
                alu1 <= 1;
                mul2 <= 0;
                mul3 <= 0;
                mul4 <= 0;
                alu5 <= 1;
                alu6 <= 0;
                mul7 <= 1;
                mul8 <= 0;
                mul9 <= 0;
                mul10 <= 0;
                alu11 <= 0;
                alu12 <= 0;
                alu13 <= 0;
            end
            STATE3: begin
                alu1 <= 0;
                mul2 <= 0;
                mul3 <= 1;
                mul4 <= 0;
                alu5 <= 0;
                alu6 <= 1;
                mul7 <= 0;
                mul8 <= 0;
                mul9 <= 0;
                mul10 <= 0;
                alu11 <= 0;
                alu12 <= 0;
                alu13 <= 0;
            end
            STATE2: begin
                alu1 <= 1;
                mul2 <= 0;
                mul3 <= 0;
                mul4 <= 0;
                alu5 <= 1;
                alu6 <= 0;
                mul7 <= 1;
                mul8 <= 0;
                mul9 <= 0;
                mul10 <= 0;
                alu11 <= 0;
                alu12 <= 0;
                alu13 <= 0;
            end
            STATE5: begin
                alu1 <= 0;
                mul2 <= 0;
                mul3 <= 0;
                mul4 <= 0;
                alu5 <= 0;
                alu6 <= 0;
                mul7 <= 0;
                mul8 <= 1;
                mul9 <= 0;
                mul10 <= 0;
                alu11 <= 0;
                alu12 <= 1;
                alu13 <= 0;
            end
            STATE6: begin
                alu1 <= 0;
                mul2 <= 0;
                mul3 <= 0;
                mul4 <= 0;
                alu5 <= 0;
                alu6 <= 0;
                mul7 <= 0;
                mul8 <= 0;
                mul9 <= 1;
                mul10 <= 0;
                alu11 <= 0;
                alu12 <= 0;
                alu13 <= 1;
            end
            STATE7: begin
                alu1 <= 0;
                mul2 <= 0;
                mul3 <= 0;
                mul4 <= 0;
                alu5 <= 0;
                alu6 <= 0;
                mul7 <= 0;
                mul8 <= 0;
                mul9 <= 0;
                mul10 <= 1;
                alu11 <= 0;
                alu12 <= 0;
                alu13 <= 0;
            end
            STATE4: begin
                alu1 <= 0;
                mul2 <= 0;
                mul3 <= 0;
                mul4 <= 1;
                alu5 <= 0;
                alu6 <= 0;
                mul7 <= 0;
                mul8 <= 0;
                mul9 <= 0;
                mul10 <= 0;
                alu11 <= 1;
                alu12 <= 0;
                alu13 <= 0;
            end
            STATE5: begin
                alu1 <= 0;
                mul2 <= 0;
                mul3 <= 0;
                mul4 <= 0;
                alu5 <= 0;
                alu6 <= 0;
                mul7 <= 0;
                mul8 <= 1;
                mul9 <= 0;
                mul10 <= 0;
                alu11 <= 0;
                alu12 <= 1;
                alu13 <= 0;
            end
            STATE6: begin
                alu1 <= 0;
                mul2 <= 0;
                mul3 <= 0;
                mul4 <= 0;
                alu5 <= 0;
                alu6 <= 0;
                mul7 <= 0;
                mul8 <= 0;
                mul9 <= 1;
                mul10 <= 0;
                alu11 <= 0;
                alu12 <= 0;
                alu13 <= 1;
            end
        endcase
    end


endmodule
