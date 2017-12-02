`timescale 1ns / 1ns

// HLS has generated this HDL code with the hlsyn executable
// Author: David Akre

module HLSM (Clk, Rst, Start, Done,   a, b, c,    z, x);
    input Clk, Rst, Start;
    output reg Done;
    reg clk_en;
    input [31:0] a, b, c;
     output reg [31:0] z, x;
      reg [31:0] d, e, f, g, h;
      reg dLTe, dEQe  ;
    localparam WAIT = 0, FINAL = 9999, STATE1 = 1, STATE2 = 2, STATE3 = 3, STATE4 = 4, STATE5 = 5, STATE6 = 6, STATE7 = 7, STATE8 = 8, STATE9 = 9;
    reg alu1, alu2, alu3, alu4, alu5, alu, alu, alu8, alu9;
    reg[9:0] state, next_state;


    // Creating HLSM datapath
    always @(clk_en, alu1, alu2, alu3, alu4, alu5, alu, alu, alu8, alu9) begin
        if (alu1) begin
             d <= a + b;
            next_state <= STATE2;
        end
        if (alu2) begin
             e <= a + c;
            next_state <= STATE3;
        end
        if (alu3) begin
             f <= a - b  ;
            next_state <= STATE4;
        end
        if (alu4) begin
             dEQe <= d == e;
            next_state <= STATE5;
        end
        if (alu5) begin
             dLTe <= d < e;
            next_state <= STATE6;
        end
        if (alu) begin
             g <= dLTe ? d : e ;
            next_state <= STATE7;
        end
        if (alu) begin
             h <= dEQe ? g : f ;
            next_state <= STATE8;
        end
        if (alu8) begin
             x <= g << dLTe;
            next_state <= STATE9;
        end
        if (alu9) begin
             z <= h >> dEQe;
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
             d  <= 0;
             e  <= 0;
             f  <= 0;
             dEQe  <= 0;
             dLTe  <= 0;
             g  <= 0;
             h  <= 0;
             x  <= 0;
             z  <= 0;
         dLTe<= 0;
             dEQe      <= 0;
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
                alu1 <= 1;
                alu2 <= 0;
                alu3 <= 0;
                alu4 <= 0;
                alu5 <= 0;
                alu <= 0;
                alu <= 0;
                alu8 <= 0;
                alu9 <= 0;
            end
            STATE2: begin
                alu1 <= 0;
                alu2 <= 1;
                alu3 <= 0;
                alu4 <= 0;
                alu5 <= 0;
                alu <= 0;
                alu <= 0;
                alu8 <= 0;
                alu9 <= 0;
            end
            STATE3: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 1;
                alu4 <= 0;
                alu5 <= 0;
                alu <= 0;
                alu <= 0;
                alu8 <= 0;
                alu9 <= 0;
            end
            STATE4: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu4 <= 1;
                alu5 <= 0;
                alu <= 0;
                alu <= 0;
                alu8 <= 0;
                alu9 <= 0;
            end
            STATE5: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu4 <= 0;
                alu5 <= 1;
                alu <= 0;
                alu <= 0;
                alu8 <= 0;
                alu9 <= 0;
            end
            STATE6: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu4 <= 0;
                alu5 <= 0;
                alu <= 1;
                alu <= 0;
                alu8 <= 0;
                alu9 <= 0;
            end
            STATE7: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu4 <= 0;
                alu5 <= 0;
                alu <= 0;
                alu <= 1;
                alu8 <= 0;
                alu9 <= 0;
            end
            STATE8: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu4 <= 0;
                alu5 <= 0;
                alu <= 0;
                alu <= 0;
                alu8 <= 1;
                alu9 <= 0;
            end
            STATE9: begin
                alu1 <= 0;
                alu2 <= 0;
                alu3 <= 0;
                alu4 <= 0;
                alu5 <= 0;
                alu <= 0;
                alu <= 0;
                alu8 <= 0;
                alu9 <= 1;
            end
        endcase
    end


endmodule
