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
#include <math.h>
#include <iostream>
#include <cstddef>
#include <map>
#include <vector>
#include "GraphHelper.h"

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
    vector<Node> vertices_;
    vector<string> operands_;
    vector<string> outputs_;
    vector<string> operations_;

    // Map edges
    multimap<Node*, Edge> edges_;

    // Bad return code
    int bad_rc_;

    // Vertices count
    int count_;

    // Parse input buffer and create verilog file
    bool parseBufferCreateVerilogSrc(char* buff, size_t buff_len, FILE* file_out);

    // Create CDFG
    bool createCDFG(const char* sub_buff, size_t sub_buff_len);

    // Unscheduled graph
    void createUnschedGraph();

};
