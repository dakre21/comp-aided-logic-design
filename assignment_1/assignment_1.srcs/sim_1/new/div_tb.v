`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: DIV module
// Module Name: div_tb
// Project Name: Assignment 1
// Target Devices: Artix 7
// Tool Versions: 
// Description: DIV Test bench procedural module
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module div_tb();
     
   reg [1:0] a, b;
   wire [1:0] quot;

   DIV #(2) div_1(a, b, quot);

   initial begin

       #10 a <= 2'b01; b <= 2'b01; // 1
       #10 a <= 2'b00; b <= 2'b11; // 0
       #10 a <= 2'b10; b <= 2'b01; // 2
       #10 a <= 2'b11; b <= 2'b00; // Overflow (undefined 'x')
   
    end

endmodule
