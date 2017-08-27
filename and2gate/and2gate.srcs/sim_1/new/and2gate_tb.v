`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/26/2017 05:14:27 PM
// Design Name: 
// Module Name: and2gate_tb
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


module and2gate_tb();
    reg A_t, B_t;
    wire F_t;
    
    and2gate and2gate_1(A_t, B_t, F_t);
    
    initial
    begin
        // Case 0
        A_t <= 0; B_t <= 0;
        #1 $display("F_t = %b", F_t);
        
        // Case 1
        A_t <= 0; B_t <= 1;
        #1 $display("F_t = %b", F_t);
        
        // Case 2
        A_t <= 1; B_t <= 0;
        #1 $display("F_t = %b", F_t);
        
        // Case 3
        A_t <= 1; B_t <= 1;
        #1 $display("F_t = %b", F_t);
    end
endmodule
