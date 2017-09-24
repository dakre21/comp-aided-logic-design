Group:
David Akre (netid: dakre)

Xilinx Tool:
Vivado 2017.2

***************************************
Part 1/2:

Target FPGA & Speed Grade:
Artix-7 (part xc7a100tcsg324-1) & 155 speed grade
1ns / 1ns timescale

Method used to capture critical path:
- For all the individual datapath components I ran synthesis and implementation on them and obtained the critical path through the timing reports generated from those options.

***************************************
Part 3/4:
Target FPGA & Speed Grade:
Artix-7 (part xc7a1001-fgg484) & 155 speed grade
1ns / 1ns timescale

Method used to find estimated critical path:
- I analyzed each netlist circuit's datapath components and combinational logic dependencies to come up with an estimated critical path for each circuit. The datapath components critical path was found in part 2, so I leveraged those results for part 3. Thus, the critical path was based on the timing delay of the longest path for the estimation times.
  - Circuit 1's Longest Path: MUL16 -> SUB16 -> REG16
  - Circuit 2's Longest Path: ADD32 -> COMP32 -> REG32 -> SHL32 -> REG32
  - Circuit 3's Longest Path: ADD32 -> Add32 -> SHR32 -> REG32
  - Circuit 4's Longest Path: ADD32 x14 -> REG32
  - Circuit 5's Longest Path: ADD64 -> COMP64 -> REG64 x2 -> SHL64 -> REG64
  - Circuit 6's Longest Path: (ADD32 -> REG32) x7 -> DIV32 -> REG32
  - Circuit 7's Longest Path:
  - Circuit 8's Longest Path:

Method used to capture critical path:
- I created verilog modules for all of the behavioral netlist circuits utilizing the datapath modules created in part 1/2 and then I ran synthesis and implementation on my implemented circuits to obtain the critical path through the timing reports generated from the implementation.

NOTE: I chose a different fpga board to run synthesis and implementation against in Parts 3/4 vs Parts 1/2 because of the IO resource constraint I had when building up the netlist circuits on the first board target.
