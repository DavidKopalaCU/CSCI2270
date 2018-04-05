//
//  main.cpp
//  Recitation10
//
//  Created by David Kopala on 3/22/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    string filepath;
    if (argc != 2) {
        cout<<"Invalid Usage!"<<endl;
        cout<<"Usage: ./a.out [filename]"<<endl;
        cout<<"Using defaults"<<endl;
        filepath = "/Users/davidkopala/Documents/CUBoulder/CSCI2270/Recitation10/mat.txt";
    } else {
        filepath = argv[1];
    }
    cout<<"Filepath: "<<filepath<<endl;
    
    ifstream file(filepath);
    if (!file.is_open()) {
        cout<<"Invalid Filepath!"<<endl;
        return -1;
    }
    
    Graph *g = new Graph();
    
    string keys[4];
    int keyIndex = 0;
    string line;
    getline(file, line);
    stringstream first(line);
    string city;
    first>>city;
    while (first>>city) {
        if (city == "") {
            continue;
        }
        g->addVertex(city);
        keys[keyIndex++] = city;
        
    }
    
    while (!file.eof()) {
        getline(file, line);
        if (line == "") {
            continue;
        }
        
        stringstream s(line);
        string city;
        s>>city;
        
        string word;
        int index = 0;
        while (s>>word) {
            if (word == "") {
                continue;
            }
            if (word != "0") {
                g->addEdge(city, keys[index], stoi(word));
            }
            index++;
        }
    }
    
    g->displayEdges();
    
    return 0;
}
