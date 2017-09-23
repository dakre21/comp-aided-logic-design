`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: circuit3 module
// Module Name: circuit3
// Project Name: Assignment 3
// Target Devices: Artix 7
// Tool Versions: 
// Description: Circuit 3
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module circuit3(a, b, c, d, e, f, g, h, sa, avg);

    // Declare inputs and outputs
    input [15:0] a, b, c, d, e, f, g, h;
    input [7:0] sa;
    
    output reg [15:0] avg;
    
    wire [31:0] l00, l01, l02, l03, l10, l11, l2, l2div2, l2div4, l2div8;
    
    /*
    l00 = a + b
    l01 = c + d
    l02 = e + f
    l03 = g + h
    l10 = l00 + l01
    l11 = l02 + l03
    l2 = l10 + l11
    l2div2 = l2 >> sa
    l2div4 = l2div2 >> sa
    l2div8 = l2div4 >> sa
    avg = l2div8
    */
    
endmodule