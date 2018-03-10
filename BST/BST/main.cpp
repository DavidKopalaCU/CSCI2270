//
//  main.cpp
//  BST
//
//  Created by David Kopala on 3/8/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include "BST.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    BST *bst = new BST(10);
    bst->addValue(5);
    bst->addValue(15);
    bst->addValue(2);
    bst->addValue(17);
    bst->addValue(1);
    bst->addValue(19);
    bst->addValue(12);
    bst->addValue(13);
    bst->addValue(16);
    bst->addValue(8);
    bst->addValue(9);
    bst->addValue(4);
    bst->addValue(6);
    bst->addValue(11);
    bst->addValue(7);
    bst->addValue(3);
    bst->printTree();
    
    bst->deleteValue(15);
    bst->addValue(15);
    bst->printTree();
    
    cout<<endl;
    
    return 0;
}
