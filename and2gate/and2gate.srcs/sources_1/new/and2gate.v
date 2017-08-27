`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/26/2017 05:12:07 PM
// Design Name: 
// Module Name: and2gate
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module and2gate(A, B, F);
    input A, B;
    output F;
    reg F;
    
    always @(A, B)
    begin
        F <= A & B;
    end
endmodule
