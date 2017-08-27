`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/26/2017 07:19:04 PM
// Design Name: 
// Module Name: rounder_tb
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


module rounder_tb();
    reg a2, a1, a0;
    
    // Wire connects different components together
    wire r2, r1, r0;
    
    // Instantiate rounder module
    rounder rounder_1(a2, a1, a0, r2, r1, r0);
    
    // Inital = whatever in this block it only runs once
    // regardless of varaibles in the sensativity list
    initial begin
        // #<num> means delay for some time
        // Case 0
        a2 <= 0; a1 <= 0; a0 <= 0;
        
        // Case 1
        #10 a2 <= 0; a1 <= 0; a0 <= 1;
        
        // Case 2
        #10 a2 <= 0; a1 <= 1; a0 <= 0;
        
        // Case 3
        #10 a2 <= 0; a1 <= 1; a0 <= 1;
        
        // Case 4
        #10 a2 <= 1; a1 <= 0; a0 <= 0;
        
        // Case 5
        #10 a2 <= 1; a1 <= 0; a0 <= 1;
        
        // Case 6
        #10 a2 <= 0; a1 <= 1; a0 <= 1;
        
        // Case 7
        #10 a2 <= 1; a1 <= 1; a0 <= 1;
    
    end
endmodule
