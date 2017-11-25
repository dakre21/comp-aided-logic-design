/*
 * Author: David Akre
 * Date: 11/25/17
 * Description: Helper interface that holds nodes
 * and edges structs
 */

#pragma once

#include <string.h>

using namespace std;

// Define two structs for nodes and edges
struct Node {
    int force;
    int cycle;
    int asap;
    int alap;
    int slack;
    string op;
    
    Node(string operation) { 
        op = operation;
        force = 0;
        cycle = 0;
        asap = 0;
        alap = 0;
        slack = 0;
    }
};

struct Edge {
    Node* vertex;

    Edge(Node* node) {
        vertex = node;
    }
};
