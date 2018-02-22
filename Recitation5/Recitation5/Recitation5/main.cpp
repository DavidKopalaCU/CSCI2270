//
//  main.cpp
//  Recitation5
//
//  Created by David Kopala on 2/15/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#include <iostream>
#include "doublyLL.h"

int main(int argc, const char * argv[]) {
    doublyLL *ll = new doublyLL(0);
    for (int i = 1; i < 10; i++) {
        ll->add_node(i/3);
    }
    
    ll->print_list();
    ll->deleteNode(2);
    ll->print_list();
    
    return 0;
}
