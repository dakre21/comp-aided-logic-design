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
#include <math.h>
#include <iostream>
#include <cstddef>
#include <map>
#include <vector>

using namespace std;

class HLSEngine {

public:
    // CTOR
    HLSEngine();

    // DTOR
    ~HLSEngine();

    // Create verilog src
    bool createVerilogSrc(FILE* file_in, FILE* file_out, string v_file, int latency);
   
private:
    // Initialize class members
    vector<string> vertices_;
    vector<string> operands_;

    // Map states to operations
    map<int, char*> unsched_map_;

    // Bad return code
    int bad_rc_;

    // Map count
    int unsched_map_count_;

    // Parse input buffer and create verilog file
    bool parseBufferCreateVerilogSrc(char* buff, size_t buff_len, FILE* file_out);

    // Create CDFG
    bool createCDFG(const char* sub_buff, size_t sub_buff_len);

};
