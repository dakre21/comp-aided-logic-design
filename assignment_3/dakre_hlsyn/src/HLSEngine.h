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
    // Class members
    // Datapath to width map
    map<string, string> input_vars_;
    map<string, string> output_vars_;
    map<string, string> wire_vars_;
    map<string, string> reg_vars_;
    
    // Dapapath to var multipmap
    multimap<string, string> vars_to_dp_;

    // Vector of operations
    vector<string> ops_;
    vector<string> outputs_;

    // Current datapath component
    string curr_dp_;

    // Unsigned data path counters
    int dp_count_;

    // Bad return code
    int bad_rc_;

    // Parse input buffer and create verilog file
    bool parseBufferCreateVerilogSrc(char* buff, size_t buff_len, FILE* file_out);

    // Parse netlist substring and map to datapath component
    bool mapNetOpToDataPathComp(char* sub_buff, size_t sub_buff_len, FILE* file_out);

    // Write datapath op to file
    bool dataPathOpToFile(string op, int pos, const char* dcomp, FILE* file_out);

    // Set datapath component to string
    string setDataPathComp(string op, string data_width, const char* dcomp);

    // Set datapath vars to component string
    void setDataPathVars(string* i_var, string* o_var, string* m_var, string* m2_var,
            string* m3_var, string map_var, string op, const char* docmp, int npos);

    // Calculate individual dapath component latency
    float calcDpLatency(string dcomp);

};
