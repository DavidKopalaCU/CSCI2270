//
//  main.cpp
//  Assignment1
//
//  Created by David Kopala on 1/21/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

#define MAX_LENGTH      100

bool split(string fill[3], string line) {
    int index = 0;
    string temp = "";
    for (int i = 0; i < line.length(); i++) {
        if (line[i] != ',') {
            temp += line[i];
        } else {
            fill[index++] = temp;
            temp = "";
            i++;
        }
    }
    fill[index++] = temp;
    if (index != 3) {
        return false;
    }
    return true;
}

struct CommunityItem {
    string type;
    bool forSale;
    int price;
    
    CommunityItem() {type = ""; forSale = false; price = -1;};
    
    CommunityItem(string line) {
        string comps[3];
        split(comps, line);
        
        type = comps[0];
        if (comps[1] == "for sale") {
            forSale = true;
        } else {
            forSale = false;
        }
        price = atoi(comps[2].c_str());
    }
};

void deleteItem(CommunityItem *arr[MAX_LENGTH], int index) {
    for (int i = index; i < MAX_LENGTH - 1; i++) {
        if (arr[i+1] != nullptr) {
            arr[i] = arr[i+1];
        } else {
            arr[i] = nullptr;
            return;
        }
    }
}

void foundItem(bool *found, int *curLen, CommunityItem *sale, CommunityItem *wanted, int index, CommunityItem *items[MAX_LENGTH]) {
    *found = true;
    cout<<sale->type<<" "<<wanted->price<<endl;
    deleteItem(items, index);
    *curLen = *curLen-1;
}

int main(int argc, const char * argv[]) {
    
    CommunityItem *items[MAX_LENGTH];
    int currLen = 0;
    //cout<<items[0].price<<endl;
    
    string filename;
    getline(cin, filename);
    ifstream file(filename);
    
    string line;
    while (!file.eof()) {
        getline(file, line);
        
        bool found = false;
        
        CommunityItem *item = new CommunityItem(line);
        for (int i = 0; i < currLen; i++) {
            if (item->type != items[i]->type) {
                continue;
            }
            if (item->forSale) {
                if (!items[i]->forSale) {
                    // SALE            WANTED
                    if (item->price <= items[i]->price) {
                        //FOUND ITEM
                        foundItem(&found, &currLen, items[i], item, i, items);
                        break;
                    }
                } else {
                    continue;
                }
            } else {
                if (items[i]->forSale) {
                    if (item->price >= items[i]->price) {
                        //FOUND ITEM
                        foundItem(&found, &currLen, item, items[i], i, items);
                        break;
                    }
                } else {
                    continue;
                }
            }
        }
        
        if (!found) {
            items[currLen++] = item;
        }
    }
    
    cout<<"#"<<endl;
    
    for (int i = 0; i < currLen; i++) {
        cout<<items[i]->type;
        if (items[i]->forSale) {
            cout<<", for sale, ";
        } else {
            cout<<", wanted, ";
        }
        cout<<items[i]->price<<endl;
    }
    
    cout<<"#"<<endl;
    
    return 0;
}
