#include "HLSEngine.h"

HLSEngine::HLSEngine() {
    // Do nothing
}

HLSEngine::~HLSEngine() {
    // Do nothing
}

bool HLSEngine::parseBufferCreateVerilogSrc(char* buff, size_t buff_len) {
    // Parse buffer for behavioral netlist
    for (int i = 0; i < buff_len; i++) {
        printf("%c", buff[i]);
        // Write verilog code to new synthesizable verilog module
        // Continue/Return based on successfullness
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

    // Clear buffer
    rewind(file_in);

    // Read buffer
    fread(buff, buff_len, 1, file_in);

    // NULL terminate buffer
    buff[buff_len] = '\0'; 

    if (strlen(buff) != buff_len) {
        fprintf(stderr, "Failed to read all of the bytes in the file\n");
        return false;
    }

    // Parse buffer and create verilog file
    return parseBufferCreateVerilogSrc(buff, buff_len);
}

float HLSEngine::findCriticalPath(FILE* file_in, FILE* file_out) {
    // TODO: Implement
    return 0.0;
}
