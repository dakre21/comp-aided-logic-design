/* Author: David Akre
 * Date: 10/7/17
 * Description: Assignment 2 - main entry point
 * - This program will take in a behavioral netlist file and output
 *   a synthesizable verilog file. Additionally, this program will
 *   compute the critical path for a behavioral netlist granted 
 *   there are no issues in the behavioral netlist is invalid.
 *
 * Usage:
 * - './dpgen <netlistFile> <verilogFile>'
 *
 */ 

#include <dpgen.h>

// Forward declaration of files
FILE* file_in;
FILE* file_out;

// Verify dpgen inputs helper function
bool verify_dpgen_inputs(int argc, char* argv[]) {
    // Begin verification steps
    if (argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Invalid number of inputs\n");
        return false;
    }

    // Attempt to open the input file
    file_in = fopen(argv[1], "r");

    // Check if the file exists
    if (file_in == NULL) {
        fprintf(stderr, "Input file (i.e. <netlistFile>) does not exist\n");
        return false;
    }

    // Attempt to create verilog file
    string vsrc = string(argv[2]);

    if(vsrc.substr(vsrc.find_last_of(".") + 1) != "v") {
        fprintf(stderr, "Output file (i.e. <verilogFile>) contains an invalid extension, please use '.v' as the appropriate extension\n");
        return false;
    }

    file_out = fopen(argv[2], "w+");

    // Check if the file exists
    if (file_out == NULL) {
        fprintf(stderr, "Failed to create output file (i.e. <verilogFile>)\n");
        return false;
    }

    return true;
}

// Main execution entry point
int main(int argc, char* argv[]) {

    // Verify inputs
    if (verify_dpgen_inputs(argc, argv) != true) {
        fprintf(stderr, "Valid usage: './dpgen <netlistFile> <verilogFile>\n");
        exit(-1);
    }

    // Create HLSEngine
    engine = new HLSEngine(file_in, file_out);

    // Read input file- behavioral netlist into buffer
    engine->readFileData();

    // Parse buffer and create verilog file- synthesizable verilog code
    engine->parseBufferCreateVerilogSrc();

    // Find critical path of netlist
    float critical_path = engine->findCriticalPath();

    printf("Critical Path : %.3f\n", critical_path);

    exit(0);
}
