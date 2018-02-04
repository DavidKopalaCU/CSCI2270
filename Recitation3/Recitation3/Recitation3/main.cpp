//
//  main.cpp
//  Recitation3
//
//  Created by David Kopala on 2/1/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

void resize(int *old, int *capacity) {
    int newCap = (*capacity) * 2;
    int *newArr = new int[newCap];
    for (int i = 0; i < *capacity; i++) {
        int inc = sizeof(int) * i;
        *(newArr + inc) = *(old + inc);
    }
    delete [] old;
    old = newArr;
    *capacity = newCap;
}

int main(int argc, const char * argv[]) {
    
    string filename;
    if (argc != 2) {
        cout<<"Incorrect Arguments!"<<endl;
        cout<<"Usage: ./a.out <filename>"<<endl;
        cout<<"Using default parameters."<<endl;
        //return -1;
        filename = "/Users/davidkopala/Documents/CUBoulder/CSCI2270/Recitation3/Recitation3/Recitation3/test.txt";
    } else {
        filename = argv[1];
    }
    
    cout<<"Input file: "<<filename<<endl;
    
    ifstream in(filename);
    if (!in.is_open()) {
        cout<<"Invalid Filepath! Could not open file."<<endl;
        return -2;
    }
    
    int capacity = 10;
    int *arr = new int[capacity];
    
    int index = 0;
    string line;
    while (!in.eof()) {
        getline(in, line);
        if (line == "") {
            continue;
        }
        arr[index++] = atoi(line.c_str());
        if (index == capacity) {
            resize(arr, &capacity);
        }
    }
    
    ofstream out("/Users/davidkopala/Documents/CUBoulder/CSCI2270/Recitation3/Recitation3/Recitation3/out.txt");
    for (int i = 0; i < index; i++) {
        out<<arr[i]<<endl;
    }
    
    return 0;
}
