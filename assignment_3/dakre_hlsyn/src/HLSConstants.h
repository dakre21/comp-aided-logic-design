// Netlist constants
const char* NET_REGISTER = "register";
const char* NET_INT1     = "Int1";
const char* NET_INT2     = "Int2";
const char* NET_INT8     = "Int8";
const char* NET_INT16    = "Int16";
const char* NET_INT32    = "Int32";
const char* NET_INT64    = "Int64";
const char* NET_UINT1    = "UInt1";
const char* NET_UINT2    = "UInt2";
const char* NET_UINT8    = "UInt8";
const char* NET_UINT16   = "UInt16";
const char* NET_UINT32   = "UInt32";
const char* NET_UINT64   = "UInt64";
const char* NET_WIRE     = "wire";
const char* NET_INPUT    = "input";
const char* NET_OUTPUT   = "output";
const char* NET_REGW     = "wire";

// Datawidth constants
const char* ODATAWIDTH_1        = "reg";
const char* ODATAWIDTH_2        = "reg [1:0]";
const char* ODATAWIDTH_8        = "reg [7:0]";
const char* ODATAWIDTH_16       = "reg [15:0]";
const char* ODATAWIDTH_32       = "reg [31:0]";
const char* ODATAWIDTH_64       = "reg [63:0]";
const char* DATAWIDTH_1       = "";
const char* DATAWIDTH_2       = "[1:0]";
const char* DATAWIDTH_8       = "[7:0]";
const char* DATAWIDTH_16      = "[15:0]";
const char* DATAWIDTH_32      = "[31:0]";
const char* DATAWIDTH_64      = "[63:0]";

const char* DATAWIDTH_1_STR   = "1";
const char* DATAWIDTH_2_STR   = "2";
const char* DATAWIDTH_8_STR   = "8";
const char* DATAWIDTH_16_STR  = "16";
const char* DATAWIDTH_32_STR  = "32";
const char* DATAWIDTH_64_STR  = "64";

// Misc constants
const char* MISC_NULL       = "\0";
const char* MISC_NEW_LINE   = "\n";
const char* MISC_WHITESPACE = " ";
const char* MISC_COMMENT    = "\\";
const char* MISC_LINE_END   = ";\n";
const char* MISC_COMMA      = ",";
const char* MISC_TAB        = "    ";
const char* MISC_EQUALS     = "=";
const char* MISC_SEL        = ":";

const char* EQZ             = "EQZ_";
const char* GTZ             = "GTZ_";
const char* LTZ             = "LTZ_";

const char* STATIC_NULL      = " ";
const char* STATIC_COMMENT   = "// HLS has generated this HDL code with the hlsyn executable\n// Author: David Akre\n\n";
const char* STATIC_DP        = "    // Creating HLSM datapath\n";
const char* STATIC_CTRL      = "    // Creating HLSM controller logic\n";
const char* STATIC_STARTC    = "    // Initial Wait State S0 of the HLSM\n"; 
const char* STATIC_CODEC     = "    // C to HLSM states below based on FDS scheduling\n";
const char* STATIC_DONEC     = "    // Final State to conclude the HLSM by setting Done to logic level high (i.e. 1)\n";
const char* STATIC_INPUTS    = "    input Clk, Rst, Start;\n";
const char* STATIC_OUTPUTS   = "    output reg Done;\n";
const char* STATIC_MODULE    = "module HLSM (Clk, Rst, Start, Done, ";
const char* STATIC_ENDMODULE = "endmodule\n";
const char* STATIC_TIMING    = "`timescale 1ns / 1ns\n\n";
const char* STATIC_ALWAYS      = "    always @(posedge Clk) begin\n";
const char* STATIC_END       = "    end\n";
const char* STATIC_DONE      = "        Done = 1;\n";

// Resource latencies
const unsigned int MUL_LATENCY     = 2;
const unsigned int DIV_MOD_LATENCY = 3;
const unsigned int OTHER_LATENCY   = 1;

