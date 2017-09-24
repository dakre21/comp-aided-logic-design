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
    
    reg Clk, Rst;
    
    wire [63:0] e, f, g, zwire;
    wire [1:0] gEQz, gLTz, gGTz;
    
    // Start clock for circuit
    always 
        #10 Clk <= ~Clk; 
        
    DEC #(64) dec_1(a, e); // e = a - 1
    INC #(64) inc_1(c, f); // f = c + 1
    MOD #(64) mod_1(a, c, g); // g = a % c
    COMP #(64) comp_1(g, zero, gGTz, gLTz, gEQz); // gEQz = g == zero 
    REG #(64) REG_1((gEQz ? e : f), zwire, Clk, Rst); // zwire = gEQz ? e : f
    REG #(64) REG_2(zwire, z, Clk, Rst); // z = zwire
    
endmodule