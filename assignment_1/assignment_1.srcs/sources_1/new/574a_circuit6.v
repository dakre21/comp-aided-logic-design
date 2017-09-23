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
    
    output reg [15:0] avg;
    
    reg [15:0] r1, r2, r3, r4, r5, r6, r7;
    
    wire [15:0] avgwire;
    wire [31:0] t1, t2, t3, t4, t5, t6, t7;
    
    /*
    t1 = a + b
    r1 = t1
    t2 = r1 + c
    r2 = t2
    t3 = r2 + d
    r3 = t3
    t4 = r3 + e
    r4 = t4
    t5 = r4 + f
    r5 = t5
    t6 = r5 + g
    r6 = t6
    t7 = r6 + h
    r7 = t7
    avgwire = r7 / num
    avg = avgwire
    */
    
    

endmodule