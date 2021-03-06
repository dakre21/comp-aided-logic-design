#include "HLSEngine.h"
#include "HLSConstants.h"

HLSEngine::HLSEngine() :

           input_vars_(),
           output_vars_(),
           wire_vars_(),
           reg_vars_(),
           vars_to_dp_(),
           curr_dp_(),
           outputs_(),
           ops_(),
           dp_count_(0),
           bad_rc_(-1) {
    // Do nothing
}

HLSEngine::~HLSEngine() {
    // Do nothing
}

void HLSEngine::setDataPathVars(string* i_var, string* o_var, string* m_var, 
        string* m2_var, string* m3_var, string map_var, string op, const char* dcomp, 
        int npos) {
    // Forward declarations
    int epos   = 0;
    int spos   = 0;

    // Append new line char at the end of the op string
    op += "\n";
    int cpos   = op.find(dcomp);
    int m_size = map_var.size();
    int o_size = op.size();
    int lower  = 0;
    int upper  = 0;
    string low_str;
    string high_str;

    // Determine location of = operator
    epos = op.find(MISC_EQUALS);
    if (epos == bad_rc_) {
        return;
    }

    for (int i = 0; i < o_size; i++) {
        // Determine if variable is valid
        lower = npos - 1;
        if (lower < 0) {
            lower = 0; 
        }

        upper = npos + m_size + 1;
        if (upper >= o_size) {
            upper = o_size;
        }

        low_str = op.substr(lower, 1);
        high_str = op.substr(upper, 1);

        // Check lower bounds
        if (low_str == string(MISC_WHITESPACE) || 
                low_str == dcomp ||
                low_str == string(MISC_SEL) ||
                low_str == string(MISC_EQUALS) ||
                low_str == string(MISC_NEW_LINE) ||
                low_str == string(MISC_NULL) ||
                low_str == string(NET_COMP_LT) ||
                low_str == string(NET_COMP_GT) ||
                low_str == string(NET_ADD) ||
                low_str == string(NET_SUB) ||
                low_str == string(dcomp)) {
            // Do nothing
        } else {
            // Attempt to find sub string in diff location
            op.replace(npos, m_size, "");
            npos = op.find(map_var);
            if (npos != bad_rc_) {
                continue;
            } else {
                return;
            }
        }

        // Check upper bounds
        if (high_str == string(MISC_WHITESPACE) || 
                high_str == dcomp ||
                high_str == string(MISC_SEL) ||
                high_str == string(MISC_EQUALS) ||
                high_str == string(MISC_NEW_LINE) ||
                high_str == string(MISC_NULL) ||
                high_str == string(NET_COMP_LT) ||
                high_str == string(NET_COMP_GT) ||
                high_str == string(NET_ADD) ||
                high_str == string(NET_SUB) ||
                high_str == string(dcomp)) {
            break;
        } else {
            // Attempt to find sub string in diff location
            op.replace(npos, m_size, "");
            npos = op.find(map_var);
            if (npos != bad_rc_) {
                continue;
            } else {
                return;
            }
        }
    }

    // Case for REG
    if (dcomp == NET_REG) {
        if (npos < epos && npos < cpos) {
            *o_var = map_var;
        } else {
            *i_var = map_var;
        }
    
        return;
    }

    // Case for COMP 
    if (dcomp == NET_COMP_GT || dcomp == NET_COMP_LT || dcomp == NET_COMP_EQ) {
        if (npos < epos && npos < cpos) {
            *o_var = map_var;
        } else if (epos < npos && npos < cpos) {
            *i_var = map_var;
        } else {
            *m_var = map_var;
        }
        return;
    }

    // Case for MUX 
    if (dcomp == NET_MUX) {
        spos = op.find(MISC_SEL);
        if (spos != bad_rc_) {
            if (npos < epos && npos < cpos) {
                *m_var = map_var;
            } else if (epos < npos && npos < cpos) {
                *o_var = map_var;
            } else if (npos < spos && cpos < npos) {
                *m2_var = map_var;
            } else {
                *i_var = map_var;
            }
        }

        return;
    }

    // Case for inc/dec
    if (dcomp == NET_INC || dcomp == NET_DEC) {
        if (npos < epos && npos < cpos) {
            *o_var = map_var;
        } else {
            *i_var = map_var;
        }
        return;
    }

    // Case for non-mux/comp/reg/inc/dec
    if (npos < epos && npos < cpos) {
        *o_var = map_var; 
    } else if (cpos < npos) {
        *m_var = map_var;
    } else {
        *i_var = map_var;
    }

}

string HLSEngine::setDataPathComp(string op, string data_width, const char* dcomp) {
    // Forward declaration 
    string v_str = "";
    string w_str = " ";
    int pos      = 0;
    string width;

    // Get position of signed char
    pos = data_width.find("S");

    // Remove signed/unsigned char
    data_width.replace(0, 1, "");

    if (data_width == string(DATAWIDTH_1_STR)) {
        w_str += string(DATAWIDTH_1_INST) + " ";
        width = string(DP_WIDTH_1);
    } else if (data_width == string(DATAWIDTH_2_STR)) {
        w_str += string(DATAWIDTH_2_INST) + " ";
        width = string(DP_WIDTH_2);
    } else if (data_width == string(DATAWIDTH_8_STR)) {
        w_str += string(DATAWIDTH_8_INST) + " ";
        width = string(DP_WIDTH_8);
    } else if (data_width == string(DATAWIDTH_16_STR)) {
        w_str += string(DATAWIDTH_16_INST) + " ";
        width = string(DP_WIDTH_16);
    } else if (data_width == string(DATAWIDTH_32_STR)) {
        w_str += string(DATAWIDTH_32_INST) + " ";
        width = string(DP_WIDTH_32);
    } else {
        w_str += string(DATAWIDTH_64_INST) + " ";
        width = string(DP_WIDTH_64);
    } 

    if (pos != bad_rc_) {
        // Append signed data path component
        if (dcomp == NET_ADD) {
            v_str += MISC_TAB + string(DP_SADD) + w_str + string(DP_SADD_INST);          
            curr_dp_ = string(DP_ADD) + width;
        } else if (dcomp == NET_SUB) {
            v_str += MISC_TAB + string(DP_SSUB) + w_str + string(DP_SSUB_INST);          
            curr_dp_ = string(DP_SUB) + width;
        } else if (dcomp == NET_MUL) {
            v_str += MISC_TAB + string(DP_SMUL) + w_str +  string(DP_SMUL_INST);          
            curr_dp_ = string(DP_MUL) + width;
        } else if (dcomp == NET_DIV) {
            v_str += MISC_TAB + string(DP_SDIV) + w_str + string(DP_SDIV_INST);          
            curr_dp_ = string(DP_DIV) + width;
        } else if (dcomp == NET_MOD) {
            v_str += MISC_TAB + string(DP_SMOD) + w_str + string(DP_SMOD_INST);          
            curr_dp_ = string(DP_MOD) + width;
        } else if (dcomp == NET_COMP_LT || 
                dcomp == NET_COMP_GT || 
                dcomp == NET_COMP_EQ) {
            v_str += MISC_TAB + string(DP_SCOMP) + w_str + string(DP_SCOMP_INST);          
            curr_dp_ = string(DP_COMP) + width;
        } else if (dcomp == NET_SHL) {
            v_str += MISC_TAB + string(DP_SSHL) + w_str + string(DP_SSHL_INST);          
            curr_dp_ = string(DP_SHL) + width;
        } else if (dcomp == NET_SHR) {
            v_str += MISC_TAB + string(DP_SSHR) + w_str + string(DP_SSHR_INST);          
            curr_dp_ = string(DP_SHR) + width;
        } else if (dcomp == NET_REG) {
            v_str += MISC_TAB + string(DP_SREG) + w_str + string(DP_SREG_INST);          
            curr_dp_ = string(DP_REG) + width;
        } else if (dcomp == NET_INC) {
            v_str += MISC_TAB + string(DP_SINC) + w_str + string(DP_SINC_INST);          
            curr_dp_ = string(DP_INC) + width;
        } else if (dcomp == NET_DEC) {
            v_str += MISC_TAB + string(DP_SDEC) + w_str + string(DP_SDEC_INST);          
            curr_dp_ = string(DP_DEC) + width;
        } else if (dcomp == NET_MUX) {
            v_str += MISC_TAB + string(DP_SMUX) + w_str + string(DP_SMUX_INST);          
            curr_dp_ = string(DP_MUX) + width;
        }
    } else {
        // Append signed data path component
        if (dcomp == NET_ADD) {
            v_str += MISC_TAB + string(DP_ADD) + w_str + string(DP_ADD_INST);          
            curr_dp_ = string(DP_ADD) + width;
        } else if (dcomp == NET_SUB) {
            v_str += MISC_TAB + string(DP_SUB) + w_str + string(DP_SUB_INST);          
            curr_dp_ = string(DP_SUB) + width;
        } else if (dcomp == NET_MUL) {
            v_str += MISC_TAB + string(DP_MUL) + w_str + string(DP_MUL_INST);          
            curr_dp_ = string(DP_MUL) + width;
        } else if (dcomp == NET_DIV) {
            v_str += MISC_TAB + string(DP_DIV) + w_str + string(DP_DIV_INST);          
            curr_dp_ = string(DP_DIV) + width;
        } else if (dcomp == NET_MOD) {
            v_str += MISC_TAB + string(DP_MOD) + w_str + string(DP_MOD_INST);          
            curr_dp_ = string(DP_MUX) + width;
        } else if (dcomp == NET_COMP_LT || 
                dcomp == NET_COMP_GT || 
                dcomp == NET_COMP_EQ) {
            v_str += MISC_TAB + string(DP_COMP) + w_str + string(DP_COMP_INST);          
            curr_dp_ = string(DP_COMP) + width;
        } else if (dcomp == NET_SHL) {
            v_str += MISC_TAB + string(DP_SHL) + w_str + string(DP_SHL_INST);          
            curr_dp_ = string(DP_SHL) + width;
        } else if (dcomp == NET_SHR) {
            v_str += MISC_TAB + string(DP_SHR) + w_str + string(DP_SHR_INST);          
            curr_dp_ = string(DP_SHR) + width;
        } else if (dcomp == NET_REG) {
            v_str += MISC_TAB + string(DP_REG) + w_str + string(DP_REG_INST);          
            curr_dp_ = string(DP_REG) + width;
        } else if (dcomp == NET_INC) {
            v_str += MISC_TAB + string(DP_INC) + w_str + string(DP_INC_INST);          
            curr_dp_ = string(DP_INC) + width;
        } else if (dcomp == NET_DEC) {
            v_str += MISC_TAB + string(DP_DEC) + w_str + string(DP_DEC_INST);          
            curr_dp_ = string(DP_DEC) + width;
        } else if (dcomp == NET_MUX) {
            v_str += MISC_TAB + string(DP_MUX) + w_str + string(DP_MUX_INST);          
            curr_dp_ = string(DP_MUX) + width;
        }
    }

    return v_str;
}

bool HLSEngine::dataPathOpToFile(string op, int pos, const char* dcomp, FILE* file_out) {
    // Forward declarations
    int npos = 0;
    string v_str;
    string temp_str;
    string o_var;
    string m_var;
    string m2_var;
    string m3_var;
    string i_var;

    // Get the mapped var sizes
    size_t input_size = input_vars_.size();
    size_t output_size = output_vars_.size();
    size_t wire_size = wire_vars_.size();
    size_t reg_size = reg_vars_.size();

    // Ensure there are appropriate variables being 
    // used in the design
    if (input_size == 0 && output_size == 0 &&
            wire_size == 0 && reg_size == 0) {
        return false;
    }

    // Check for input vars
    for (map<string, string>::iterator it = input_vars_.begin(); it != input_vars_.end(); ++it) {
        npos = op.find(it->first);

        if (npos != bad_rc_) {
            v_str = setDataPathComp(op, it->second, dcomp);
            setDataPathVars(&i_var, &o_var, &m_var, &m2_var, &m3_var, it->first, op, dcomp, npos);
        }

    }

    // Check for output vars
    for (map<string, string>::iterator it = output_vars_.begin(); it != output_vars_.end(); ++it) {
        npos = op.find(it->first);

        if (npos != bad_rc_) {
            v_str = setDataPathComp(op, it->second, dcomp);
            setDataPathVars(&i_var, &o_var, &m_var, &m2_var, &m3_var, it->first, op, dcomp, npos);
        }
    }

    // Check for wire vars
    for (map<string, string>::iterator it = wire_vars_.begin(); it != wire_vars_.end(); ++it) {
        npos = op.find(it->first);

        if (npos != bad_rc_) {
            v_str = setDataPathComp(op, it->second, dcomp);
            setDataPathVars(&i_var, &o_var, &m_var, &m2_var, &m3_var, it->first, op, dcomp, npos);
        }
    }

    // Check for reg vars
    for (map<string, string>::iterator it = reg_vars_.begin(); it != reg_vars_.end(); ++it) {
        npos = op.find(it->first);

        if (npos != bad_rc_) {
            v_str = setDataPathComp(op, it->second, dcomp);
            setDataPathVars(&i_var, &o_var, &m_var, &m2_var, &m3_var, it->first, op, dcomp, npos);
        }
    }

    // Set dp number to string
    v_str += to_string(dp_count_) + "(";
    dp_count_++;

    if (i_var == "" || o_var == "") {
        return false;
    }

    if (dcomp == NET_MUX) {
        if (m2_var == "" || m_var == "") {
            return false;
        }
        v_str += i_var + ", " + m2_var + ", " + m_var + ", " + o_var + ")" + string(MISC_LINE_END);
    } else if (dcomp == NET_REG) {
        v_str += i_var + ", " + o_var + ", " + string(DP_CLK) + ", " + string(DP_RST) + ")" + string(MISC_LINE_END);
    } else if (dcomp == NET_COMP_LT) {
        if (m_var == "") {
            return false;
        }
        v_str += i_var + ", " + m_var + ", " + string(GTZ) + ", " + o_var + ", " + string(EQZ) + ")" + string(MISC_LINE_END);
    } else if (dcomp == NET_COMP_GT) {
        if (m_var == "") {
            return false;
        }
        v_str += i_var + ", " + m_var + ", " + o_var + ", " + string(LTZ) + ", " + string(EQZ) + ")" + string(MISC_LINE_END);
    } else if (dcomp == NET_COMP_EQ) {
        if (m_var == "") {
            return false;
        }
        v_str += i_var + ", " + m_var + ", " + string(GTZ) + ", " + string(LTZ) + ", " + o_var + ")" + string(MISC_LINE_END);
    } else if (dcomp == NET_INC || dcomp == NET_DEC) {
        v_str += i_var + ", " + o_var + ")" + string(MISC_LINE_END);   
    } else {
        if (m_var == "") {
            return false;
        }
        v_str += i_var + ", " + m_var + ", " + o_var + ")" + string(MISC_LINE_END);
    }

    // Append mapped_var to vars_to_dp_
    if (i_var != "") {
        vars_to_dp_.insert(pair<string, string>(i_var, curr_dp_));
    }

    if (m_var != "") {
        vars_to_dp_.insert(pair<string, string>(m_var, curr_dp_));
    }

    if (m2_var != "") {
        vars_to_dp_.insert(pair<string, string>(m2_var, curr_dp_));
    }
   
    if (m3_var != "") {
        vars_to_dp_.insert(pair<string, string>(m3_var, curr_dp_));
    }

    if (o_var != "") {
        curr_dp_ = "O_" + curr_dp_;
        vars_to_dp_.insert(pair<string, string>(o_var, curr_dp_));
    }

    ops_.push_back(v_str);
    outputs_.push_back(o_var);

    // Write this str to file
    fputs(v_str.c_str(), file_out);

    return true;
}

bool HLSEngine::mapNetOpToDataPathComp(char* sub_buff, size_t sub_buff_len, FILE* file_out) {
    // Forward declarations
    string sub_str     = string(sub_buff);
    string temp_str    = string(sub_buff);
    string decl_str    = string(MISC_TAB);
    size_t pos         = 0;
    size_t tmp_pos     = 0;
    bool   dtype_found = false;
    int    begin       = 0;
    bool   is_input    = false;
    bool   is_output   = false;
    bool   is_wire     = false;
    bool   is_reg      = false;
    string temp_var;
    string data_width;

    // Attempt to find data type & data width
    pos = sub_str.find(NET_UINT16);
    if (pos != bad_rc_ && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, strlen(NET_UINT16), DATAWIDTH_16);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_16);
        data_width = "U16";
    }

    pos = sub_str.find(NET_UINT32);
    if (pos != bad_rc_ && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, strlen(NET_UINT32), DATAWIDTH_32);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_32);
        data_width = "U32";
    }

    pos = sub_str.find(NET_UINT64);
    if (pos != bad_rc_ && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, strlen(NET_UINT64), DATAWIDTH_64);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_64);
        data_width = "U64";
    }

    pos = sub_str.find(NET_UINT1);
    if (pos != bad_rc_ && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, strlen(NET_UINT1), DATAWIDTH_1);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_1);
        data_width = "U1";
    }

    pos = sub_str.find(NET_UINT2);
    if (pos != bad_rc_ && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, strlen(NET_UINT2), DATAWIDTH_2);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_2);
        data_width = "U2";
    }

    pos = sub_str.find(NET_UINT8);
    if (pos != bad_rc_ && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, strlen(NET_UINT8), DATAWIDTH_8);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_8);
        data_width = "U8";
    }

    pos = sub_str.find(NET_INT16);
    if (pos != bad_rc_ && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, strlen(NET_INT16), DATAWIDTH_16);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_16);
        data_width = "S16";
    }

    pos = sub_str.find(NET_INT32);
    if (pos != bad_rc_ && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, strlen(NET_INT32), DATAWIDTH_32);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_32);
        data_width = "S32";
    }

    pos = sub_str.find(NET_INT64);
    if (pos != bad_rc_ && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, strlen(NET_INT64), DATAWIDTH_64);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_64);
        data_width = "S64";
    }

    pos = sub_str.find(NET_INT1);
    if (pos != bad_rc_ && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, strlen(NET_INT1), DATAWIDTH_1);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_1);
        data_width = "S1";
    }

    pos = sub_str.find(NET_INT2);
    if (pos != bad_rc_ && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, strlen(NET_INT2), DATAWIDTH_2);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_2);
        data_width = "S2";
    }

    pos = sub_str.find(NET_INT8);
    if (pos != bad_rc_ && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, strlen(NET_INT8), DATAWIDTH_8);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_8);
        data_width = "S8";
    }

    // Attempt to find either register or wire declaration
    // If there is a match, map the variable with the respective length
    if (dtype_found == true) {
        string var_str = sub_str.substr(temp_str.length(), sub_str.length());

        while (true) {
            pos = var_str.find(MISC_COMMA);
            
            if (pos == -1) {
                break;
            }

            var_str.replace(pos, 1, "");
        }

        pos = sub_str.find(NET_REGISTER);
        if (pos != bad_rc_) {
            sub_str.replace(pos, strlen(NET_REGISTER), NET_REGW);
            pos = sub_str.find(MISC_LINE_END);
            if (pos == bad_rc_) {
                sub_str += MISC_LINE_END;
            }
            is_reg = true;
        }

        pos = sub_str.find(NET_WIRE);
        if (pos != bad_rc_) {
            pos = sub_str.find(MISC_LINE_END);
            if (pos == bad_rc_) {
                sub_str += MISC_LINE_END;
            }
            is_wire = true;
        }

        pos = sub_str.find(NET_INPUT);
        if (pos != bad_rc_) {
            pos = sub_str.find(MISC_LINE_END);
            if (pos == bad_rc_) {
                sub_str += MISC_LINE_END;
            }
            is_input = true;
        }

        pos = sub_str.find(NET_OUTPUT);
        if (pos != bad_rc_) {
            pos = sub_str.find(MISC_LINE_END);
            if (pos == bad_rc_) {
                sub_str += MISC_LINE_END;
            }
            is_output = true;
        }

        while (true) {
            pos = var_str.find(MISC_WHITESPACE);

            if (pos == -1 && var_str.length() == 0) {
                break;
            }

            if (pos == 0) {
                var_str.replace(0, 1, ""); 
                continue;
            }
           
            temp_var = var_str.substr(0, pos);
            
            if (is_input == true) {
                input_vars_.insert(make_pair(temp_var, data_width));
            } else if (is_output == true) {
                output_vars_.insert(make_pair(temp_var, data_width));
            } else if (is_wire == true) {
                wire_vars_.insert(make_pair(temp_var, data_width));
            } else {
                reg_vars_.insert(make_pair(temp_var, data_width));
            }
            
            var_str.replace(0, pos, "");
        }

        // Remove initial new line char
        pos = sub_str.find(MISC_NEW_LINE);
        if (pos == 0) {
            sub_str.replace(0, 1, "");
        }

        // Write string to file
        decl_str += sub_str + string(MISC_NEW_LINE);
        fputs(decl_str.c_str(), file_out);

        return true;
    }

    // Attempt to find data path components 
    pos = sub_str.find(NET_INC);
    if (pos != bad_rc_) {
        return dataPathOpToFile(sub_str, pos, NET_INC, file_out);
    }

    pos = sub_str.find(NET_DEC);
    if (pos != bad_rc_) {
        return dataPathOpToFile(sub_str, pos, NET_DEC, file_out);
    }
    
    pos = sub_str.find(NET_SHL);
    if (pos != bad_rc_) {
        return dataPathOpToFile(sub_str, pos, NET_SHL, file_out);
    }

    pos = sub_str.find(NET_SHR);
    if (pos != bad_rc_) {
        return dataPathOpToFile(sub_str, pos, NET_SHR, file_out);
    }

    pos = sub_str.find(NET_ADD);
    if (pos != bad_rc_) {
        return dataPathOpToFile(sub_str, pos, NET_ADD, file_out);
    }

    pos = sub_str.find(NET_SUB);
    if (pos != bad_rc_) {
        return dataPathOpToFile(sub_str, pos, NET_SUB, file_out);
    }

    pos = sub_str.find(NET_MUL);
    if (pos != bad_rc_) {
        return dataPathOpToFile(sub_str, pos, NET_MUL, file_out);
    }

    pos = sub_str.find(NET_DIV);
    if (pos != bad_rc_) {
        return dataPathOpToFile(sub_str, pos, NET_DIV, file_out);
    }

    pos = sub_str.find(NET_MOD);
    if (pos != bad_rc_) {
        return dataPathOpToFile(sub_str, pos, NET_MOD, file_out);
    }

    pos = sub_str.find(NET_COMP_LT);
    if (pos != bad_rc_) {
        return dataPathOpToFile(sub_str, pos, NET_COMP_LT, file_out);
    }

    pos = sub_str.find(NET_COMP_GT);
    if (pos != bad_rc_) {
        return dataPathOpToFile(sub_str, pos, NET_COMP_GT, file_out);
    }

    pos = sub_str.find(NET_COMP_EQ);
    if (pos != bad_rc_) {
        return dataPathOpToFile(sub_str, pos, NET_COMP_EQ, file_out);
    }

    pos = sub_str.find(NET_MUX);
    if (pos != bad_rc_) {
        return dataPathOpToFile(sub_str, pos, NET_MUX, file_out);
    }

    pos = sub_str.find(NET_REG);
    if (pos != bad_rc_) {
        return dataPathOpToFile(sub_str, pos, NET_REG, file_out);
    }

    // Check if the only contents on the line is either a comment or new line
    pos = sub_str.find(MISC_COMMENT);
    if (pos != bad_rc_) {
        tmp_pos = sub_str.find_first_not_of(MISC_WHITESPACE);
        if (tmp_pos == pos) {
            return true;
        }
    } else {
        pos = sub_str.find(MISC_NEW_LINE);
        if (pos == 0) {
            return true;
        }
    }

    return false;
}

bool HLSEngine::parseBufferCreateVerilogSrc(char* buff, size_t buff_len, FILE* file_out) {
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
            if (mapNetOpToDataPathComp(sub_buff, sub_buff_len, file_out) != true) {
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

    return true;
}

bool HLSEngine::createVerilogSrc(FILE* file_in, FILE* file_out, string v_file) {
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

    // Set initial buffer to file with null chars
    for (int i = 0; i < 255; i++) {
        fputs(STATIC_NULL, file_out);
    }

    // Write initial stuff for verilog code
    fputs(STATIC_COMMENT, file_out);

    // Write static regs & wires
    fputs(STATIC_REGS, file_out);
    fputs(STATIC_WIRES, file_out);

    // Write starting clock info
    fputs(STATIC_ALWAYS, file_out);
    fputs(STATIC_CLK_START, file_out);

    if (strlen(buff) != buff_len) {
        fprintf(stderr, "Failed to read all of the bytes in the file\n");
        return false;
    }

    // Parse buffer and create verilog file
    rc &= parseBufferCreateVerilogSrc(buff, buff_len, file_out);
    free(buff);

    if (rc != false) {
        module = string(STATIC_MODULE) + v_file.replace(v_file.size()-2, v_file.size(), "") + "(";

        // Write end module
        fputs(STATIC_ENDMODULE, file_out);

        // Write module to first line
        fseek(file_out, 0, SEEK_SET);

        for (map<string, string>::iterator it = input_vars_.begin(); it != input_vars_.end(); ++it) {
            module += it->first + ", ";
        }
        
        for (map<string, string>::iterator it = output_vars_.begin(); it != output_vars_.end(); ++it) {
            module += it->first + ", ";
        }

        module.replace(module.size()-2, module.size(), ");\n");
    } else {
        return false;
    }

    // Write timing signal
    fputs(STATIC_TIMING, file_out);

    // Write module
    fputs(module.c_str(), file_out);

    return true;
}

float HLSEngine::calcDpLatency(string dcomp) {
    // Forward declaration
    float latency = 0.0;

    // Find data path component and return latency
    if (dcomp == ((string(DP_REG) + string(DP_WIDTH_1)))) {
        latency = DP_REG_1;
    } else if (dcomp == ((string(DP_REG) + string(DP_WIDTH_2)))) {
        latency = DP_REG_2;
    } else if (dcomp == ((string(DP_REG) + string(DP_WIDTH_8)))) {
        latency = DP_REG_8;
    } else if (dcomp == ((string(DP_REG) + string(DP_WIDTH_16)))) {
        latency = DP_REG_16;
    } else if (dcomp == ((string(DP_REG) + string(DP_WIDTH_32)))) {
        latency = DP_REG_32;
    } else if (dcomp == ((string(DP_REG) + string(DP_WIDTH_64)))) {
        latency = DP_REG_64;
    } else if (dcomp == ((string(DP_ADD) + string(DP_WIDTH_1)))) {
        latency = DP_ADD_1;
    } else if (dcomp == ((string(DP_ADD) + string(DP_WIDTH_2)))) {
        latency = DP_ADD_2;
    } else if (dcomp == ((string(DP_ADD) + string(DP_WIDTH_8)))) {
        latency = DP_ADD_8;
    } else if (dcomp == ((string(DP_ADD) + string(DP_WIDTH_16)))) {
        latency = DP_ADD_16;
    } else if (dcomp == ((string(DP_ADD) + string(DP_WIDTH_32)))) {
        latency = DP_ADD_32;
    } else if (dcomp == ((string(DP_ADD) + string(DP_WIDTH_64)))) {
        latency = DP_ADD_64;
    } else if (dcomp == ((string(DP_SUB) + string(DP_WIDTH_1)))) {
        latency = DP_SUB_1;
    } else if (dcomp == ((string(DP_SUB) + string(DP_WIDTH_2)))) {
        latency = DP_SUB_2;
    } else if (dcomp == ((string(DP_SUB) + string(DP_WIDTH_8)))) {
        latency = DP_SUB_8;
    } else if (dcomp == ((string(DP_SUB) + string(DP_WIDTH_16)))) {
        latency = DP_SUB_16;
    } else if (dcomp == ((string(DP_SUB) + string(DP_WIDTH_32)))) {
        latency = DP_SUB_32;
    } else if (dcomp == ((string(DP_SUB) + string(DP_WIDTH_64)))) {
        latency = DP_SUB_64;
    } else if (dcomp == ((string(DP_MUL) + string(DP_WIDTH_1)))) {
        latency = DP_MUL_1;
    } else if (dcomp == ((string(DP_MUL) + string(DP_WIDTH_2)))) {
        latency = DP_MUL_2;
    } else if (dcomp == ((string(DP_MUL) + string(DP_WIDTH_8)))) {
        latency = DP_MUL_8;
    } else if (dcomp == ((string(DP_MUL) + string(DP_WIDTH_16)))) {
        latency = DP_MUL_16;
    } else if (dcomp == ((string(DP_MUL) + string(DP_WIDTH_32)))) {
        latency = DP_MUL_32;
    } else if (dcomp == ((string(DP_MUL) + string(DP_WIDTH_64)))) {
        latency = DP_MUL_64;
    } else if (dcomp == ((string(DP_COMP) + string(DP_WIDTH_1)))) {
        latency = DP_COMP_1;
    } else if (dcomp == ((string(DP_COMP) + string(DP_WIDTH_2)))) {
        latency = DP_COMP_2;
    } else if (dcomp == ((string(DP_COMP) + string(DP_WIDTH_8)))) {
        latency = DP_COMP_8;
    } else if (dcomp == ((string(DP_COMP) + string(DP_WIDTH_16)))) {
        latency = DP_COMP_16;
    } else if (dcomp == ((string(DP_COMP) + string(DP_WIDTH_32)))) {
        latency = DP_COMP_32;
    } else if (dcomp == ((string(DP_COMP) + string(DP_WIDTH_64)))) {
        latency = DP_COMP_64;
    } else if (dcomp == ((string(DP_MUX) + string(DP_WIDTH_1)))) {
        latency = DP_MUX2x1_1;
    } else if (dcomp == ((string(DP_MUX) + string(DP_WIDTH_2)))) {
        latency = DP_MUX2x1_2;
    } else if (dcomp == ((string(DP_MUX) + string(DP_WIDTH_8)))) {
        latency = DP_MUX2x1_8;
    } else if (dcomp == ((string(DP_MUX) + string(DP_WIDTH_16)))) {
        latency = DP_MUX2x1_16;
    } else if (dcomp == ((string(DP_MUX) + string(DP_WIDTH_32)))) {
        latency = DP_MUX2x1_32;
    } else if (dcomp == ((string(DP_MUX) + string(DP_WIDTH_64)))) {
        latency = DP_MUX2x1_64;
    } else if (dcomp == ((string(DP_SHR) + string(DP_WIDTH_1)))) {
        latency = DP_SHR_1;
    } else if (dcomp == ((string(DP_SHR) + string(DP_WIDTH_2)))) {
        latency = DP_SHR_2;
    } else if (dcomp == ((string(DP_SHR) + string(DP_WIDTH_8)))) {
        latency = DP_SHR_8;
    } else if (dcomp == ((string(DP_SHR) + string(DP_WIDTH_16)))) {
        latency = DP_SHR_16;
    } else if (dcomp == ((string(DP_SHR) + string(DP_WIDTH_32)))) {
        latency = DP_SHR_32;
    } else if (dcomp == ((string(DP_SHR) + string(DP_WIDTH_64)))) {
        latency = DP_SHR_64;
    } else if (dcomp == ((string(DP_SHL) + string(DP_WIDTH_1)))) {
        latency = DP_SHL_1;
    } else if (dcomp == ((string(DP_SHL) + string(DP_WIDTH_2)))) {
        latency = DP_SHL_2;
    } else if (dcomp == ((string(DP_SHL) + string(DP_WIDTH_8)))) {
        latency = DP_SHL_8;
    } else if (dcomp == ((string(DP_SHL) + string(DP_WIDTH_16)))) {
        latency = DP_SHL_16;
    } else if (dcomp == ((string(DP_SHL) + string(DP_WIDTH_32)))) {
        latency = DP_SHL_32;
    } else if (dcomp == ((string(DP_SHL) + string(DP_WIDTH_64)))) {
        latency = DP_SHL_64;
    } else if (dcomp == ((string(DP_DIV) + string(DP_WIDTH_1)))) {
        latency = DP_DIV_1;
    } else if (dcomp == ((string(DP_DIV) + string(DP_WIDTH_2)))) {
        latency = DP_DIV_2;
    } else if (dcomp == ((string(DP_DIV) + string(DP_WIDTH_8)))) {
        latency = DP_DIV_8;
    } else if (dcomp == ((string(DP_DIV) + string(DP_WIDTH_16)))) {
        latency = DP_DIV_16;
    } else if (dcomp == ((string(DP_DIV) + string(DP_WIDTH_32)))) {
        latency = DP_DIV_32;
    } else if (dcomp == ((string(DP_DIV) + string(DP_WIDTH_64)))) {
        latency = DP_DIV_64;
    } else if (dcomp == ((string(DP_MOD) + string(DP_WIDTH_1)))) {
        latency = DP_MOD_1;
    } else if (dcomp == ((string(DP_MOD) + string(DP_WIDTH_2)))) {
        latency = DP_MOD_2;
    } else if (dcomp == ((string(DP_MOD) + string(DP_WIDTH_8)))) {
        latency = DP_MOD_8;
    } else if (dcomp == ((string(DP_MOD) + string(DP_WIDTH_16)))) {
        latency = DP_MOD_16;
    } else if (dcomp == ((string(DP_MOD) + string(DP_WIDTH_32)))) {
        latency = DP_MOD_32;
    } else if (dcomp == ((string(DP_MOD) + string(DP_WIDTH_64)))) {
        latency = DP_MOD_64;
    } else if (dcomp == ((string(DP_INC) + string(DP_WIDTH_1)))) {
        latency = DP_INC_1;
    } else if (dcomp == ((string(DP_INC) + string(DP_WIDTH_2)))) {
        latency = DP_INC_2;
    } else if (dcomp == ((string(DP_INC) + string(DP_WIDTH_8)))) {
        latency = DP_INC_8;
    } else if (dcomp == ((string(DP_INC) + string(DP_WIDTH_16)))) {
        latency = DP_INC_16;
    } else if (dcomp == ((string(DP_INC) + string(DP_WIDTH_32)))) {
        latency = DP_INC_32;
    } else if (dcomp == ((string(DP_INC) + string(DP_WIDTH_64)))) {
        latency = DP_INC_64;
    } else if (dcomp == ((string(DP_DEC) + string(DP_WIDTH_1)))) {
        latency = DP_DEC_1;
    } else if (dcomp == ((string(DP_DEC) + string(DP_WIDTH_2)))) {
        latency = DP_DEC_2;
    } else if (dcomp == ((string(DP_DEC) + string(DP_WIDTH_8)))) {
        latency = DP_DEC_8;
    } else if (dcomp == ((string(DP_DEC) + string(DP_WIDTH_16)))) {
        latency = DP_DEC_16;
    } else if (dcomp == ((string(DP_DEC) + string(DP_WIDTH_32)))) {
        latency = DP_DEC_32;
    } else if (dcomp == ((string(DP_DEC) + string(DP_WIDTH_64)))) {
        latency = DP_DEC_64;
    }

    return latency;
}

float HLSEngine::findCriticalPath(FILE* file_in, FILE* file_out) {
    // Forward declarations
    float cp    = 0.0;
    float tcp   = 0.0;
    float itcp  = 0.0;
    float itcp2 = 0.0;
    float itcp3 = 0.0;
    int count   = 0;
    int pos     = 0;
    string var  = "";
    string prev_output = "";
    string prev_output2 = "";
    bool begin  = false;
    bool found  = false;
    bool found2 = false;

    int size = vars_to_dp_.size();
    int size_ops = ops_.size()-1;

    for (int i = 0; i < size; i++) {
        for (int x = size_ops; x > 0; x--) {
            for (multimap<string, string>::iterator it = vars_to_dp_.begin(); it != vars_to_dp_.end(); it++) {
                // Reset count & tcp if the current var doesn't equal previous
                if (count == 0) {
                    begin = true;
                    found = false;
                    found2 = false;
                    var = it->first;
                    itcp3 = tcp;
                    prev_output = prev_output2;

                    // Re-init variables
                    count = 0;
                    tcp = 0;
                    itcp = 0;
                    itcp2 = 0;
                }

                if (var == it->first) {
                    // Attempt to find an output variable if so sum current tcp with its latency
                    // Otherwise find longest latency of input variable
                    pos = it->second.find("O_");
                    if (pos != bad_rc_) {
                        it->second.replace(pos, 2, "");
                        tcp += calcDpLatency(it->second);
                        prev_output2 = it->first;

                        // This is checking the chaining/edges of previous nodes 
                        // with the current node's output
                        if (found2 != true) {
                            if (prev_output != prev_output2) {
                                for (int x = size_ops; x > 0; x--) {
                                    pos = ops_[x].find(prev_output);
                                    if (pos != bad_rc_) {
                                        pos = ops_[x].find(prev_output2);
                                        if (pos != bad_rc_) {
                                            if (outputs_[x] == prev_output2) {
                                                tcp += itcp3;
                                                found2 = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        found = true;
                    } else {
                        if (found == true) {
                            itcp2 = calcDpLatency(it->second);
                            if (itcp < itcp2) {
                                itcp = itcp2;
                            }
                        }
                    }

                    vars_to_dp_.erase(it);
                    count++;
                } else {
                    break;
                }

            }

            if (begin == true) {
                // Set temp to final critical path if its greater
                if (cp < tcp) {
                    cp = tcp;
                }

                // Reset count
                count = 0;
                begin = false;
            }
        }
    }

    return cp;
}
