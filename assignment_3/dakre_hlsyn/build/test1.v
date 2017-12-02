`timescale 1ns / 1ns

// HLS has generated this HDL code with the hlsyn executable
// Author: David Akre

module HLSM (Clk, Rst, Start, Done);
    input Clk, Rst, Start;
    output reg Done;
    reg done, clk_en;
     reg [7:0] a, b, c, d, e, f, g, h, num;
      reg [7:0] avg;
      reg [31:0] t1, t2, t3, t4, t5, t6, t7;
    localparam WAIT = 0, FINAL = 9999, STATE1 = 1, STATE5 = 5, STATE6 = 6, STATE3 = 3, STATE4 = 4, STATE7 = 7, STATE8 = 8;
    reg alu1, alu2, alu3, alu4, alu5, alu6, alu7, div8;
    reg[7:0] state, next_state;


    // Creating HLSM datapath
    always @(clk_en, done, alu1, alu2, alu3, alu4, alu5, alu6, alu7, div8) begin
        if (done) begin
            next_state <= FINAL;
        end
        if (alu1) begin
             t1 = a + b;
            next_state <= STATE1;
        end
        if (alu2) begin
             t2 = t1 + c ;
            next_state <= STATE5;
        end
        if (alu3) begin
             t3 = t2 + d ;
            next_state <= STATE6;
        end
        if (alu4) begin
             t4 = t3 + e ;
            next_state <= STATE3;
        end
        if (alu5) begin
             t5 = t4 + f ;
            next_state <= STATE4;
        end
        if (alu6) begin
             t6 = t5 + g ;
            next_state <= STATE7;
        end
        if (alu7) begin
             t7 = t6 + h ;
            next_state <= STATE8;
        end
        if (div8) begin
             avg = t7 / num;
            next_state <= STATE8;
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
            STATE1: begin
                alu1 <= 1;
                alu2 <= 0;
                alu3 <= 0;
                alu4 <= 0;
                alu5 <= 0;
                alu6 <= 0;
                alu7 <= 0;
                div8 <= 0;
            end
            STATE5: begin
                alu1 <= 0;
                alu2 <= 1;
                alu3 <= 0;
                alu4 <= 0;
                alu5 <= 0;
                alu6 <= 0;
                alu7 <= 0;
                div8 <= 0;
            end
            STATE6: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 1;
                alu4 <= 0;
                alu5 <= 0;
                alu6 <= 0;
                alu7 <= 0;
                div8 <= 0;
            end
            STATE3: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu4 <= 1;
                alu5 <= 0;
                alu6 <= 0;
                alu7 <= 0;
                div8 <= 0;
            end
            STATE4: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu4 <= 0;
                alu5 <= 1;
                alu6 <= 0;
                alu7 <= 0;
                div8 <= 0;
            end
            STATE7: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu4 <= 0;
                alu5 <= 0;
                alu6 <= 1;
                alu7 <= 0;
                div8 <= 0;
            end
            STATE8: begin
                done <= 1;
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu4 <= 0;
                alu5 <= 0;
                alu6 <= 0;
                alu7 <= 1;
                div8 <= 1;
            end
            STATE8: begin
                done <= 1;
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu4 <= 0;
                alu5 <= 0;
                alu6 <= 0;
                alu7 <= 1;
                div8 <= 1;
            end
        endcase
    end


endmodule
