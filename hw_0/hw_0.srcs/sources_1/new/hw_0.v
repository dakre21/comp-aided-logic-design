`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: University of Arizona
// Engineer: David Akre
// 
// Create Date: 08/26/2017 08:26:55 PM
// Design Name: HW #0
// Module Name: hw_0_procedural & hw_0_structural
// Project Name: hw_0
// Target Devices: Artix 7 
// Tool Versions: 
// Description: Simple two OR feeding into AND gate procedural and structural 
// design.
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

// Structural blocks for design

module andGate(x, y, z);
    input x, y;
    output reg z;
    
    always @(x, y) begin
        z <= x & y;
     end

endmodule

module orGate(x, y, z);
    input x, y;
    output reg z;
    
    always @(x, y) begin
        z <= x | y;
    end

endmodule

// HW designs

// Procedural design
module hw_0_procedural(a3, a2, a1, a0, r0);
    input a3, a2, a1, a0;
    output reg r0;
    
    always @(a3, a2, a1, a0) begin
        r0 <= (a0 | a1) & (a2 | a3);
    end

endmodule

// Structural design
module hw_0_structural(a3, a2, a1, a0, r0);
    input a3, a2, a1, a0;
    output wire r0;
    
    wire n1, n2;
    
    orGate orGate_1(a0, a1, n1);
    orGate orGate_2(a2, a3, n2);
    andGate andGate_1(n1, n2, r0);
    
endmodule

