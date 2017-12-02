`timescale 1ns / 1ns

// HLS has generated this HDL code with the hlsyn executable
// Author: David Akre

module HLSM (Clk, Rst, Start, Done);
    input Clk, Rst, Start;
    output reg Done;
     reg [31:0] a, b, c, d, e, f, g, h, sa;
      reg [31:0] avg;
      reg [31:0] t1, t2, t3, t4, t5, t6, t7, t7div2, t7div4;
    localparam WAIT = 0,STATE1 = 1, STATE7 = 7, STATE8 = 8, STATE9 = 9, STATE10 = 10, STATE5 = 5, STATE6 = 6, STATE11 = 11, STATE12 = 12, STATE13 = 13;
    reg alu1, alu2, alu3, alu4, alu5, alu6, alu7, alu8, alu9, alu10;
    reg[10:0] state, next_state;


    // Creating HLSM datapath
    always @(alu1, alu2, alu3, alu4, alu5, alu6, alu7, alu8, alu9, alu10) begin
        if (alu1) begin
             t1 = a + b;
            next_state <= STATE1;
        end
        if (alu2) begin
             t2 = t1 + c ;
            next_state <= STATE7;
        end
        if (alu3) begin
             t3 = t2 + d ;
            next_state <= STATE8;
        end
        if (alu4) begin
             t4 = t3 + e ;
            next_state <= STATE9;
        end
        if (alu5) begin
             t5 = t4 + f ;
            next_state <= STATE10;
        end
        if (alu6) begin
             t6 = t5 + g ;
            next_state <= STATE5;
        end
        if (alu7) begin
             t7 = t6 + h ;
            next_state <= STATE6;
        end
        if (alu8) begin
             t7div2 = t7 >> sa;
            next_state <= STATE11;
        end
        if (alu9) begin
             t7div4 = t7div2 >> sa ;
            next_state <= STATE12;
        end
        if (alu10) begin
             avg = t7div4 >> sa;
            next_state <= STATE13;
        end

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
            STATE1: begin
            end
            STATE5: begin
            end
            STATE6: begin
            end
            STATE7: begin
            end
            STATE8: begin
            end
            STATE9: begin
            end
            STATE10: begin
            end
            STATE11: begin
            end
            STATE12: begin
            end
            STATE13: begin
            end
        endcase
    end


endmodule
