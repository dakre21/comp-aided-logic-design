#include "HLSEngine.h"
#include "HLSConstants.h"
#include <ctype.h>
#include <list>

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

void HLSEngine::checkErrors() {
    //TODO Implement
}

void HLSEngine::createHLSM() {
    //TODO Implement
}

void HLSEngine::createFDS() {
    //TODO Implement
}

void HLSEngine::createALAP() {
    //TODO Implement
}

void HLSEngine::createASAP() {
    bool found = false;
    int time = 0;
    vector<Node> scheduled;

    for (int i = 0; i < vertices_.size(); i++) {
        time = 0;
        found = false;
        for (int j = 0; j < vertices_.size(); j++) {
            for (multimap<Node*, Edge>::iterator it = edges_.lower_bound(&vertices_[j]), 
                    end = edges_.upper_bound(&vertices_[j]); it != end; ++it) {
                if (it->second.vertex->op == vertices_[i].op) {
                    time += 1;
                }
            }
        }

        for (int j = 0; j < scheduled.size(); j++) {
            if (scheduled[j].op == vertices_[i].op) {
               found = true; 
               break;
            }
        }

        if (found != true) {
            vertices_[i].asap = time;
            scheduled.push_back(vertices_[i]);
        }
    }
}

void HLSEngine::createCDFGExt() {
    // Follow pemdas for priority for scheduling + MISC
    size_t found;
    size_t efound;
    size_t nfound;
    size_t vfound;
    string line;
    string output;
    string noutput;
    
    for (size_t i = 0; i < outputs_.size(); i++) {
        output = outputs_[i];
        for (size_t j = 0; j < operations_.size(); j++) {
            line = operations_[j]; 
            found = line.find(output);
            efound = line.find("=");
            if (found != bad_rc_ && efound != bad_rc_) {
                if (efound < found) {
                    for (size_t k = 0; k < outputs_.size(); k++) {
                        noutput = outputs_[k];
                        nfound = line.find(noutput);
                        if (nfound != bad_rc_) {
                            if (vertices_[i].op == vertices_[k].op) {
                                continue;
                            }

                            vfound = line.find(vertices_[k].op.substr(0,1));
                            if (vfound != bad_rc_) {
                                edges_.insert(make_pair(&vertices_[i], Edge(&vertices_[k])));
                            }
                        }
                    }
                }
            }
        }
    }
}

bool HLSEngine::createCDFG(const char* sub_buff, size_t sub_buff_len) {
    // Forward declarations
    string line = sub_buff;
    operations_.push_back(line);
    string str_operands  = "";

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

    string new_str = "";
    for (size_t i = 0; i < tmp_str.length(); i++) {
        if (isspace(tmp_str[i])) {
            // Do nothing
        } else {
            new_str.push_back(tmp_str[i]); 
        }
    }

    if (new_str.length() > 0) {
        outputs_.push_back(new_str);
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
            vertices_.push_back(Node(temp + to_string(count_)));
        } 
    }

    return true;
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

    createCDFGExt();

    createASAP();

    /*for (int i = 0; i < vertices_.size(); i++) {
        cout << vertices_[i] << endl;
    }

    for (int i = 0; i < operands_.size(); i++) {
        cout << operands_[i] << endl;
    }

    for (int i = 0; i < outputs_.size(); i++) {
        cout << outputs_[i] << endl;
    }*/

    for (int i = 0; i < vertices_.size(); i++) {
        cout << vertices_[i].op << " " << vertices_[i].asap << endl;
    }

    for (int i = 0; i < vertices_.size(); i++) {
        for (multimap<Node*, Edge>::iterator it = edges_.lower_bound(&vertices_[i]), 
                end = edges_.upper_bound(&vertices_[i]); it != end; ++it) {
                cout << it->first->op << " " << it->second.vertex->op << endl;
        }
    }

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

    return true;
}


