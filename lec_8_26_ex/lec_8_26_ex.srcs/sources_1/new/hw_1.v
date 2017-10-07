`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/28/2017 08:07:43 PM
// Design Name: 
// Module Name: hw_1
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


module hw_1(RST, CLK, A, B, C);
    parameter DATAWIDTH = 4;
    output reg [DATAWIDTH-1:0] A, B, C;
    input RST, CLK;

always @(posedge RST or posedge CLK) begin
    if (RST == 1) begin
        A = 2; B = 4; C=1;
    end
    else begin
        A <= B;
        C = B + 1;
        C <= A + B;
    end
end
    
endmodule
