`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: circuit8 module
// Module Name: circuit8
// Project Name: Assignment 1
// Target Devices: Artix 7
// Tool Versions: 
// Description: Circuit 8
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module circuit8(a, b, c, zero, z);

    // Declare inputs and outputs
    input [63:0] a, b, c, zero;
    
    output [63:0] z;
    
    wire [63:0] e, f, g, zwire;
    wire [1:0] gEQz;
    
    /*
    e = a - 1
    f = c + 1
    g = a % c
    gEQz = g == zero
    zwire = gEQz ? e : f
    z = zwire
    */
endmodule