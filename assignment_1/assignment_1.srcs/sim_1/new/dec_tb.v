`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: DEC module
// Module Name: dec_tb
// Project Name: Assignment 1
// Target Devices: Artix 7
// Tool Versions: 
// Description: DEC Test bench procedural module
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module dec_tb();
     reg [1:0] a;
     wire [1:0] d;
     
     DEC #(2) dec_1(a, d);
     
     initial begin
     
        #10 a <= 2'b01;
        #10 a <= 2'b00;
        #10 a <= 2'b10;
        #10 a <= 2'b11;
        
     end

endmodule
