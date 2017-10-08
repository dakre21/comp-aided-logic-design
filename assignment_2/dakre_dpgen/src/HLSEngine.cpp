#include "HLSEngine.h"

HLSEngine::HLSEngine() {
    // Do nothing
}

HLSEngine::~HLSEngine() {
    // Do nothing
}

bool HLSEngine::parseBufferCreateVerilogSrc(char* buff, size_t buff_len) {
    // Forward declarations 
    char* sub_buff;
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

            // TODO: Parse sub string for data path elements
            printf("%s", sub_buff);

            // Set loop elements
            buff_num = i;
            k = 0;

            // Clear sub_buff
            memset(sub_buff, '\0', buff_len);
        } 
    }
    printf("\n");
    return true;
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

    // Parse buffer and create verilog file and return result
    if (parseBufferCreateVerilogSrc(buff, buff_len) != true) {
        free(buff);
        return false;
    } else {
        free(buff);
        return true;
    }
}

float HLSEngine::findCriticalPath(FILE* file_in, FILE* file_out) {
    // TODO: Implement
    return 0.0;
}
