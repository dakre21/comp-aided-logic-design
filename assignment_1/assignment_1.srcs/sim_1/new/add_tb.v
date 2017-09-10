`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: ADDER module
// Module Name: add_tb
// Project Name: Assignment 1
// Target Devices: Artix 7
// Tool Versions: 
// Description: ADDER Test bench procedural module
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module add_tb();

    // Declare inputs and outputs
    reg [1:0] a, b;
    wire [1:0] sum;
     
    // Instantiate adder
    ADD #(2) add_1(a, b, sum);
    
    // Begin tests
    initial begin
        // Test 01 + 00
        #10 a <= 2'b00;
        #10 b <= 2'b01; 
        
        // Test 10 + 01
        #10 a <= 2'b10;
        #10 b <= 2'b01;
        
        // Test 11 + 01 (overflow but not being caught; sum == 00)
        #10 a <= 2'b11;
        #10 b <= 2'b01;
    end

endmodule
