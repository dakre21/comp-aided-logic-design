`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: circuit2 module
// Module Name: circuit2
// Project Name: Assignment 2
// Target Devices: Artix 7
// Tool Versions: 
// Description: Circuit 2
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module circuit2(a, b, c, z, x);

    // Declare inputs and outputs
    input [31:0] a, b, c;
    
    output [31:0] z, x;
    
    reg Clk, Rst;
    
    wire [31:0] d, e, f, g, h;
    wire [1:0] dLTe, dEQe;
    wire [31:0] zwire, xwire;
    
    /*
    d = a + b
    e = a + c
    f = a - b
    dEQe = d == e
    dLTe = d < e
    g = dLTe ? d : e
    h = dEQe ? g : f
    xwire = g << dLTe
    zwire = h >> dEQe
    x = xwire
    z = zwire
    */
    

endmodule