#include "HLSEngine.h"

HLSEngine::HLSEngine(FILE* file_in,
                     FILE* file_out) :

                     file_in_(file_in),
                     file_out_(file_out),
                     buff_(),
                     buff_len_(0) {
    // Do nothing
}

HLSEngine::~HLSEngine() {
    // Do nothing
}

void HLSEngine::readFileData() {
    // TODO: Implement
}

void HLSEngine::parseBufferCreateVerilogSrc() {
    // TODO: Implement
}

float HLSEngine::findCriticalPath() {
    // TODO: Implement
    return 0.0;
}
