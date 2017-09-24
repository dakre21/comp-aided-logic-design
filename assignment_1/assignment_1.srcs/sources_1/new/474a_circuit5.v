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
    
    reg Clk, Rst;
    
    output [31:0] z, x;
    
    wire [63:0] d, e, f, g, h;
    wire [1:0] dLTe, dEQe, dGTe;
    wire [63:0] xrin, zrin;
    
    wire [63:0] greg, hreg; // NOTE: Setting these as wires to be hooked up to the output port connection to the REG module
    
    // Start clock for circuit
    always 
        #10 Clk <= ~Clk; 
    
    ADD #(64) add_1(a, b, d); // d = a + b
    ADD #(64) add_2(a, c, e); // e = a + c
    SUB #(64) sub_1(a, b, f); // f = a - b
    COMP #(64) comp_1(d, e, dGTe, dLTe, dEQe); // dEQe = d == e or dLTe = d < e -- This comparator will set one of those wires to true based on result
    REG #(64) reg_1((dLTe ? d : e), g, Clk, Rst); // g = dLTe ? d : e
    REG #(64) reg_2((dEQe ? g : f), h, Clk, Rst); // h = dEQe ? g : f
    REG #(64) reg_3(g, greg, Clk, Rst); // greg = g
    REG #(64) reg_4(h, hreg, Clk, Rst); // hreg = h
    SHL #(64) shl_1(hreg, dLTe, xrin); // xrin = hreg << dLTe
    SHR #(64) shr_1(greg, dEQe, zrin); // zrin = greg >> dEQe
    REG #(32) reg_5(xrin, x, Clk, Rst); // x = xrin
    REG #(32) reg_6(zrin, z, Clk, Rst); // z = zrin

endmodule