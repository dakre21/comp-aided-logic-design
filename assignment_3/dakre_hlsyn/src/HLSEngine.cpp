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

void HLSEngine::calcSlack() {
    for (size_t i = 0; i < vertices_.size(); i++) {
        vertices_[i].slack = vertices_[i].alap - vertices_[i].asap; 
    }
}

bool HLSEngine::createALAP(int latency) {
    bool found = false;
    int time = latency;
    vector<Node> scheduled;

    for (size_t i = 0; i < vertices_.size(); i++) {
        time = latency;
        found = false;
        for (multimap<Node*, Edge>::iterator it = edges_.lower_bound(&vertices_[i]), 
                end = edges_.upper_bound(&vertices_[i]); it != end; ++it) {
            time -= 1;
        }

        for (size_t j = 0; j < scheduled.size(); j++) {
            if (scheduled[j].op == vertices_[i].op) {
               found = true; 
               break;
            }
        }

        if (found != true) {
            vertices_[i].alap = time;
            
            if (time < 0) {
                return false;
            }
            scheduled.push_back(vertices_[i]);
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
        for (size_t j = 0; j < vertices_.size(); j++) {
            for (multimap<Node*, Edge>::iterator it = edges_.lower_bound(&vertices_[j]), 
                    end = edges_.upper_bound(&vertices_[j]); it != end; ++it) {
                if (it->second.vertex->op == vertices_[i].op) {
                    time += 1;
                }
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
    int found;
    int efound;
    int nfound;
    int vfound;
    int bfound;
    int ifound;
    int ffound;
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
                if (efound < found && efound != bad_rc_) {
                    for (size_t k = 0; k < outputs_.size(); k++) {
                        noutput = outputs_[k];
                        nfound = line.find(noutput);
                        if (nfound != bad_rc_) {
                            if (vertices_[i].op == vertices_[k].op) {
                                continue;
                            }

                            if (line.length() < (found + 1)) {
                                if (line.substr(found, found + 1) != " ") {
                                    continue;
                                }
                            }

                            vfound = line.find(vertices_[k].op.substr(0, 1));
                            if (vfound != bad_rc_) {
                                edges_.insert(make_pair(&vertices_[i], Edge(&vertices_[k])));
                            }
                        }
                    }
                } else if (ifound != bad_rc_) {
                    for (size_t k = j + 1; k < operations_.size(); k++) {
                        line = operations_[k];
                        bfound = line.find("}");
                        if (bfound != bad_rc_) {
                            break;
                        }

                        for (size_t l = 0; l < outputs_.size(); l++) {
                            noutput = outputs_[l];
                            nfound = line.find(noutput);

                            if (line.length() < (found + 1)) {
                                if (line.substr(found, found + 1) != " ") {
                                    continue;
                                }
                            }

                            if (nfound != bad_rc_) {
                                efound = line.find("=");
                                if (efound != bad_rc_ && nfound < efound) {
                                    edges_.insert(make_pair(&vertices_[i], Edge(&vertices_[l])));
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

bool HLSEngine::createCDFG(const char* sub_buff, size_t sub_buff_len) {
    // Forward declarations
    string line = " " + string(sub_buff) + " ";

    // Pad line with initial white space to help with parsing
    line[1] = line[0];
    line[0] = '\n';
    line[line.length()-1] = line[line.length()];
    line[line.length()] = '\n';

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
            vertices_.push_back(Node(temp + to_string(count_)));
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
                "being too small based netlist's total inter opertaional dependencies exceeding latency time\n");
        return false;
    }

    if (createALAP(latency) != true) {
        fprintf(stderr, "Failed to create ALAP graph... issue with given latency "\
                "being too small based on netlist's total inter operational total dependencies exceeding latency time\n");
        return false;
    }

    calcSlack();

    /*for (int i = 0; i < vertices_.size(); i++) {
        cout << vertices_[i] << endl;
    }

    for (int i = 0; i < operands_.size(); i++) {
        cout << operands_[i] << endl;
    }

    for (int i = 0; i < outputs_.size(); i++) {
        cout << outputs_[i] << endl;
    }*/

    cout << "ALAP TIMES" << endl;
    for (int i = 0; i < vertices_.size(); i++) {
        cout << vertices_[i].op << " " << vertices_[i].alap << endl;
    }

    cout << "ASAP TIMES" << endl;
    for (int i = 0; i < vertices_.size(); i++) {
        cout << vertices_[i].op << " " << vertices_[i].asap << endl;
    }

    cout << "SLACK TIMES" << endl;
    for (int i = 0; i < vertices_.size(); i++) {
        cout << vertices_[i].op << " " << vertices_[i].slack << endl;
    }

    cout << "EDGES" << endl;
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
    rc &= parseBufferCreateVerilogSrc(buff, buff_len, file_out, latency);
    free(buff);

    return true;
}


