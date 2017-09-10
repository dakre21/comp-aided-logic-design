`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: COMPARATOR module
// Module Name: comp_tb
// Project Name: Assignment 1
// Target Devices: Artix 7
// Tool Versions: 
// Description: COMPARATOR Test bench procedural module
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module comp_tb();
     
    // Declare inputs and outputs
    reg [1:0] a, b;
    wire gt, lt, eq;
 
    // Instantiate adder
    COMP #(2) comp_1(a, b, gt, lt, eq);

    // Begin tests
    initial begin
        // a == b case (init to zero)
        #10 a <= 2'b00;
        #10 b <= 2'b00;
        
        // a < b case (lt set)
        #10 b <= 2'b01; 
        
        // a > b case (gt set)
        #10 a <= 2'b10;
        
        // a == b case (eq set)
        #10 a <= 2'b01;
    end

endmodule
