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
#include <stdio.h>
#include <stdlib.h>

// Verify dpgen inputs helper function
bool verify_dpgen_inputs(int argc, char* argv[]) {
    // Begin verification steps
    if (argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Invalid number of inputs\n");
        return false;
    }

    return true;
}

// Main execution entry point
int main (int argc, char* argv[]) {

    // Verify inputs
    if (verify_dpgen_inputs(argc, argv) != true) {
        fprintf(stderr, "Valid usage: './dpgen <netlistFile> <verilogFile>\n");
        exit(-1);
    }

    exit(0);
}
