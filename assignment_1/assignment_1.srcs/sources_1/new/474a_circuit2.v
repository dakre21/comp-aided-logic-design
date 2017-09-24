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
    wire [1:0] dLTe, dEQe, dGTe;
    wire [31:0] zwire, xwire;
    
    // Start clock for circuit
    always 
        #10 Clk <= ~Clk; 
    
    ADD #(32) add_1(a, b, d); // d = a + b
    ADD #(32) add_2(a, c, e); // e = a + c
    SUB #(32) sub_1(a, b, f); // f = a - b
    COMP #(32) comp_1(d, e, dGTe, dLTe, dEQe); // dEQe = d == e or dLTe = d < e -- This comparator will set one of those wires to true based on result
    REG #(32) reg_1((dLTe ? d : e), g, Clk, Rst); // g = dLTe ? d : e
    REG #(32) reg_2((dEQe ? g : f), h, Clk, Rst); // h = dEQe ? g : f
    SHL #(32) shl_1(g, dLTe, xwire); // xwire = g << dLTe
    SHR #(32) shr_1(h, dEQe, zwire); // zwire = h >> dEQe
    REG #(32) reg_3(xwire, x, Clk, Rst); // x = xwire
    REG #(32) reg_4(zwire, z, Clk, Rst); // z = zwire    

endmodule