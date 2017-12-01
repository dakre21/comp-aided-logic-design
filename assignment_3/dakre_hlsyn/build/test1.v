`timescale 1ns / 1ns

// HLS has generated this HDL code with the dpgen executable
// Author: David Akre

module HLSM (Clk, Rst, Start, Done);
    reg Clk, Rst, Start;
    output reg Done;
    reg LTZ_, GTZ_, EQZ_;

    input [31:0] a, b, c, d, e, f, g, h, sa;
     output [31:0] avg;
     reg [31:0] t1, t2, t3, t4, t5, t6, t7, t7div2, t7div4;


    always @(posedge Clk, ~Start) begin
    // Do nothing
    end

    always @(posedge Clk, a, b, c, t1, Start) begin
        t1 = a + b;
        t2 = t1 + c ;
    end

    always @(posedge Clk, e, t3, f, t4) begin
        t4 = t3 + e ;
        t5 = t4 + f ;
    end

    always @(posedge Clk, g, t5) begin
        t6 = t5 + g ;
    end

    always @(posedge Clk, d, t2) begin
        t3 = t2 + d ;
    end

    always @(posedge Clk, h, t6) begin
        t7 = t6 + h ;
    end

    always @(posedge Clk, a, sa) begin
        t7div2 = t7 >> sa;
    end

    always @(posedge Clk, a, sa, t7div2) begin
        t7div4 = t7div2 >> sa ;
    end

    always @(posedge Clk, d, sa, t7, t7div4) begin
        avg = t7div4 >> sa;
    end

    always @(posedge Clk,  t) begin
        Done = 1;
    end



endmodule
