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
#include <map>

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
    // Class members
    // Datapath to width map
    map<string, string> input_vars_;
    map<string, string> output_vars_;
    map<string, string> wire_vars_;
    map<string, string> reg_vars_;

    // Unsigned data path counters
    int add_count_;
    int sub_count_;
    int mul_count_;
    int div_count_;
    int mod_count_;
    int comp_count_;
    int shl_count_;
    int shr_count_;
    int reg_count_;
    int inc_count_;
    int dec_count_;
    int mux_count_;

    // Signed data path counters
    int sadd_count_;
    int ssub_count_;
    int smul_count_;
    int sdiv_count_;
    int smod_count_;
    int scomp_count_;
    int sshl_count_;
    int sshr_count_;
    int sreg_count_;
    int sinc_count_;
    int sdec_count_;
    int smux_count_;

    // Bad return code
    int bad_rc_;

    // Parse input buffer and create verilog file
    void parseBufferCreateVerilogSrc(char* buff, size_t buff_len);

    // Parse netlist substring and map to datapath component
    bool mapNetOpToDataPathComp(char* sub_buff, size_t sub_buff_len);

    // Write datapath op to file
    bool dataPathOpToFile(string op, int pos, const char* dcomp);

    // Set datapath component to string
    string setDataPathComp(string op, string data_width, const char* dcomp);

};
