`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/28/2017 08:08:08 PM
// Design Name: 
// Module Name: hw1_tb
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


module hw1_tb();
    reg RST, CLK;
    
    wire [2:0] A, B, C;
    
    hw_1 #(4) hw_1_1(RST, CLK, A, B, C);
    
    always begin
        #10 CLK = ~CLK;
    end
    
    initial begin
        CLK <= 1;
        RST <= 1;
        #15 RST <= 0;
    end
endmodule
