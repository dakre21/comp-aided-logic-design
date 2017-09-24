Group:
David Akre (netid: dakre)


***************************************
Part 1/2:

Xilinx Tool:
Vivado 2017.2

Target FPGA & Speed Grade:
Artix-7 (part xc7a100tcsg324-1) & 155 speed grade

1ns / 1ns timescale

Method used to capture critical path:
- For all the individual datapath components I ran synthesis and implementation on them and obtained the critical path through the timing reports generated from those options.

***************************************
Part 3/4:

Xilinx Tool (circuits 1 - 6):
Vivado 2017.2

Xilinx Tool (circuits 7 - 8):
Vivado 2015.4 

Target FPGA & Speed Grade for circuits 1 - 6:
Artix-7 (part xc7a1001-fgg484) & 155 speed grade

Target FPGA & Speed Grade for circuits 7 - 8:
Artix-7 (part xc7a200tiffg1156-1L) & 328 speed grade

1ns / 1ns timescale

Method used to find estimated critical path:
- I analyzed each netlist circuit's datapath components and combinational logic dependencies to come up with an estimated critical path for each circuit. The datapath components critical path was found in part 2, so I leveraged those results for part 3. Thus, the critical path was based on the timing delay of the longest path for the estimation times.
  - Circuit 1's Longest Path: MUL16 -> SUB16 -> REG16
  - Circuit 2's Longest Path: ADD32 -> COMP32 -> REG32 -> SHL32 -> REG32
  - Circuit 3's Longest Path: ADD32 -> Add32 -> SHR32 -> REG32
  - Circuit 4's Longest Path: ADD32 x14 -> REG32
  - Circuit 5's Longest Path: ADD64 -> COMP64 -> REG64 x2 -> SHL64 -> REG64
  - Circuit 6's Longest Path: (ADD32 -> REG32) x7 -> DIV32 -> REG32
  - Circuit 7's Longest Path: MOD64 -> COMP64 -> REG64 x2 
  - Circuit 8's Longest Path: MOD64 -> COMP64 -> REG64 x2

Method used to capture critical path:
- I created verilog modules for all of the behavioral netlist circuits utilizing the datapath modules created in part 1/2 and then I ran synthesis and implementation on my implemented circuits to obtain the critical path through the timing reports generated from the implementation.

NOTE: I chose a different fpga board to run synthesis and implementation against in Parts 3/4 vs Parts 1/2 because of the IO resource constraint I had when building up the netlist circuits on the first board target. Additionally, for circuits 7 and 8 had to be synthesized and implemented on my work computer using vivado 2015.4, my home computer RAM was insufficient to synthesis and run implementation for those two circuits.

NOTE: Dapath components module name is all CAPS instead of lower case, there were collisions for Xilinx naming conventions when I used lower case for both.
