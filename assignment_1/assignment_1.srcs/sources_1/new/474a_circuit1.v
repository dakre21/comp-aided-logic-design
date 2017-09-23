`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: circuit1 module
// Module Name: circuit1
// Project Name: Assignment 1
// Target Devices: Artix 7
// Tool Versions: 
// Description: Circuit 1 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module circuit1(a, b, c, z, x);

    // Declare inputs and outputs
    input [7:0] a, b, c;
    
    output reg [7:0] z;
    output reg [15:0] x;
    
    wire [7:0] d, e;
    wire [15:0] f, g;
    wire [15:0] xwire;
    
    /*
    Use datapath library to do the following operations
    d = a + b
    e = a + c
    g = d > e
    z = g ? d : e
    f = a * c
    xwire = f - d
    x = xwire
    */
    

endmodule
