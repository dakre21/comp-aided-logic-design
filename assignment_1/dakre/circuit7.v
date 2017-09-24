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
    
    reg Clk, Rst;
    
    wire [63:0] e, f, g, zwire;
    wire [1:0] gEQz, gLTz, gGTz;
    
    // Start clock for circuit
    always 
        #10 Clk <= ~Clk; 
    
    DIV #(64) div_1(a, b, e); // e = a / b
    DIV #(64) div_2(c, d, f); // f = c / d
    MOD #(64) mod_1(a, b, g); // g = a % b
    COMP #(64) comp_1(g, zero, gGTz, gLTz, gEQz); // gEQz = g == zero 
    REG #(64) REG_1((gEQz ? e : f), zwire, Clk, Rst); // zwire = gEQz ? e : f
    REG #(64) REG_2(zwire, z, Clk, Rst); // z = zwire

endmodule