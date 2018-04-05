//
//  main.cpp
//  Assignment6
//
//  Created by David Kopala on 3/9/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "MovieTree.hpp"

using namespace std;

//Splits at ','
void splitString(string arr[], string str, int len) {
    stringstream ss(str);
    string sect;
    int index = 0;
    while(!ss.eof()) {
        getline(ss, sect, ',');
        if (sect == "") {
            continue;
        } else if (index == len) {
            break;
        }
        
        arr[index++] = sect;
    }
}

bool readFiles(MovieTree *m, string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout<<"Could not open file!"<<endl;
        return false;
    }
    
    string line;
    string comps[4];
    while (!file.eof()) {
        getline(file, line);
        if (line == "") {
            continue;
        }
        
        splitString(comps, line, 4);
        m->addMovieNode(stoi(comps[0]), comps[1], stoi(comps[2]), stoi(comps[3]));
    }
    return true;
}

void findMovie(MovieTree *m) {
    cout<<"Enter title:"<<endl;
    string title;
    while (title == "") {
        getline(cin, title);
    }
    m->findMovie(title);
}

void rentMovie(MovieTree *m) {
    cout<<"Enter title:"<<endl;
    string title;
    while (title == "") {
        getline(cin, title);
    }
    m->rentMovie(title);
}

void printMovies(MovieTree *m) {
    m->printMovieInventory();
}

void deleteMovie(MovieTree *m) {
    cout<<"Enter title:"<<endl;
    string title;
    while (title == "") {
        getline(cin, title);
    }
    m->deleteMovieNode(title);
}

void countMovies(MovieTree *m) {
    cout<<"Tree contains: "<<m->countMovieNodes()<<" movies."<<endl;
}

void menu(MovieTree *m) {
    cout << "======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Rent a movie" << endl;
    cout << "3. Print the inventory" << endl;
    cout << "4. Delete a movie" << endl;
    cout << "5. Count the movies" << endl;
    cout << "6. Quit" << endl;
    int opt = 0;
    while (opt == 0) {
        cin>>opt;
    }
    switch (opt) {
        case 1:
            findMovie(m);
            break;
        case 2:
            rentMovie(m);
            break;
        case 3:
            printMovies(m);
            break;
        case 4:
            deleteMovie(m);
            break;
        case 5:
            countMovies(m);
            break;
        case 6:
            cout << "Goodbye!" << endl;
            delete m;
            return;
    }
    menu(m);
}

int main(int argc, const char * argv[]) {
    
    string filename;
    if (argc != 2) {
        cout<<"Invalid Arguments!"<<endl;
        cout<<"Usage: MovieTree [filename]"<<endl;
        cout<<"Using defaults."<<endl;
        filename = "/Users/davidkopala/Documents/CUBoulder/CSCI2270/Assignment6/Assignment6Movies.txt";
    } else {
        filename = argv[1];
    }
    //cout<<"Filename: "<<filename<<endl;
    
    MovieTree *m = new MovieTree();
    readFiles(m, filename);
    
    menu(m);
    
    return 0;
}

