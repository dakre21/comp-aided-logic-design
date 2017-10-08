#include "HLSEngine.h"
#include "HLSConstants.h"

HLSEngine::HLSEngine() {
    // Do nothing
}

HLSEngine::~HLSEngine() {
    // Do nothing
}

void HLSEngine::mapNetOpToDataPathComp(char* sub_buff, size_t sub_buff_len) {
    // Forward declarations
    string sub_str = string(sub_buff);
    size_t pos     = 0;

    // TODO: Create relationship between data type & data width with vars used in data path components
    // TODO: Write data path component to verilog file (signed or unsigned based on data type)    
    
    // Attempt to find either register or wire declaration
    pos = sub_str.find(NET_REGISTER);
    if (pos != 0) {
    }

    pos = sub_str.find(NET_WIRE);
    if (pos != 0) {
    }

    // Attempt to find data type & data width
    pos = sub_str.find(NET_UINT1);
    if (pos != 0) {
    }

    pos = sub_str.find(NET_UINT2);
    if (pos != 0) {
    }

    pos = sub_str.find(NET_UINT8);
    if (pos != 0) {
    }

    pos = sub_str.find(NET_UINT16);
    if (pos != 0) {
    }

    pos = sub_str.find(NET_UINT32);
    if (pos != 0) {
    }

    pos = sub_str.find(NET_UINT64);
    if (pos != 0) {
    }

    pos = sub_str.find(NET_INT1);
    if (pos != 0) {
    }

    pos = sub_str.find(NET_INT2);
    if (pos != 0) {
    }

    pos = sub_str.find(NET_INT8);
    if (pos != 0) {
    }

    pos = sub_str.find(NET_INT16);
    if (pos != 0) {
    }

    pos = sub_str.find(NET_INT32);
    if (pos != 0) {
    }

    pos = sub_str.find(NET_INT64);
    if (pos != 0) {
    }

    // Attempt to find data path components 
    pos = sub_str.find(NET_INC);
    if (pos != 0) {
        return;
    }

    pos = sub_str.find(NET_DEC);
    if (pos != 0) {
        return;
    }
    
    pos = sub_str.find(NET_SHL);
    if (pos != 0) {
        return;
    }

    pos = sub_str.find(NET_SHR);
    if (pos != 0) {
        return;
    }

    pos = sub_str.find(NET_ADD);
    if (pos != 0) {
        return;
    }

    pos = sub_str.find(NET_SUB);
    if (pos != 0) {
        return;
    }

    pos = sub_str.find(NET_MUL);
    if (pos != 0) {
        return;
    }

    pos = sub_str.find(NET_DIV);
    if (pos != 0) {
        return;
    }

    pos = sub_str.find(NET_MOD);
    if (pos != 0) {
        return;
    }

    pos = sub_str.find(NET_COMP_LT);
    if (pos != 0) {
        return;
    }

    pos = sub_str.find(NET_COMP_GT);
    if (pos != 0) {
        return;
    }

    pos = sub_str.find(NET_COMP_EQ);
    if (pos != 0) {
        return;
    }

    pos = sub_str.find(NET_MUX);
    if (pos != 0) {
        return;
    }

    pos = sub_str.find(NET_REG);
    if (pos != 0) {
        return;
    }
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

            printf("%s", sub_buff);

            // Map netlist circuit operation to data path component
            sub_buff_len = i - buff_num;
            mapNetOpToDataPathComp(sub_buff, sub_buff_len); 

            // Set loop elements
            buff_num = i;
            k = 0;

            // Clear sub_buff
            memset(sub_buff, '\0', buff_len);
        } 
    }
    printf("\n");
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
