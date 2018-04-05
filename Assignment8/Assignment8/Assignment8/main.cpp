//
//  main.cpp
//  Assignment8
//
//  Created by David Kopala on 3/25/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Graph.h"

using namespace std;

void printV(Graph *g) {
    g->displayEdges();
}

void vAdj(Graph *g) {
    string v1 = "";
    string v2 = "";
    cout << "Enter first city:" << endl;
    while (v1 == "") {
        getline(cin, v1);
    }
    cout << "Enter second city:" << endl;
    while (v2 == "") {
        getline(cin, v2);
    }
    if (g->isAdjacent(v1, v2)) {
        cout<<"True"<<endl;
    } else {
        cout<<"False"<<endl;
    }
}

void menu(Graph *g) {
    cout << "======Main Menu======" << endl;
    cout << "1. Print vertices" << endl;
    cout << "2. Vertex adjacent" << endl;
    cout << "3. Quit" << endl;
    int opt = -1;
    while (opt == -1) {
        cin>>opt;
    }
    switch (opt) {
        case 1:
            printV(g);
            break;
        case 2:
            vAdj(g);
            break;
        case 3:
            cout<<"Goodbye!"<<endl;
            return;
        default:
            cout<<"Unsupported Option, Try Again"<<endl;
    }
    menu(g);
}

int main(int argc, const char * argv[]) {
    
    string filename;
    if (argc != 2) {
        //cout<<"Invalid Usage!"<<endl;
        filename = "/Users/davidkopala/Documents/CUBoulder/CSCI2270/Assignment8/zombieCities.txt";
    } else {
        filename = argv[1];
    }
    //cout<<"Filename: "<<filename<<endl;
    
    ifstream file(filename);
    if (!file.is_open()) {
        cout<<"Could not open file!"<<endl;
        return -1;
    }
    
    Graph *g = new Graph();
    
    string line;
    vector<string> cities;
    getline(file, line);
    //cout<<line;
    stringstream ss(line);
    string c;
    getline(ss, c, ',');
    while (!ss.eof()) {
        getline(ss, c, ',');
        if (c == "") {
            continue;
        }
        cities.push_back(c);
        g->addVertex(c);
    }
    while (!file.eof()) {
        getline(file, line);
        //cout<<line;
        if (line == "") {
            continue;
        }
        
        stringstream s(line);
        string weight;
        string city;
        getline(s, city, ',');
        int index = 0;
        while (!s.eof()) {
            getline(s, weight, ',');
            if (weight == "") {
                continue;
            }
            
            if (weight != "-1") {
                g->addEdge(city, cities[index], stoi(weight));
            }
            index++;
        }
        
    }
    
    menu(g);
    
    return 0;
}
