#include "HLSEngine.h"
#include "HLSConstants.h"
#include <ctype.h>
#include <list>
#include <ctime>

HLSEngine::HLSEngine() :

           vertices_(),
           operands_(),
           outputs_(),
           operations_(),
           edges_(),
           count_(0),
           bad_rc_(-1) {
    // Do nothing
}

HLSEngine::~HLSEngine() {
    // Do nothing
}

void HLSEngine::createHLSM(FILE* file_out, int latency) {
    // Part 1 Write initial verilog code

    // Write timescale
    fputs(STATIC_TIMING, file_out);

    // Write initial stuff for verilog code
    fputs(STATIC_COMMENT, file_out);

    // Write module
    fputs(STATIC_MODULE, file_out);
    int pos = 0;
    string sub_str = "";
    string final_str = "";
    for (size_t i = 0; i < operations_.size(); i++) {
        sub_str = operations_[i];

        pos = sub_str.find("variable");
        if (pos != bad_rc_) {
            continue;
        }

        pos = sub_str.find("input");
        if (pos != bad_rc_) {
            sub_str.replace(pos, strlen("input"), "");
            sub_str.replace((sub_str.length() - 4), sub_str.length(), ", ");
            sub_str.replace(0, 4, "");
        }

        pos = sub_str.find("output");
        if (pos != bad_rc_) {
            sub_str.replace(pos, strlen("output"), "");
            sub_str.replace((sub_str.length() - 4), sub_str.length(), ", ");
            sub_str.replace(0, 4, "");
        }

        pos = sub_str.find(NET_UINT16);
        if (pos != bad_rc_) {
            sub_str.replace(pos, strlen(NET_UINT16), "");
            final_str += sub_str;
            continue;
        }

        pos = sub_str.find(NET_UINT32);
        if (pos != bad_rc_) {
            sub_str.replace(pos, strlen(NET_UINT32), "");
            final_str += sub_str;
            continue;
        }

        pos = sub_str.find(NET_UINT64);
        if (pos != bad_rc_) {
            sub_str.replace(pos, strlen(NET_UINT64), "");
            final_str += sub_str;
            continue;
        }

        pos = sub_str.find(NET_UINT1);
        if (pos != bad_rc_) {
            sub_str.replace(pos, strlen(NET_UINT1), "");
            final_str += sub_str;
            continue;
        }

        pos = sub_str.find(NET_UINT2);
        if (pos != bad_rc_) {
            sub_str.replace(pos, strlen(NET_UINT2), "");
            final_str += sub_str;
            continue;
        }

        pos = sub_str.find(NET_UINT8);
        if (pos != bad_rc_) {
            sub_str.replace(pos, strlen(NET_UINT8), "");
            final_str += sub_str;
            continue;
        }

        pos = sub_str.find(NET_INT16);
        if (pos != bad_rc_) {
            sub_str.replace(pos, strlen(NET_INT16), "");
            final_str += sub_str;
            continue;
        }

        pos = sub_str.find(NET_INT32);
        if (pos != bad_rc_) {
            sub_str.replace(pos, strlen(NET_INT32), "");
            final_str += sub_str;
            continue;
        }

        pos = sub_str.find(NET_INT64);
        if (pos != bad_rc_) {
            sub_str.replace(pos, strlen(NET_INT64), "");
            final_str += sub_str;
            continue;
        }
        pos = sub_str.find(NET_INT1);
        if (pos != bad_rc_) {
            sub_str.replace(pos, strlen(NET_INT1), "");
            final_str += sub_str;
            continue;
        }

        pos = sub_str.find(NET_INT2);
        if (pos != bad_rc_) {
            sub_str.replace(pos, strlen(NET_INT2), "");
            final_str += sub_str;
            continue;
        }

        pos = sub_str.find(NET_INT8);
        if (pos != bad_rc_) {
            sub_str.replace(pos, strlen(NET_INT8), "");
            final_str += sub_str;
            continue;
        }
    }

    final_str.replace((final_str.length() - 2), final_str.length(), ");\n");
    fputs(final_str.c_str(), file_out);

    // Write inputs and outputs
    fputs(STATIC_INPUTS, file_out);
    fputs(STATIC_OUTPUTS, file_out);
    fputs("    reg clk_en;\n", file_out);

    // Part 2 Write custom inputs and outputs
    pos = 0;
    bool ofound = false;
    string var_str = "";
    string tmp_str = "";
    for (size_t i = 0; i < operations_.size(); i++) {
        sub_str = operations_[i];

        pos = sub_str.find("variable");
        if (pos != bad_rc_) {
            tmp_str = sub_str;
            sub_str.replace(pos, strlen("variable"), "");
            var_str = tmp_str.replace(pos, strlen("variable UInt"), "");
        }

        pos = sub_str.find("output");
        if (pos != bad_rc_) {
            ofound = true; 
        }

        sub_str.replace((sub_str.length() - 4), sub_str.length(), ";\n");

        pos = sub_str.find(NET_UINT16);
        if (pos != bad_rc_) {
            if (ofound) {
                sub_str.replace(pos, strlen(NET_UINT16), ODATAWIDTH_16);
            } else {
                sub_str.replace(pos, strlen(NET_UINT16), DATAWIDTH_16);
            }
            fputs(sub_str.c_str(), file_out);
            continue;
        }

        pos = sub_str.find(NET_UINT32);
        if (pos != bad_rc_) {
            if (ofound) {
                sub_str.replace(pos, strlen(NET_UINT32), ODATAWIDTH_32);
            } else {
                sub_str.replace(pos, strlen(NET_UINT32), DATAWIDTH_32);
            }
            fputs(sub_str.c_str(), file_out);
            continue;
        }

        pos = sub_str.find(NET_UINT64);
        if (pos != bad_rc_) {
            if (ofound) {
                sub_str.replace(pos, strlen(NET_UINT64), ODATAWIDTH_64);
            } else {
                sub_str.replace(pos, strlen(NET_UINT64), DATAWIDTH_64);
            }
            fputs(sub_str.c_str(), file_out);
            continue;
        }

        pos = sub_str.find(NET_UINT1);
        if (pos != bad_rc_) {
            if (ofound) {
                sub_str.replace(pos, strlen(NET_UINT1), ODATAWIDTH_1);
            } else {
                sub_str.replace(pos, strlen(NET_UINT1), DATAWIDTH_1);
            }
            fputs(sub_str.c_str(), file_out);
            continue;
        }

        pos = sub_str.find(NET_UINT2);
        if (pos != bad_rc_) {
            if (ofound) {
                sub_str.replace(pos, strlen(NET_UINT1), ODATAWIDTH_2);
            } else {
                sub_str.replace(pos, strlen(NET_UINT2), DATAWIDTH_2);
            }
            fputs(sub_str.c_str(), file_out);
            continue;
        }

        pos = sub_str.find(NET_UINT8);
        if (pos != bad_rc_) {
            if (ofound) {
                sub_str.replace(pos, strlen(NET_UINT8), ODATAWIDTH_8);
            } else {
                sub_str.replace(pos, strlen(NET_UINT8), DATAWIDTH_8);
            }
            fputs(sub_str.c_str(), file_out);
            continue;
        }

        pos = sub_str.find(NET_INT16);
        if (pos != bad_rc_) {
            if (ofound) {
                sub_str.replace(pos, strlen(NET_INT16), ODATAWIDTH_16);
            } else {
                sub_str.replace(pos, strlen(NET_INT16), DATAWIDTH_16);
            }
            fputs(sub_str.c_str(), file_out);
            continue;
        }

        pos = sub_str.find(NET_INT32);
        if (pos != bad_rc_) {
            if (ofound) {
                sub_str.replace(pos, strlen(NET_INT32), ODATAWIDTH_32);
            } else {
                sub_str.replace(pos, strlen(NET_INT32), DATAWIDTH_32);
            }
            fputs(sub_str.c_str(), file_out);
            continue;
        }

        pos = sub_str.find(NET_INT64);
        if (pos != bad_rc_) {
            if (ofound) {
                sub_str.replace(pos, strlen(NET_INT64), ODATAWIDTH_64);
            } else {
                sub_str.replace(pos, strlen(NET_INT64), DATAWIDTH_64);
            }
            fputs(sub_str.c_str(), file_out);
            continue;
        }
        pos = sub_str.find(NET_INT1);
        if (pos != bad_rc_) {
            if (ofound) {
                sub_str.replace(pos, strlen(NET_INT1), ODATAWIDTH_1);
            } else {
                sub_str.replace(pos, strlen(NET_INT1), DATAWIDTH_1);
            }
            fputs(sub_str.c_str(), file_out);
            continue;
        }

        pos = sub_str.find(NET_INT2);
        if (pos != bad_rc_) {
            if (ofound) {
                sub_str.replace(pos, strlen(NET_INT2), ODATAWIDTH_2);
            } else {
                sub_str.replace(pos, strlen(NET_INT2), DATAWIDTH_2);
            }
            fputs(sub_str.c_str(), file_out);
            continue;
        }

        pos = sub_str.find(NET_INT8);
        if (pos != bad_rc_) {
            if (ofound) {
                sub_str.replace(pos, strlen(NET_INT8), ODATAWIDTH_8);
            } else {
                sub_str.replace(pos, strlen(NET_INT8), DATAWIDTH_8);
            }
            fputs(sub_str.c_str(), file_out);
            continue;
        }
    }

    // Part 2.1 Define local states for controller
    string st = "";
    string state_decls = "    localparam WAIT = 0, FINAL = 9999, ";
    string dp_decls = "    reg ";
    string dp_logic = "";
    string dp_op = "";
    string operation = "";
    int state_count = 0;
    int next_cycle = 0;
    bool done = false;
    for (size_t i = 0; i < vertices_.size(); i++) {
        st = "STATE" + to_string(vertices_[i].cycle);
        if (state_decls.find(st) == bad_rc_) {
            state_decls += st + " = " + to_string(vertices_[i].cycle) + ", "; 
            state_count += 1;
        }
    }

    for (size_t i = 0; i < vertices_.size(); i++) {
        string op = vertices_[i].op;
        done = false;

        next_cycle = 1000000;
        for (size_t k = 0; k < vertices_.size(); k++) {
            if (vertices_[i].cycle < vertices_[k].cycle && vertices_[k].cycle < next_cycle) {
                next_cycle = vertices_[k].cycle;
            }
        }

        if (next_cycle == 1000000) {
            next_cycle = vertices_[i].cycle;
            done = true;
        }

        pos = op.find("*");
        if (pos != bad_rc_) {
            dp_op = "mul" + op.substr(pos + 1, op.length());
            dp_decls += dp_op + ", ";
            dp_logic += "        if (" + dp_op + ") begin\n";
           
            for (size_t j = 0; j < operations_.size(); j++) {
                if (operations_[j].find(outputs_[i]) != bad_rc_ && operations_[j].find("Int") == bad_rc_) {
                    operation = operations_[j];
                    operation.replace(0, 4, "");
                    operation.replace(operation.length() - 4, operation.length(), ";\n");
                    dp_logic += "            " + operation;
                    break;
                }
            }

            if (done) {
                dp_logic += "            next_state <= FINAL;\n";
            } else {
                dp_logic += "            next_state <= STATE" + to_string(next_cycle) + ";\n";
            }
            dp_logic += "        end\n";
            continue;
        }

        pos = op.find("/");
        if (pos != bad_rc_) {
            dp_op = "div" + op.substr(pos + 1, op.length());
            dp_decls += dp_op + ", ";
            dp_logic += "        if (" + dp_op + ") begin\n";

            for (size_t j = 0; j < operations_.size(); j++) {
                if (operations_[j].find(outputs_[i]) != bad_rc_ && operations_[j].find("Int") == bad_rc_) {
                    operation = operations_[j];
                    operation.replace(0, 4, "");
                    operation.replace(operation.length() - 4, operation.length(), ";\n");
                    dp_logic += "            " + operation;
                    break;
                }
            }

            if (done) {
                dp_logic += "            next_state <= FINAL;\n";
            } else {
                dp_logic += "            next_state <= STATE" + to_string(next_cycle) + ";\n";
            }

            continue;
        }

        pos = op.find("%");
        if (pos != bad_rc_) {
            dp_op = "div" + op.substr(pos + 1, op.length());
            dp_decls += dp_op + ", ";
            dp_logic += "        if (" + dp_op + ") begin\n";
            for (size_t j = 0; j < operations_.size(); j++) {
                if (operations_[j].find(outputs_[i]) != bad_rc_ && operations_[j].find("Int") == bad_rc_) {
                    operation = operations_[j];
                    operation.replace(0, 4, "");
                    operation.replace(operation.length() - 4, operation.length(), ";\n");
                    dp_logic += "            " + operation;
                    break;
                }
            }

            if (done) {
                dp_logic += "            next_state <= FINAL;\n";
            } else {
                dp_logic += "            next_state <= STATE" + to_string(next_cycle) + ";\n";
            }

            continue;
        }

        if (op.find("<<") != bad_rc_ || op.find(">>") != bad_rc_ || op.find("==") != bad_rc_ || op.find("?") != bad_rc_) {
            dp_op = "alu" + op.substr(2, op.length());
        } else if (op.find("+") != bad_rc_ || op.find("-") != bad_rc_ || op.find("<") != bad_rc_ || op.find(">") != bad_rc_) {
            dp_op = "alu" + op.substr(1, op.length());
        } else {
            dp_op = "alu" + op.substr(op.length() - 1, op.length());
        }

        dp_decls += dp_op + ", ";
        dp_logic += "        if (" + dp_op + ") begin\n";
        for (size_t j = 0; j < operations_.size(); j++) {
            if (operations_[j].find(outputs_[i]) != bad_rc_ && operations_[j].find("Int") == bad_rc_) {
                operation = operations_[j];
                operation.replace(0, 4, "");
                operation.replace(operation.length() - 4, operation.length(), ";\n");
                dp_logic += "            " + operation;
                break;
            }
        }

        if (done) {
            dp_logic += "            next_state <= FINAL;\n";
        } else {
            dp_logic += "            next_state <= STATE" + to_string(next_cycle) + ";\n";
        }
        dp_logic += "        end\n";
    }

    state_decls.replace(state_decls.length() - 2, state_decls.length(), ";\n");
    dp_decls.replace(dp_decls.length() - 2, dp_decls.length(), ";\n");

    fputs(state_decls.c_str(), file_out);
    fputs(dp_decls.c_str(), file_out);

    // Part 2.2 Define reg to hold states and next state
    string state_regs = "    reg[" + to_string(state_count) + ":0] state, next_state;\n";
    fputs(state_regs.c_str(), file_out);

    fputs("\n\n", file_out);

    // Part 3 Create the HLSM 
    // 3.1 Create HLSM datapath
    string tmp_dp_decls = dp_decls.replace(0, 8, "");
    pos = tmp_dp_decls.find(";");
    if (pos != bad_rc_) {
        tmp_dp_decls.replace(pos, pos, "");
    }

    string always_dp = "    always @(clk_en, " + tmp_dp_decls + ") begin\n";
    fputs(STATIC_DP, file_out);
    fputs(always_dp.c_str(), file_out);
    fputs(dp_logic.c_str(), file_out);
    fputs("\n    end\n\n", file_out);

    fputs("    always @(posedge Clk) begin\n", file_out);
    fputs("        clk_en <= 1;\n", file_out);
    fputs("    end\n\n", file_out);

    // 3.2 Create HLSM Controller
    fputs(STATIC_CTRL, file_out);
    fputs("    always @(posedge Start) begin\n", file_out);
    fputs("        if (Rst) begin\n", file_out);
    fputs("            state <= WAIT;\n", file_out);

    string rst_str = "";
    for (size_t i = 0; i < outputs_.size(); i++) {
        rst_str += "            " + outputs_[i] + " <= 0;\n";
    }

    rst_str += "        ";
    for (size_t i = 0; i < var_str.length(); i++) {
        if (var_str[i] == ',') {
            rst_str += "<= 0;\n            ";
        } else if (var_str[i] == '0' || var_str[i] == '1' || var_str[i] == '2' || var_str[i] == '3' ||
                var_str[i] == '4' || var_str[i] == '5' || var_str[i] == '6' || var_str[i] == '7' ||
                var_str[i] == '8' || var_str[i] == '9') {
            // Do nothing
        } else {
            rst_str.push_back(var_str[i]);
        }
    }

    rst_str += "<= 0;\n";

    fputs(rst_str.c_str(), file_out);
    fputs("            Done <= 0;\n", file_out);
    fputs("            clk_en <= 0;\n", file_out);
    fputs("        end else begin\n", file_out);

    int min_cycle = 1;
    for (size_t i = 0; i < vertices_.size(); i++) {
        if (vertices_[i].cycle <=  min_cycle) {
            min_cycle = vertices_[i].cycle;
        }
    }

    string nstate = "            next_state <= STATE" + to_string(min_cycle) + ";\n";
    fputs(nstate.c_str(), file_out);
    fputs("            state <= next_state;\n", file_out);
    fputs("        end\n", file_out);
    fputs("    end\n", file_out);

    fputs("\n", file_out);

    string state = "";
    string operands = "";
    string op = "";
    bool found = false;
    int epos = 0;
    int opos = 0;

    fputs(STATIC_CODEC, file_out);
    fputs("    always @(state) begin\n", file_out);
    fputs("        case (state)\n", file_out);
    fputs("            WAIT: begin\n", file_out);
    fputs("                Done <= 0;\n", file_out);
    fputs("            end\n", file_out);
    fputs("            FINAL: begin\n", file_out);
    fputs("                Done <= 1;\n", file_out);
    fputs("                next_state <= WAIT;\n", file_out);
    fputs("            end\n", file_out);

    for (size_t i = 0; i < vertices_.size(); i++) {
        for (size_t j = 1; j < latency; j++) {
            found = false;
            if (vertices_[i].cycle == j) {
                

                if (found != true) {
                    state = "            STATE" + to_string(vertices_[i].cycle) + ": begin\n";
                    fputs(state.c_str(), file_out);

                    for (size_t k = 0; k < vertices_.size(); k++) {
                        op = vertices_[k].op;
                        if (vertices_[k].cycle == vertices_[i].cycle) {
                            if (op.find("*") != bad_rc_) {
                                dp_op = "mul" + op.substr(1, op.length());
                            } else if (op.find("/") != bad_rc_ || op.find("%") != bad_rc_) {
                                dp_op = "div" + op.substr(1, op.length());
                            } else if (op.find("<<") != bad_rc_ || op.find(">>") != bad_rc_ || op.find("==") != bad_rc_ || op.find("?") != bad_rc_) {
                                dp_op = "alu" + op.substr(2, op.length());
                            } else if (op.find("+") != bad_rc_ || op.find("-") != bad_rc_ || op.find("<") != bad_rc_ || op.find(">") != bad_rc_) {
                                dp_op = "alu" + op.substr(1, op.length());
                            } else {
                                dp_op = "alu" + op.substr(op.length() - 1, op.length());
                            }

                            operation = "                " + dp_op + " <= 1;\n";
                            fputs(operation.c_str(), file_out);
                        } else {
                            if (op.find("*") != bad_rc_) {
                                dp_op = "mul" + op.substr(1, op.length());
                            } else if (op.find("/") != bad_rc_ || op.find("%") != bad_rc_) {
                                dp_op = "div" + op.substr(1, op.length());
                            } else if (op.find("<<") != bad_rc_ || op.find(">>") != bad_rc_ || op.find("==") != bad_rc_ || op.find("?") != bad_rc_) {
                                dp_op = "alu" + op.substr(2, op.length());
                            } else if (op.find("+") != bad_rc_ || op.find("-") != bad_rc_ || op.find("<") != bad_rc_ || op.find(">") != bad_rc_) {
                                dp_op = "alu" + op.substr(1, op.length());
                            } else {
                                dp_op = "alu" + op.substr(op.length() - 1, op.length());
                            }

                            operation = "                " + dp_op + " <= 0;\n";
                            fputs(operation.c_str(), file_out);
                        }
                    }

                    fputs("            end\n", file_out);
                    found = true;
                }
            }
        }
    }

   
    fputs("        endcase\n", file_out);
    fputs(STATIC_END, file_out);
    fputs("\n\n", file_out);
    fputs(STATIC_ENDMODULE, file_out);
}

bool HLSEngine::createFDS(int latency) {
    bool scheduled = false;
    bool mul = false;
    bool div = false;
    int time_to_end = 0;
    int cycle = 0;
    int offset = 0;
    float probs[latency*vertices_.size()];
    float sum_probs[vertices_.size()];
    float quotient;
    float max_force_mul;
    float max_force_div;
    float max_force_alu;
    int pos_mul;
    int pos_alu;
    int pos_div;
    int count_mul = 2;
    int count_div = 3;

    // Start clock to exit
    clock_t start_time = clock() / CLOCKS_PER_SEC;

    while (!scheduled) {
                    
        for (size_t i = 0; i < vertices_.size(); i++) {
            pos_mul = 0;
            pos_div = 0;
            pos_alu = 0;
            offset = 0;
            time_to_end = latency - cycle;
            max_force_mul = -1000000;
            max_force_div = -1000000;
            max_force_alu = -1000000;    

            if (count_mul <= 0) {
                count_mul = 2;
                mul = false;
            } else if (mul) {
                count_mul -= 1;
            }

            if (count_div <= 0) {
                count_div = 3;
            } else if (div) {
                count_div -= 1;
            }
            
            // Step 1- calculate time frame
            calcTimeFrame();

            // Step 2- calculate probabilities
            for (size_t j = time_to_end; j < latency; j++) {
                if (vertices_[i].time_frame[0] <= i && i <= vertices_[i].time_frame[1]) {
                    quotient = 1 / vertices_[i].frame_width;
                    probs[offset + i] = quotient;
                } else {
                    probs[offset + i] = 0;
                }

                sum_probs[j] += probs[offset + i];
            }

            offset += latency;
        }

        offset = 0;

        // Step 3- calculate forces
        // (a) calculate self force
        for (size_t i = 0; i < vertices_.size(); i++) {
            for (size_t j = time_to_end; j < latency; j++) {
                if ((j + 1) > latency) {
                    vertices_[i].force = sum_probs[j] * (1 - probs[offset + i]);
                } else {
                    vertices_[i].force = (sum_probs[j] * (1 - probs[offset + i]) \
                            + sum_probs[j+1] * (0 - probs[offset + i]));
                }
            }

            offset += latency;
        }

        // (b) calculate total force adding predecessor and successor forces
        for (size_t i = 0; i < vertices_.size(); i++) {
            // Sum up successor forces
            for (multimap<Node*, Edge>::iterator it = edges_.lower_bound(&vertices_[i]), 
                end = edges_.upper_bound(&vertices_[i]); it != end; ++it) {
                vertices_[i].force += it->second.vertex->force;
            }

            // Sum up predessor forces
            for (multimap<Node*, Edge>::reverse_iterator it = edges_.rbegin(); it != edges_.rend(); ++it) {
                if (vertices_[i].op == it->second.vertex->op) {
                    vertices_[i].force += it->second.vertex->force;
                }
            }
        }

        // Step 4- schedule operation with the least force 
        cycle += 1;
        scheduled = true;

        for (size_t i = 0; i < vertices_.size(); i++) {
            if (vertices_[i].cycle > 0) {
                continue;
            }

            scheduled = false;

            if (vertices_[i].op.find("*") != bad_rc_) {
                if (max_force_mul < vertices_[i].force) {
                    max_force_mul = vertices_[i].force;
                    pos_mul = i;
                }
            } else if (vertices_[i].op.find("/") != bad_rc_ || vertices_[i].op.find("%") != bad_rc_) {
                if (max_force_div < vertices_[i].force) {
                    max_force_div = vertices_[i].force;
                    pos_div = i;
                }
            } else {
                if (max_force_alu < vertices_[i].force) {
                    max_force_alu = vertices_[i].force;
                    pos_alu = i;
                }
            }
        }

        if (vertices_[pos_mul].cycle == 0 && count_mul == 2 && vertices_[pos_mul].time_frame[0] <= cycle && cycle <= vertices_[pos_mul].time_frame[1]) {
            vertices_[pos_mul].cycle = cycle;
            mul = true;
        } 
        
        if (vertices_[pos_div].cycle == 0 && count_div == 3 && vertices_[pos_div].time_frame[0] <= cycle && cycle <= vertices_[pos_div].time_frame[1]) {
            vertices_[pos_div].cycle = cycle + 1;
            div = true;
        } 
        
        if (vertices_[pos_alu].cycle == 0 && vertices_[pos_alu].time_frame[0] <= cycle && cycle <= vertices_[pos_alu].time_frame[1]) {
            vertices_[pos_alu].cycle = cycle;
        }

        if (time_to_end == 0 && scheduled == false) {
            cycle = 0;
        }

        if ((start_time + 1) < (clock() / CLOCKS_PER_SEC)) {
            // Last minute effort to get these ops scheduled
            for (size_t i = 0; i < vertices_.size(); i++) {
                if (vertices_[i].cycle > 0) {
                    continue;
                } else {
                    vertices_[i].cycle = vertices_[i].asap;
                }
            }
            scheduled = true;
        }
    }

    return true;
}

void HLSEngine::calcTimeFrame() {
    for (size_t i = 0; i < vertices_.size(); i++) {
        // Calculate time frame
        vertices_[i].time_frame[0] = vertices_[i].asap;
        vertices_[i].time_frame[1] = vertices_[i].alap;

        // Calculate frame width
        vertices_[i].frame_width = vertices_[i].alap - vertices_[i].asap + 1; 
    }
}

bool HLSEngine::createALAP(int latency) {
    bool found = false;
    int time = latency;

    for (size_t i = 0; i < vertices_.size(); i++) {
        time = latency;
        found = false;
        string node = vertices_[i].op;

        for (multimap<Node*, Edge>::reverse_iterator it = edges_.rbegin(); it != edges_.rend(); ++it) {
            if (node == it->second.vertex->op && vertices_[i].op != it->first->op) {
                node = it->first->op;
                for (size_t j = 0; j < vertices_.size(); j++) {
                    if (node == vertices_[j].op) {
                        vertices_[j].alap += 1;
                    }
                }
            }
        }

        for (multimap<Node*, Edge>::iterator it = edges_.lower_bound(&vertices_[i]), 
                end = edges_.upper_bound(&vertices_[i]); it != end; ++it) {
            string node = it->second.vertex->op;
            for (size_t j = 0; j < vertices_.size(); j++) {
                if (node == vertices_[j].op) {
                    vertices_[i].alap += 1;
                }
            }
        }
    }

    // Schedule nodes per latency request
    for (size_t i = 0; i < vertices_.size(); i++) {
        vertices_[i].alap = latency - vertices_[i].alap;

        if (vertices_[i].alap < 0) {
            return false;
        }
    }

    return true;
}

bool HLSEngine::createASAP(int latency) {
    bool found = false;
    int time = 0;
    vector<Node> scheduled;

    for (size_t i = 0; i < vertices_.size(); i++) {
        time = 0;
        found = false;
        string node = vertices_[i].op;

        for (multimap<Node*, Edge>::reverse_iterator it = edges_.rbegin(); it != edges_.rend(); ++it) {
            if (node == it->second.vertex->op && vertices_[i].op != it->first->op) {
                time += 1;
                node = it->first->op;
            }
        }

        for (size_t j = 0; j < scheduled.size(); j++) {
            if (scheduled[j].op == vertices_[i].op) {
               found = true; 
               break;
            }
        }

        if (found != true) {
            vertices_[i].asap = time;
            
            if (time > latency) {
                return false;
            }
            scheduled.push_back(vertices_[i]);
        }
    }

    return true;
}

bool HLSEngine::createCDFGExt() {
    // Follow pemdas for priority for scheduling + MISC
    bool trigger = false;
    int found, efound, nfound, vfound, bfound, ifound, ffound, mfound;
    int nnfound, eefound, iifound, fffound, bcfound, lfound;
    string line;
    string output;
    string noutput;
    
    for (size_t i = 0; i < outputs_.size(); i++) {
        output = outputs_[i];
        for (size_t j = 0; j < operations_.size(); j++) {
            line = operations_[j]; 
            found = line.find(output);
            efound = line.find("=");
            ifound = line.find("if");
            ffound = line.find("for");

            if (found != bad_rc_) {
                if ((efound < found && efound != bad_rc_) || (ifound != bad_rc_ || ffound != bad_rc_)) {
                    for (size_t k = i; k < outputs_.size(); k++) {
                        noutput = outputs_[k];
                        nfound = line.find(noutput);

                        if (nfound != bad_rc_ && (nfound < efound || ifound != bad_rc_ || ffound != bad_rc_)) {
                            addEdge(i, k); 
                        } else if (ifound != bad_rc_ || ffound != bad_rc_) {
                            for (size_t l = j; l < operations_.size(); l++) {
                                nnfound = operations_[l].find(noutput);
                                eefound = operations_[l].find("=");
                                iifound = operations_[l].find("if");
                                fffound = operations_[l].find("for");
                                bcfound = operations_[l].find("}");

                                if (nnfound != bad_rc_ && (nnfound < eefound || iifound != bad_rc_ || fffound != bad_rc_)) {
                                    addEdge(i, k);
                                } else if (bcfound != bad_rc_) {
                                    if (l < operations_.size()) {
                                        lfound = operations_[l + 1].find("else");
                                        if (lfound != bad_rc_) {
                                            continue;
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                    }
                } 
            } 
        }
    }

    return true;
}

void HLSEngine::addEdge(size_t i, size_t k) {
    if (vertices_[i].op == vertices_[k].op) {
        return;
    }
                        
    for (multimap<Node*, Edge>::iterator it = edges_.begin(); it != edges_.end(); ++it) {
        if (it->first->op == vertices_[i].op && it->second.vertex->op == vertices_[k].op) {
            return;
        }
    }

    edges_.insert(make_pair(&vertices_[i], Edge(&vertices_[k])));
}

bool HLSEngine::createCDFG(const char* sub_buff, size_t sub_buff_len) {
    // Forward declarations
    string line = "    " + string(sub_buff) + "    ";

    // Pad line with initial white space to help with parsing
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '\n' || line[i] == '\t') {
            line[i] = ' ';
        }
    }

    operations_.push_back(line);
    string str_operands = "";

    // Determine operands
    size_t found = line.find(NET_INT1);
    if (found != bad_rc_) {
       str_operands = line.substr((found + strlen(NET_INT1) + 1), line.length());
    }

    found = line.find(NET_INT2);
    if (found != bad_rc_) {
       str_operands = line.substr((found + strlen(NET_INT2) + 1), line.length());
    }

    found = line.find(NET_INT8);
    if (found != bad_rc_) {
       str_operands = line.substr((found + strlen(NET_INT8) + 1), line.length());
    }

    found = line.find(NET_INT16);
    if (found != bad_rc_) {
       str_operands = line.substr((found + strlen(NET_INT16) + 1), line.length());
    }

    found = line.find(NET_INT32);
    if (found != bad_rc_) {
       str_operands = line.substr((found + strlen(NET_INT32) + 1), line.length());
    }

    found = line.find(NET_INT64);
    if (found != bad_rc_) {
       str_operands = line.substr((found + strlen(NET_INT64) + 1), line.length());
    }

    // Determine output
    string tmp_str = "";
    found = line.find("=");
    if (found != bad_rc_) {
        tmp_str = line.substr(0, (found - 1)); 
    }

    found = line.find("if");
    if (found != bad_rc_) {
        tmp_str = line.substr((found + 4), line.length()); 
    }

    found = line.find("for");
    if (found != bad_rc_) {
        tmp_str = line.substr((found + 4), line.length()); 
    }

    for (size_t i = 0; i < tmp_str.length(); i++) {
        if (tmp_str[i] == ')' || tmp_str[i] == '{') {
            tmp_str[i] = ' ';
        }
    }

    string new_str = "";
    for (size_t i = 0; i < tmp_str.length(); i++) {
        if (isspace(tmp_str[i])) {
            // Do nothing
        } else {
            new_str.push_back(tmp_str[i]); 
        }
    }

    // Underlying assumption is there is a space between and after to differentiate
    // variables from one another (e.g. d and dEQz could result in the same parse
    // otherwise)
    if (new_str.length() > 0) {
        outputs_.push_back(" " + new_str + " ");
    }

    // Split operands string into individual operands
    for (size_t i = 0; i < str_operands.length(); i++) {
        if (str_operands[i] != ',' && str_operands[i] != ' ') {
            tmp_str.push_back(str_operands[i]); 
            if (i == (str_operands.length() - 1)) {
                operands_.push_back(tmp_str);
                tmp_str = "";
            }
        } else {
            if (tmp_str.length() > 0) {
                operands_.push_back(tmp_str);
                tmp_str = "";
            }
        }
    }

    // Find all vertices in sub_buff
    for (size_t i = 0; i < sub_buff_len; i++) {
        string temp = "";
        size_t n = i + 1;
        size_t w = i + 2;
        size_t po = i + 3;
        size_t t = i + 4;
        if (sub_buff[i] == '+' || sub_buff[i] == '-' || sub_buff[i] == '*'
                || sub_buff[i] == '/' || sub_buff[i] == '%' || sub_buff[i] == '?') {
            count_++;
            temp.push_back(sub_buff[i]);
            vertices_.push_back(Node(temp + to_string(count_)));
        } else if (sub_buff[i] == '<' || sub_buff[i] == '>') {
            if (sub_buff[n] == '<') {
                count_++;
                vertices_.push_back(Node("<<" + to_string(count_)));
                i += 1;
            } else if (sub_buff[n] == '>') {
                count_++;
                vertices_.push_back(Node(">>" + to_string(count_)));
                i += 1;
            } else {
                count_++;
                temp.push_back(sub_buff[i]);
                vertices_.push_back(Node(temp + to_string(count_)));
            }
        } else if (sub_buff[i] == '=') { 
            if (sub_buff[n] == '=') {
                count_++;
                vertices_.push_back(Node(Node("==" + to_string(count_))));
            }
        } else if (sub_buff[i] == 'i' && sub_buff[n] == 'f' && sub_buff[w] == ' ' && 
                sub_buff[po] == '(') {
            for (size_t z = t; z < sub_buff_len; z++) {
                if (sub_buff[z] == ' ') {
                    continue;
                } else if (sub_buff[z] == ')') {
                    if (temp.length() == 0) {
                        return false;
                    } 

                    i = z;
                    break;
                } else {
                    temp.push_back(sub_buff[z]);
                }
            }
            count_++;
            vertices_.push_back(Node(" " + temp + " " + to_string(count_)));
        } 
    }

    return true;
}


bool HLSEngine::parseBufferCreateVerilogSrc(char* buff, size_t buff_len, FILE* file_out, int latency) {
    // Forward declarations 
    char* sub_buff;
    size_t sub_buff_len;
    int buff_num = 0;
    int k        = 0; 

    // Create heap space for buffer and clear it
    sub_buff = reinterpret_cast<char*>(malloc((buff_len + 1)*sizeof(char)));
    memset(sub_buff, '\0', buff_len);

    // Parse buffer for behavioral netlist
    for (int i = 0; i < buff_len+1; i++) {
        // Read buffer into substring buffer line by line
        if (buff[i] == '\n' || i == buff_len) {
            for (int j = buff_num; j < i; j++) {
                sub_buff[k] = buff[j];
                k++;
            }

            // Map netlist circuit operation to data path component
            sub_buff_len = i - buff_num;
            if (createCDFG(sub_buff, sub_buff_len) != true) {
                fprintf(stderr, "Failed to parse datapath component\n");
                return false;
            }

            // Set loop elements
            buff_num = i;
            k = 0;

            // Clear sub_buff
            memset(sub_buff, '\0', buff_len);
        } 
    }

    if (createCDFGExt() != true) {
        fprintf(stderr, "Failed to create CDFG... issue with given netlist\n");
        return false;
    }

    if (createASAP(latency) != true) {
        fprintf(stderr, "Failed to create ASAP graph... issue with given latency "\
                "being too small based netlist's total inter-opertaional dependencies exceeding latency time\n");
        return false;
    }

    if (createALAP(latency) != true) {
        fprintf(stderr, "Failed to create ALAP graph... issue with given latency "\
                "being too small based on netlist's total inter-operational total dependencies exceeding latency time\n");
        return false;
    }

    if (createFDS(latency) != true) {
        fprintf(stderr, "Failed to create FDS schedule... issue with given latency "\
                "being too small based on netlist's total inter-operational total dependencies exceeding latency time\n");
        return false;
    }

    /*for (int i = 0; i < vertices_.size(); i++) {
        cout << vertices_[i].op << endl;
    }

    for (int i = 0; i < operands_.size(); i++) {
        cout << operands_[i] << endl;
    }

    for (int i = 0; i < outputs_.size(); i++) {
        cout << outputs_[i] << endl;
    }

    cout << "ALAP TIMES" << endl;
    for (int i = 0; i < vertices_.size(); i++) {
        cout << vertices_[i].op << " " << vertices_[i].alap << endl;
    }

    cout << "ASAP TIMES" << endl;
    for (int i = 0; i < vertices_.size(); i++) {
        cout << vertices_[i].op << " " << vertices_[i].asap << endl;
    }

    cout << "Scheduled cycle from FDS" << endl;
    for (int i = 0; i < vertices_.size(); i++) {
        cout << vertices_[i].op << " " << vertices_[i].cycle << endl;
    }

    cout << "EDGES" << endl;
    for (int i = 0; i < vertices_.size(); i++) {
        for (multimap<Node*, Edge>::iterator it = edges_.lower_bound(&vertices_[i]), 
                end = edges_.upper_bound(&vertices_[i]); it != end; ++it) {
                cout << it->first->op << " " << it->second.vertex->op << endl;
        }
    }*/

    return true;
}

bool HLSEngine::createVerilogSrc(FILE* file_in, FILE* file_out, string v_file, int latency) {
    // Forward declaration
    size_t buff_len;
    char*  buff;
    bool   rc     = true;
    string module;

    // Get size of file by seeking to the end and returning
    fseek(file_in, 0, SEEK_END);
    buff_len = ftell(file_in);

    // Verify buff_len is non_zero
    if (buff_len == 0) {
        fprintf(stderr, "Input file contains no data\n");
        return false;
    }

    // Create heap space for buffer
    buff = reinterpret_cast<char*>(malloc((buff_len + 1)*sizeof(char)));
    memset(buff, '\0', buff_len);

    // Clear buffer
    rewind(file_in);

    // Read buffer
    fread(buff, buff_len, 1, file_in);

    if (strlen(buff) != buff_len) {
        fprintf(stderr, "Failed to read all of the bytes in the file\n");
        return false;
    }

    // Parse buffer and create verilog file
    if (parseBufferCreateVerilogSrc(buff, buff_len, file_out, latency) != false) {
        createHLSM(file_out, latency);
        free(buff);
        return true;
    } else {
        free(buff);
        return false;
    }
}


