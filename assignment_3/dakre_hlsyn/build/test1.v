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


