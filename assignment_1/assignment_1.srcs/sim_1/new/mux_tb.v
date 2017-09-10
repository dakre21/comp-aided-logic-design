`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: MULTIPLEXER module
// Module Name: mux_tb
// Project Name: Assignment 1
// Target Devices: Artix 7
// Tool Versions: 
// Description: 2x1 MULTIPLEXER Test bench procedural module
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module mux_tb();
     
    reg [1:0] a, b;
    reg sel;
    wire [1:0] d;
    
    MUX2x1 #(2) mux2x1_1(a, b, d, sel);
    
    initial begin
    
        #10 a <= 2'b00; b <= 2'b01; sel <= 1; // Select b
        #10 a <= 2'b10; b <= 2'b01; sel <= 0; // Select a
        #10 a <= 2'b10; b <= 2'b11; sel <= 1; // Select b
        #10 a <= 2'b10; b <= 2'b11; sel <= 0; // Select a
        
    
    end

endmodule
