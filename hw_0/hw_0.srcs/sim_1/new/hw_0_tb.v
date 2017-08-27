`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: Univeristy of Arizona
// Engineer: David Akre
// 
// Create Date: 08/26/2017 08:50:37 PM
// Design Name: HW #0
// Module Name: hw_0_tb
// Project Name: hw_0
// Target Devices: Artix 7
// Tool Versions: 
// Description: Test bench for procedural and structural designs
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module hw_0_procedural_tb();
    reg a3, a2, a1, a0;
    wire r0;
    
    // Simulate procedural deisgn first
    hw_0_procedural hw_0_procedural_1(a3, a2, a1, a0, r0);
    
    initial begin
        // Case 0
        a0 <= 0; a1 <= 0; a2 <= 0; a3 <= 0;
        #1 $display("r0 = %b", r0);
        
        // Case 1
        #10 a0 <= 0; a1 <= 0; a2 <= 0; a3 <= 1;
        #1 $display("r0 = %b", r0);
        
        // Case 2
        #10 a0 <= 0; a1 <= 0; a2 <= 1; a3 <= 0;
        #1 $display("r0 = %b", r0);
        
        // Case 3
        #10 a0 <= 0; a1 <= 0; a2 <= 1; a3 <= 1;
        #1 $display("r0 = %b", r0);
        
        // Case 4
        #10 a0 <= 0; a1 <= 1; a2 <= 0; a3 <= 0;
        #1 $display("r0 = %b", r0);
        
        // Case 5
        #10 a0 <= 0; a1 <= 1; a2 <= 0; a3 <= 1;
        #1 $display("r0 = %b", r0);
        
        // Case 6
        #10 a0 <= 0; a1 <= 1; a2 <= 1; a3 <= 0;
        #1 $display("r0 = %b", r0);
        
        // Case 7
        #10 a0 <= 0; a1 <= 1; a2 <= 1; a3 <= 1;
        #1 $display("r0 = %b", r0);
        
        // Case 8 
        #10 a1 <= 1; a1 <= 0; a2 <= 0; a3 <= 0;
        #1 $display("r0 = %b", r0);
        
        // Case 9 
        #10 a0 <= 1; a1 <= 0; a2 <= 0; a3 <= 1;
        #1 $display("r0 = %b", r0);
        
        // Case 10
        #10 a0 <= 1; a1 <= 0; a2 <= 1; a3 <= 0;
        #1 $display("r0 = %b", r0);
        
        // Case 11
        #10 a0 <= 1; a1 <= 0; a2 <= 1; a3 <= 1;
        #1 $display("r0 = %b", r0);
        
        // Case 12
        #10 a0 <= 1; a1 <= 1; a2 <= 0; a3 <= 0;
        #1 $display("r0 = %b", r0);
        
        // Case 13
        #10 a0 <= 1; a1 <= 1; a2 <= 0; a3 <= 1;
        #1 $display("r0 = %b", r0);
        
        // Case 14
        #10 a0 <= 1; a1 <= 1; a2 <= 1; a3 <= 0;
        #1 $display("r0 = %b", r0);
        
        // Case 15
        #10 a0 <= 1; a1 <= 1; a2 <= 1; a3 <= 1;
        #1 $display("r0 = %b", r0);
    
    end
    
    
endmodule

module hw_0_structural_tbl();
    reg a3, a2, a1, a0;
    wire r0;
    
    // Simulate structural design second
    hw_0_structural hw_0_structural_1(a3, a2, a1, a0, r0);
    
    initial begin
        // Case 0
        #10 a0 <= 0; a1 <= 0; a2 <= 0; a3 <= 0;
        #1 $display("r0 = %b", r0);
        
        // Case 1
        #10 a0 <= 0; a1 <= 0; a2 <= 0; a3 <= 1;
        #1 $display("r0 = %b", r0);
        
        // Case 2
        #10 a0 <= 0; a1 <= 0; a2 <= 1; a3 <= 0;
        #1 $display("r0 = %b", r0);
        
        // Case 3
        #10 a0 <= 0; a1 <= 0; a2 <= 1; a3 <= 1;
        #1 $display("r0 = %b", r0);
        
        // Case 4
        #10 a0 <= 0; a1 <= 1; a2 <= 0; a3 <= 0;
        #1 $display("r0 = %b", r0);
        
        // Case 5
        #10 a0 <= 0; a1 <= 1; a2 <= 0; a3 <= 1;
        #1 $display("r0 = %b", r0);
        
        // Case 6
        #10 a0 <= 0; a1 <= 1; a2 <= 1; a3 <= 0;
        #1 $display("r0 = %b", r0);
        
        // Case 7
        #10 a0 <= 0; a1 <= 1; a2 <= 1; a3 <= 1;
        #1 $display("r0 = %b", r0);
        
        // Case 8 
        #10 a1 <= 1; a1 <= 0; a2 <= 0; a3 <= 0;
        #1 $display("r0 = %b", r0);
        
        // Case 9 
        #10 a0 <= 1; a1 <= 0; a2 <= 0; a3 <= 1;
        #1 $display("r0 = %b", r0);
        
        // Case 10
        #10 a0 <= 1; a1 <= 0; a2 <= 1; a3 <= 0;
        #1 $display("r0 = %b", r0);
        
        // Case 11
        #10 a0 <= 1; a1 <= 0; a2 <= 1; a3 <= 1;
        #1 $display("r0 = %b", r0);
        
        // Case 12
        #10 a0 <= 1; a1 <= 1; a2 <= 0; a3 <= 0;
        #1 $display("r0 = %b", r0);
        
        // Case 13
        #10 a0 <= 1; a1 <= 1; a2 <= 0; a3 <= 1;
        #1 $display("r0 = %b", r0);
        
        // Case 14
        #10 a0 <= 1; a1 <= 1; a2 <= 1; a3 <= 0;
        #1 $display("r0 = %b", r0);
        
        // Case 15
        #10 a0 <= 1; a1 <= 1; a2 <= 1; a3 <= 1;
        #1 $display("r0 = %b", r0);
    
    end
    
    
endmodule
