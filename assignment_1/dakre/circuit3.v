`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: circuit3 module
// Module Name: circuit3
// Project Name: Assignment 3
// Target Devices: Artix 7
// Tool Versions: 
// Description: Circuit 3
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module circuit3(a, b, c, d, e, f, g, h, sa, avg);

    // Declare inputs and outputs
    input [15:0] a, b, c, d, e, f, g, h;
    input [7:0] sa;
    
    reg Clk, Rst;
    
    output [15:0] avg;
    
    wire [31:0] l00, l01, l02, l03, l10, l11, l2, l2div2, l2div4, l2div8;
    
    // Start clock for circuit
    always 
        #10 Clk <= ~Clk; 
    
    ADD #(32) add_1(a, b, l00); // l00 = a + b
    ADD #(32) add_2(c, d, l01); // l01 = c + d
    ADD #(32) add_3(e, f, l02); // l02 = e + f
    ADD #(32) add_4(g, h, l03); // l03 = g + h
    ADD #(32) add_5(l00, l01, l10); // l10 = l00 + l01
    ADD #(32) add_6(l02, l03, l11); // l11 = l02 + l03
    ADD #(32) add_7(l10, l11, l2); // l2 = l10 + l11
    SHR #(32) shr_1(l2, sa, l2div2); // l2div2 = l2 >> sa
    SHR #(32) shr_2(l2div2, sa, l2div4); // l2div4 = l2div2 >> sa
    SHR #(32) shr_3(l2div4, sa, l2div8); // l2div8 = l2div4 >> sa
    REG #(32) reg_1(l2div8, avg, Clk, Rst); // avg = l2div8
    
endmodule