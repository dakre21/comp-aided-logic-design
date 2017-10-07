/* Author: David Akre
 * Date: 10/7/17
 * Description: Assignment 2 - HLSEngine class
 * - This class helps perform the following functionality
 *   - Read input file data- behavioral netlist file
 *   - Parse input buffer and create verilog file/code
 *   - Calculate critical path of behavioral netlist
 *
 */ 

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstddef>

using namespace std;

class HLSEngine {

public:
    // CTOR
    HLSEngine(FILE* file_in, FILE* file_out);

    // DTOR
    ~HLSEngine();

    // Read file data public function
    void readFileData();

    // Parse input buffer and create verilog file
    void parseBufferCreateVerilogSrc();

    // Determine critical path of input netlist
    float findCriticalPath();

private:
    // Class members
    void* buff_;
    size_t buff_len_;
    FILE* file_in_;
    FILE* file_out_;

};
