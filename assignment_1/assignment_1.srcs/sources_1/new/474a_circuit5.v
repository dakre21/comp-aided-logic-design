`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: circuit5 module
// Module Name: circuit5
// Project Name: Assignment 5
// Target Devices: Artix 7
// Tool Versions: 
// Description: Circuit 5
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module circuit5(a, b, c, z, x);

    // Declare inputs and outputs
    input [63:0] a, b, c;
    
    output reg [31:0] z, x;
    
    wire [63:0] d, e, f, g, h;
    wire [1:0] dLTe, dEQe;
    wire [63:0] xrin, zrin;
    reg [63:0] greg, hreg;
    
    /*
    d = a + b
    e = a + c
    f = a - b
    dEQe = d == e
    dLTe = d < e
    g = dLTe ? d : e
    h = dEQe ? g : f
    greg = g
    hreg = h
    xrin = hreg << dLTe
    zrin greg >> dEQe
    x = xrin
    z = zrin
    */

endmodule