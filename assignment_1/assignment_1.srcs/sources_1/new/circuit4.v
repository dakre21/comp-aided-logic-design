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
    
    reg Clk, Rst;
    
    output [31:0] final;
    
    wire [31:0] t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14;
    
    // Start clock for circuit
    always 
        #10 Clk <= ~Clk; 
    
    ADD #(32) add_1(a, b, t1); // t1 = a + b                                        
    ADD #(32) add_2(t1, c, t2); // t2 = t1 + c
    ADD #(32) add_3(t2, d, t3); // t3 = t2 + d
    ADD #(32) add_4(t3, e, t4); // t4 = t3 + e
    ADD #(32) add_5(t4, f, t5); // t5 = t4 + f
    ADD #(32) add_6(t5, g, t6); // t6 = t5 + g
    ADD #(32) add_7(t6, h, t7); // t7 = t6 + h
    ADD #(32) add_8(t7, i, t8); // t8 = t7 + i
    ADD #(32) add_9(t8, j, t9); // t9 = t8 + j
    ADD #(32) add_10(t9, l, t10); // t10 = t9 + l
    ADD #(32) add_11(t10, m, t11); // t11 = t10 + m
    ADD #(32) add_12(t11, n, t12); // t12 = t11 + n
    ADD #(32) add_13(t12, o, t13); // t13 = t12 + o
    ADD #(32) add_14(t13, p, t14); // t14 = t13 + p
    REG #(32) reg_1(t14, final, Clk, Rst); // final = t14

endmodule