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

#include <hlsyn.h>

// Forward declarations
FILE* file_in;
FILE* file_out;
int latency;
string v_file;

void app_exit(int rc) {
    // Close files
    fclose(file_in);
    fclose(file_out);

    exit(rc);
}

// Verify dpgen inputs helper function
bool verify_hlsyn_inputs(int argc, char* argv[]) {
    // Begin verification steps
    if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL) {
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

    // Attempt to read 2nd argument (latency)
    sscanf(argv[2], "%d", &latency);

    if (latency <= 0) {
        fprintf(stderr, "Input latency is invalid, must be greater than 0\n");
        return false;
    }

    // Attempt to create verilog file
    string vsrc = string(argv[3]);

    if(vsrc.substr(vsrc.find_last_of(".") + 1) != "v") {
        fprintf(stderr, "Output file (i.e. <verilogFile>) contains an invalid extension, please use '.v' as the appropriate extension\n");
        fclose(file_in);
        return false;
    }

    file_out = fopen(argv[3], "w+");
    v_file = string(argv[3]);

    // Check if the file exists
    if (file_out == NULL) {
        fprintf(stderr, "Failed to create output file (i.e. <verilogFile>)\n");
        fclose(file_in);
        return false;
    }

    return true;
}

// Main execution entry point
int main(int argc, char* argv[]) {

    // Verify inputs
    if (verify_hlsyn_inputs(argc, argv) != true) {
        fprintf(stderr, "Valid usage: './hlsyn <netlistFile> <latency> <verilogFile>\n");
        exit(-1);
    }

    // Create HLSEngine
    engine = new HLSEngine();

    // Create verilog src
    if (engine->createVerilogSrc(file_in, file_out, v_file, latency) != true) {
        app_exit(-1);
    }

    app_exit(0);
}
