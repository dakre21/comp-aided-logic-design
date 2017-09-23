`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: circuit4 module
// Module Name: circuit4
// Project Name: Assignment 4
// Target Devices: Artix 7
// Tool Versions: 
// Description: Circuit 4
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module circuit4(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, final);

    // Declare inputs and outputs
    input [7:0] a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;
    
    output reg [31:0] final;
    
    wire [31:0] t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14;
    
    /*
    t1 = a + b
    t2 = t1 + c
    t3 = t2 + d
    t4 = t3 + e
    t5 = t4 + f
    t6 = t5 + g
    t7 = t6 + h
    t8 = t7 + i
    t9 = t8 + j
    ** No k?
    t10 = t9 + l
    t11 = t10 + m
    t12 = t11 + n
    t13 = t12 + 0
    t14 = t13 + p
    final = t14
    */

endmodule