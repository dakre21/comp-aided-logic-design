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
#include <string.h>
#include <iostream>
#include <cstddef>

using namespace std;

class HLSEngine {

public:
    // CTOR
    HLSEngine();

    // DTOR
    ~HLSEngine();

    // Create verilog src
    bool createVerilogSrc(FILE* file_in, FILE* file_out);
   
    // Determine critical path of input netlist
    float findCriticalPath(FILE* file_in, FILE* file_out);

private:
    // Parse input buffer and create verilog file
    void parseBufferCreateVerilogSrc(char* buff, size_t buff_len);

    // Parse netlist substring and map to datapath component
    bool mapNetOpToDataPathComp(char* sub_buff, size_t sub_buff_len);

};
