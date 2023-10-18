`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 26.07.2023 16:57:47
// Design Name: 
// Module Name: testbench
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


module testbench(
);

reg clk;
reg rst_n;

always #12.25 clk = ~clk;

initial begin
    clk = 0;
    rst_n = 0;
    
    #24.5 rst_n = 1;
end

top_nexys7 boh (
    .IO_CLK(clk),
    .IO_RST_N(rst_n)
);

endmodule
