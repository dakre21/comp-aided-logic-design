`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/26/2017 06:59:58 PM
// Design Name: 
// Module Name: rounder
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


// PROCEDURAL
module rounder(a2, a1, a0, r2, r1, r0);
    input a2, a1, a0;
    
    // reg key word describes that a varaible changes during execution
    output reg r2, r1, r0;
    
    // always watch a2, a1, and a0 in the sensativity list
    always @(a2, a1, a0) begin
        // <= is the non blocking operator-- everything can execute in parallel this way
        // = is the blocking operator
        r2 <= a2 & ~a1 | a2 & ~a0 | (~a2 & a1 & a0);
        r1 <= ~a1 & a0 | a1 & ~a0;
        r0 <= 0;
    end
    
endmodule
