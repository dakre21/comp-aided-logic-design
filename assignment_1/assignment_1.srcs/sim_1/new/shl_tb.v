`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: SHL module
// Module Name: shl_tb
// Project Name: Assignment 1
// Target Devices: Artix 7
// Tool Versions: 
// Description: SHL Test bench procedural module
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module shl_tb();
     
     // Declare inputs and outputs
    reg [1:0] a, sh_amt;
    wire [1:0] d;
     
    // Instantiate adder
    SHL #(2) shl_1(a, sh_amt, d);
    
    // Begin tests
    initial begin
       
        #10 a <= 2'b11; sh_amt <= 2'b01; // Shift by 1
        #10 a <= 2'b11; sh_amt <= 2'b10; // Shift by 2
        #10 a <= 2'b11; sh_amt <= 2'b11; // Shift by 3
        #10 a <= 2'b11; sh_amt <= 2'b00; // Don't shift by anything
        
    end

endmodule
