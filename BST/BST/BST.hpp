//
//  BST.hpp
//  BST
//
//  Created by David Kopala on 3/8/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#ifndef BST_hpp
#define BST_hpp

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
#include <sstream>

using namespace std;

struct node {
    int value;
    node *left;
    node *right;
    node *parent;
    
    node(int val, node *p, node *l, node *r) {
        value = val;
        parent = p;
        left = l;
        right = r;
    }
};

class BST {
    
private:
    node *root;
    int height;
    void priv_addValue(node *parent, int value, int depth);
    void priv_deleteValue(node *parent, int target);
    bool priv_find(node *parent, int target);
    void getLevel_recur(node *parent, int level, string *build);
    
public:
    BST(int start);
    BST();
    void addValue(int val);
    void deleteValue(int target);
    bool exists(int target);
    string *getLevel(int level);
    void printTree();
    
};

#endif /* BST_hpp */
