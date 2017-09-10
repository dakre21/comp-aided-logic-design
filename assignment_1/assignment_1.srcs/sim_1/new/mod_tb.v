`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: MODULUS module
// Module Name: mod_tb
// Project Name: Assignment 1
// Target Devices: Artix 7
// Tool Versions: 
// Description: MOULUS Test bench procedural module
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module mod_tb();
     
    reg [1:0] a, b;
    wire [1:0] rem;
    
    MOD #(2) mod_1(a, b, rem);
    
    initial begin
    
        #10 a <= 2'b01; b <= 2'b01; // 0
        #10 a <= 2'b01; b <= 2'b10; // 1
        #10 a <= 2'b01; b <= 2'b11; // 1
        #10 a <= 2'b10; b <= 2'b01; // 0
        #10 a <= 2'b11; b <= 2'b00; // 'x'
    
    end

endmodule
