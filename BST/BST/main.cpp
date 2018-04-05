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
#include "BST_T.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    /*int a = 123456;
    int *arr = &a;
    cout<<arr[0]<<endl;
    cout<<typeid(arr).name()<<endl;
    cout<<sizeof(arr)/sizeof(typeof(arr))<<endl;
    
    cout<<endl;
    
    char *str = "abc";
    cout<<str[0]<<endl;
    cout<<typeid(str[0]).name()<<endl;
    cout<<sizeof(str)/sizeof(typeof(str[0]))<<endl;
    
    cout<<endl;
    
    string x = "abc";
    string y = "b";
    cout<<(x < y)<<endl;
    
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
    
    cout<<endl;*/
    
    BST_T<int> *bst = new BST_T<int>(10);
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
    
    BST_T<string> *s = new BST_T<string>("m");
    s->addValue("azm");
    s->addValue("zma");
    s->addValue("y");
    s->printTree();
    
    return 0;
}
