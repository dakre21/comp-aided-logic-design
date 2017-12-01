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


    always @(Clk, ~Start) begin
    // Do nothing
    end

    always @(Clk, Start) begin
        t1 = a + b;
        t2 = t1 + c ;
    end

    always @(Clk,        t3 = t2 + d ;
    end

    always @(Clk,        t4 = t3 + e ;
    end

    always @(Clk,        t5 = t4 + f ;
    end

    always @(Clk,        t6 = t5 + g ;
    end

    always @(Clk,        t7 = t6 + h ;
    end

    always @(Clk,        t7div2 = t7 >> sa;
    end

    always @(Clk,        t7div4 = t7div2 >> sa ;
    end

    always @(Clk,        avg = t7div4 >> sa;
    end

    always @(Clk,    end

