`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: MUL module
// Module Name: mul_tb
// Project Name: Assignment 1
// Target Devices: Artix 7
// Tool Versions: 
// Description: MUL Test bench procedural module
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module mul_tb();
     
    reg [1:0] a, b;
    wire [1:0] prod;
    
    MUL #(2) mul_1(a, b, prod);
    
    initial begin
    
        #10 a <= 2'b01; b <= 2'b01; // 1
        #10 a <= 2'b01; b <= 2'b11; // 3
        #10 a <= 2'b01; b <= 2'b10; // 2
        #10 a <= 2'b11; b <= 2'b11; // 0 (overflow)
        #10 a <= 2'b11; b <= 2'b00; // 0
    
    end

endmodule
