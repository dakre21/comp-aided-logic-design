`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: circuit7 module
// Module Name: circuit7
// Project Name: Assignment 7
// Target Devices: Artix 7
// Tool Versions: 
// Description: Circuit 7
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module circuit7(a, b, c, d, zero, z);

    // Declare inputs and outputs
    input [63:0] a, b, c, d, zero;
    
    output [63:0] z;
    
    wire [63:0] e, f, g, zwire;
    wire [1:0] gEQz;
    
    /*
    e = a / b
    f = c / d
    g = a % b
    gEQz = g == zero
    zwire = gEQz ? e : f
    z = zwire
    */

endmodule