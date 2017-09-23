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
    
    reg Clk, Rst;
    
    output reg [7:0] z;
    output reg [15:0] x;
    
    wire [7:0] d, e;
    wire [15:0] f, g;
    wire [15:0] xwire;
    
    // Wire declaration for lt/eq, gt = g which is above
    wire lt, eq;
    
    // Start clock for circuit
    always 
        #10 Clk <= ~Clk;   
    
    ADD #(8) add_1(a, b, d); // d = a + b
    ADD #(8) add_2(a, c, e); // e = a + c
    COMP #(8) comp_1(d, e, g, lt, eq); // g = d > e
    REG #(8) reg_1((g ? d : e), z, Clk, Rst); // z = g ? d : e
    MUL #(16) mul_1(a, c, f); // f = a * c
    SUB #(16) sub_1(f, d, xwire); // xwire = f - d
    REG #(16) reg_2(xwire, x, Clk, Rst); // x = xwire

endmodule
