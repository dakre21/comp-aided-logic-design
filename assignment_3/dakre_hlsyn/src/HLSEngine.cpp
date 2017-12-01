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

void HLSEngine::createHLSM() {
    //TODO Implement
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
            vertices_[pos_div].cycle = cycle;
            div = true;
        } 
        
        if (vertices_[pos_alu].cycle == 0 && vertices_[pos_alu].time_frame[0] <= cycle && cycle <= vertices_[pos_alu].time_frame[1]) {
            vertices_[pos_alu].cycle = cycle;
        }

        if (time_to_end == 0 && scheduled == false) {
            cycle = 0;
        }

        if ((start_time + 1) < (clock() / CLOCKS_PER_SEC)) {
            return false;
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
    }*/

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


