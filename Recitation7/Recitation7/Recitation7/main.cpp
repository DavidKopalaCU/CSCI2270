//
//  main.cpp
//  Recitation7
//
//  Created by David Kopala on 3/1/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#include <iostream>
#include "BST.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    BST *tree = new BST(5);
    //tree->printTree();
    
    tree->insertNode(3);
    tree->insertNode(1);
    tree->insertNode(4);
    tree->insertNode(7);
    tree->insertNode(10);
    tree->insertNode(-1);
    tree->insertNode(8);
    
    cout<<tree->searchKey(8)<<endl;
    
    tree->printTree();
    
    cout<<endl;
    
    return 0;
}
