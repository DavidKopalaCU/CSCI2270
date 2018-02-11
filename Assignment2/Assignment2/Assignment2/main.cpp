//
//  main.cpp
//  Assignment2
//
//  Created by David Kopala on 2/3/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>

#define IGNORE_LEN      50

using namespace std;

struct wordItem {
    string word;
    int count;
    
    wordItem(string a, int b) {
        word = a;
        count = b;
    }
};

void getStopWords(char *ignoreWordFilename, string ignoreWords[]) {
    ifstream in(ignoreWordFilename);
    if (!in.is_open()) {
        cout<<"Could not open "<<*ignoreWordFilename<<endl;
        return;
    }
    
    string line;
    int index = 0;
    while (!in.eof()) {
        getline(in, line);
        if (line == "") {
            continue;
        }
        stringstream s(line);
        string word;
        while (s>>word) {
            ignoreWords[index++] = word;
        }
        
    }
}

bool isStopWord(string word, string ignoreWords[]) {
    for (int i = 0; i < IGNORE_LEN; i++) {
        if (word == ignoreWords[i]) {
            return true;
        }
    }
    return false;
}

int getTotalNumberNonStopWords(wordItem** list, int length) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        count += list[i]->count;
    }
    return count;
}

void arraySort(wordItem** list, int length) {
    bool sorted = true;
    
    for (int i = 0; i < length - 1; i++) {
        wordItem *first = list[i];
        wordItem *next = list[i+1];
        
        if (next->count > first->count) {
            list[i] = next;
            list[i+1] = first;
            
            sorted = false;
        }
    }
    
    if (!sorted) {
        arraySort(list, length);
    }
}

void printTopN(wordItem** list, int topN) {
    for (int i = 0; i < topN; i++) {
        wordItem *item = list[i];
        cout<<item->count<<" - "<<item->word<<endl;
    }
}

void doubleFound(wordItem*** arr_a, int *len) {
    wordItem **arr = *arr_a;
    wordItem **newArr = new wordItem*[(*len)*2];
    for (int i = 0; i < *len; i++) {
        newArr[i] = arr[i];
        arr[i] = nullptr;
    }
    delete [] arr;
    *arr_a = newArr;
    *len = (*len) * 2;
}

int main(int argc, char * argv[]) {
    
    int numOut;
    string filename;
    string ignoreFile;
    
    if (argc != 4) {
        cout<<"Incorrect Usage!"<<endl;
        cout<<"Using defaults."<<endl;
        
        numOut = 50;
        filename = "/Users/davidkopala/Documents/CUBoulder/CSCI2270/Assignment2/HungerGames_edit.txt";
        ignoreFile = "/Users/davidkopala/Documents/CUBoulder/CSCI2270/Assignment2/ignoreWords.txt";
    } else {
        numOut = atoi(argv[1]);
        filename = argv[2];
        ignoreFile = argv[3];
    }
    
    cout<<"N Words: "<<numOut<<endl;
    cout<<"Filename: "<<filename<<endl;
    cout<<"Ignore: "<<ignoreFile<<endl;
    
    string ignoreWords[100];
    char *c = (char *)malloc(ignoreFile.size() + 1);
    memcpy(c, ignoreFile.c_str(), ignoreFile.size() + 1);
    getStopWords(c, ignoreWords);
    
    ifstream in(filename);
    if (!in.is_open()) {
        cout<<"Could not open "<<filename<<endl;
        return -1;
    }
    
    int length = 100;
    int index = 0;
    int numDouble = 0;
    wordItem** words = new wordItem*[length];
    string line;
    while (!in.eof()) {
        getline(in, line);
        if (line == "") {
            continue;
        }
        stringstream s(line);
        string word;
        while (s>>word) {
            //s>>word;
            if (word == "") {
                continue;
            }
            
            if (index == length) {
                doubleFound(&words, &length);
                numDouble++;
            }
            
            bool found = false;
            if (isStopWord(word, ignoreWords)) {
                found = true;
                continue;
            }
            for (int i = 0; i < index; i++) {
                wordItem *item = words[i];
                if (item->word == word) {
                    item->count++;
                    found = true;
                }
            }
            if (!found) {
                words[index++] = new wordItem(word, 1);
            }
        }
    }
    
    arraySort(words, index);
    printTopN(words, numOut);
    cout<<"#"<<endl;
    cout<<"Array Doubled: "<<numDouble<<endl;
    cout<<"#"<<endl;
    cout<<"Unique non-common words: "<<index<<endl;
    cout<<"#"<<endl;
    cout<<"Total non-common words: "<<getTotalNumberNonStopWords(words, index)<<endl;
    
    return 0;
}
