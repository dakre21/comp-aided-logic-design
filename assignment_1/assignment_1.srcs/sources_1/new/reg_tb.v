`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 09/09/2017 12:52:38 PM
// Design Name: Register module
// Module Name: reg_tb
// Project Name: Assignment 1
// Target Devices: Artix 7
// Tool Versions: 
// Description: Register Test bench procedural module
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module reg_tb();
   
    // Input and output declarations for the register module
    reg [2:0] d;
    wire [2:0] q;
    reg Clk, Rst;
    
    // Start clock
    always 
        #10 Clk <= ~Clk;     
        
    // Instantiate reg module
    REG #(2) reg_1(d, q, Clk, Rst);    
        
    initial begin
        // Init control inputs
        Clk <= 0;
        #10 Rst <= 0;
        
        // Test two values
        @(posedge Clk);
        d <= 2'b00;
        @(posedge Clk);
        d <= 2'b01;
        
        // Reset reg
        @(posedge Clk);
        Rst <= 1;
        @(posedge Clk);
        Rst <= 0;
        
        // Test two more values
        @(posedge Clk);
        d <= 2'b10;
        @(posedge Clk);
        d <= 2'b11;
        
    end     

endmodule
