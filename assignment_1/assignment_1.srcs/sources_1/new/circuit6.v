`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: circuit6 module
// Module Name: circuit6
// Project Name: Assignment 1
// Target Devices: Artix 7
// Tool Versions: 
// Description: Circuit 6
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module circuit6(a, b, c, d, e, f, g, h, num, avg);

    // Declare inputs and outputs
    input [15:0] a, b, c, d, e, f, g, h, num;
    
    output [15:0] avg;
    
    reg Clk, Rst;
    
    wire [15:0] r1, r2, r3, r4, r5, r6, r7; // NOTE: Setting these as wires to be hooked up to the output port connection to the REG module
    
    wire [15:0] avgwire;
    wire [31:0] t1, t2, t3, t4, t5, t6, t7;
    
    // Start clock for circuit
    always 
        #10 Clk <= ~Clk; 
    
    ADD #(32) add_1(a, b, t1); // t1 = a + b
    REG #(32) reg_1(t1, r1, Clk, Rst); // r1 = t1
    ADD #(32) add_2(r1, c, t2); // t2 = r1 + c
    REG #(32) reg_2(t2, r2, Clk, Rst); // r2 = t2
    ADD #(32) add_3(r2, d, t3); // t3 = r2 + d
    REG #(32) reg_3(t3, r3, Clk, Rst); // r3 = t3
    ADD #(32) add_4(r3, e, t4); // t4 = r3 + e
    REG #(32) reg_4(t4, r4, Clk, Rst); // r4 = t4
    ADD #(32) add_5(r4, f, t5); // t5 = r4 + f
    REG #(32) reg_5(t5, r5, Clk, Rst); // r5 = t5
    ADD #(32) add_6(r5, g, t6); // t6 = r5 + g
    REG #(32) reg_6(t6, r6, Clk, Rst); // r6 = t6
    ADD #(32) add_7(r6, h, t7); // t7 = r6 + h
    REG #(32) reg_7(t7, r7, Clk, Rst); // r7 = t7
    DIV #(32) div_1(r7, num, avgwire); // avgwire = r7 / num
    REG #(32) reg_8(avgwire, avg, Clk, Rst); // avg = avgwire
   
endmodule