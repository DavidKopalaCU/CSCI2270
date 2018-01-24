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

//The maximum number of lines in the text file
#define MAX_LENGTH      100

/*
 split description
 
 splits a line from the file into components
 that can be parsed and used to populate a struct
 
 Inputs: string fill[3] -> the array to populate
         string line -> the string to parse
 Outputs: bool -> if the operation was successful or not
 
 */
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

//Represents an item on the community board from the input file
struct CommunityItem {
    string type;    //The type of item
    bool forSale;   //If the item is for sale or wanted
    int price;      //The associated price
    
    //Default Constructor
    CommunityItem() {type = ""; forSale = false; price = -1;};
    
    //Instantiates an item based on a line from the file
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

/*
 deleteItem description
 
 deletes an item from the array of items at a specific index
 
 does this by shifting elements up to fill the deleted spot,
 then replacing the last item (which has been duplicated) with
 a nullptr
 
 THIS ONLY WORKS BECAUSE THE ARRAY IS AN ARRAY OF POINTERS
 
 Inputs: CommunityItem *arr[] -> The array of items
         int index -> the index to delete
 */
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

/*
 foundItem description
 
 helper function that manages what happens when a match is found
 
 prints out the required text to the console
 deletes the found item
 decrement the current number of items
 
 Inputs: bool *found -> Points to the found boolean in the while loop of main()
         int curLen -> Points to the curLen int the main()
         CommunityItem *sale -> the item that is being sold
         CommunityItem *wanted -> the item that is wanted
         int index -> the index of the stored item in the array
         CommunityItem *items -> A pointer to the array of stored items
 */
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
    
    //Get the filename from the user
    string filename;
    if (argc != 2) {
        cout<<"Incorrent Usage!"<<endl;
        cout<<"Usage: ./a.out [filepath]"<<endl;
        filename = "/Users/davidkopala/Documents/CUBoulder/CSCI2270/Assignment1/garageSale.txt";
    } else {
        filename = argv[1];
    }
    //getline(cin, filename);
    ifstream file(filename);
    
    //Iterate through the file line by line
    string line;
    while (!file.eof()) {
        getline(file, line);
        
        //Specifies if there is a matching item in the array
        bool found = false;
        
        //Creates a new item based on the current line in the file
        CommunityItem *item = new CommunityItem(line);
        //Search the stored items for a match
        for (int i = 0; i < currLen; i++) {
            //Check if they have a matching type
            if (item->type != items[i]->type) {
                continue;
            }
            if (item->forSale) {
                if (!items[i]->forSale) {   //Make sure they are of different sale types
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
                if (items[i]->forSale) {    //Make sure they are of different sale types
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
            //Add the item to the array
            items[currLen++] = item;
        }
    }
    
    cout<<"#"<<endl;
    
    //Print out the remaining items
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
