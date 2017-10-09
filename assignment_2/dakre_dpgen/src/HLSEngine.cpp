#include "HLSEngine.h"
#include "HLSConstants.h"

HLSEngine::HLSEngine() {
    // Do nothing
}

HLSEngine::~HLSEngine() {
    // Do nothing
}

bool HLSEngine::mapNetOpToDataPathComp(char* sub_buff, size_t sub_buff_len) {
    // Forward declarations
    string sub_str     = string(sub_buff);
    string temp_str    = string(sub_buff);
    size_t pos         = 0;
    size_t tmp_pos     = 0;
    bool   dtype_found = false;
    int    bad_rc      = -1;

    // TODO: Create relationship between data type & data width with vars used in data path components
    // TODO: Write data path component to verilog file (signed or unsigned based on data type)    

    // Attempt to find data type & data width
    pos = sub_str.find(NET_UINT16);
    if (pos != bad_rc && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, string(NET_INT16).length(), DATAWIDTH_16);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_16);
    }

    pos = sub_str.find(NET_UINT32);
    if (pos != bad_rc && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, string(NET_INT32).length(), DATAWIDTH_32);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_32);
    }

    pos = sub_str.find(NET_UINT64);
    if (pos != bad_rc && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, string(NET_INT64).length(), DATAWIDTH_64);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_64);
    }

    pos = sub_str.find(NET_UINT1);
    if (pos != bad_rc && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, string(NET_INT1).length(), DATAWIDTH_1);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_1);
    }

    pos = sub_str.find(NET_UINT2);
    if (pos != bad_rc && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, string(NET_INT2).length(), DATAWIDTH_2);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_2);
    }

    pos = sub_str.find(NET_UINT8);
    if (pos != bad_rc && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, string(NET_INT8).length(), DATAWIDTH_8);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_8);
    }

    pos = sub_str.find(NET_INT16);
    if (pos != bad_rc && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, string(NET_INT16).length(), DATAWIDTH_16);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_16);
    }

    pos = sub_str.find(NET_INT32);
    if (pos != bad_rc && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, string(NET_INT32).length(), DATAWIDTH_32);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_32);
    }

    pos = sub_str.find(NET_INT64);
    if (pos != bad_rc && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, string(NET_INT64).length(), DATAWIDTH_64);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_64);
    }

    pos = sub_str.find(NET_INT1);
    if (pos != bad_rc && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, string(NET_INT1).length(), DATAWIDTH_1);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_1);
    }

    pos = sub_str.find(NET_INT2);
    if (pos != bad_rc && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, string(NET_INT2).length(), DATAWIDTH_2);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_2);
    }

    pos = sub_str.find(NET_INT8);
    if (pos != bad_rc && dtype_found != true) {
        dtype_found = true;
        sub_str.replace(pos, string(NET_INT8).length(), DATAWIDTH_8);
        temp_str.replace(pos, temp_str.length(), DATAWIDTH_8);
    }

    // Attempt to find either register or wire declaration
    // If there is a match, map the variable with the respective length
    if (dtype_found == true) {
        string var_str = sub_str.substr(temp_str.length(), sub_str.length());
        cout << var_str << endl;

        pos = sub_str.find(NET_REGISTER);
        if (pos != bad_rc) {
            pos = sub_str.find(MISC_LINE_END);
            if (pos == bad_rc) {
                sub_str += MISC_LINE_END;
            }
        }

        pos = sub_str.find(NET_WIRE);
        if (pos != bad_rc) {
            pos = sub_str.find(MISC_LINE_END);
            if (pos == bad_rc) {
                sub_str += MISC_LINE_END;
            }
        }

        pos = sub_str.find(NET_INPUT);
        if (pos != bad_rc) {
            pos = sub_str.find(MISC_LINE_END);
            if (pos == bad_rc) {
                sub_str += MISC_LINE_END;
            }
        }

        pos = sub_str.find(NET_OUTPUT);
        if (pos != bad_rc) {
            pos = sub_str.find(MISC_LINE_END);
            if (pos == bad_rc) {
                sub_str += MISC_LINE_END;
            }
        }

        //cout << sub_str;
        return true;
    }

    cout << sub_str;

    // TODO: Set the components below
    // Attempt to find data path components 
    pos = sub_str.find(NET_INC);
    if (pos != bad_rc) {
        return true;
    }

    pos = sub_str.find(NET_DEC);
    if (pos != bad_rc) {
        return true;
    }
    
    pos = sub_str.find(NET_SHL);
    if (pos != bad_rc) {
        return true;
    }

    pos = sub_str.find(NET_SHR);
    if (pos != bad_rc) {
        return true;
    }

    pos = sub_str.find(NET_ADD);
    if (pos != bad_rc) {
        return true;
    }

    pos = sub_str.find(NET_SUB);
    if (pos != bad_rc) {
        return true;
    }

    pos = sub_str.find(NET_MUL);
    if (pos != bad_rc) {
        return true;
    }

    pos = sub_str.find(NET_DIV);
    if (pos != bad_rc) {
        return true;
    }

    pos = sub_str.find(NET_MOD);
    if (pos != bad_rc) {
        return true;
    }

    pos = sub_str.find(NET_COMP_LT);
    if (pos != bad_rc) {
        return true;
    }

    pos = sub_str.find(NET_COMP_GT);
    if (pos != bad_rc) {
        return true;
    }

    pos = sub_str.find(NET_COMP_EQ);
    if (pos != bad_rc) {
        return true;
    }

    pos = sub_str.find(NET_MUX);
    if (pos != bad_rc) {
        return true;
    }

    pos = sub_str.find(NET_REG);
    if (pos != bad_rc) {
        return true;
    }

    // Check if the only contents on the line is either a comment or new line
    pos = sub_str.find(MISC_COMMENT);
    if (pos != bad_rc) {
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

void HLSEngine::parseBufferCreateVerilogSrc(char* buff, size_t buff_len) {
    // Forward declarations 
    char* sub_buff;
    size_t sub_buff_len;
    int buff_num = 0;
    int k        = 0; 

    // Create heap space for buffer and clear it
    sub_buff = reinterpret_cast<char*>(malloc((buff_len + 1)*sizeof(char)));
    memset(sub_buff, '\0', buff_len);

    // Parse buffer for behavioral netlist
    for (int i = 0; i < buff_len; i++) {
        // Read buffer into substring buffer line by line
        if (buff[i] == '\n') {
            for (int j = buff_num; j < i; j++) {
                sub_buff[k] = buff[j];
                k++;
            }

            // Map netlist circuit operation to data path component
            sub_buff_len = i - buff_num;
            if (mapNetOpToDataPathComp(sub_buff, sub_buff_len) != true) {
                fprintf(stderr, "Failed to parse datapath component\n");
                return;
            }

            // Set loop elements
            buff_num = i;
            k = 0;

            // Clear sub_buff
            memset(sub_buff, '\0', buff_len);
        } 
    }
}

bool HLSEngine::createVerilogSrc(FILE* file_in, FILE* file_out) {
    // Forward declaration
    size_t buff_len;
    char*  buff;

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
    parseBufferCreateVerilogSrc(buff, buff_len);
    free(buff);

    return true;
}

float HLSEngine::findCriticalPath(FILE* file_in, FILE* file_out) {
    // TODO: Implement
    return 0.0;
}
