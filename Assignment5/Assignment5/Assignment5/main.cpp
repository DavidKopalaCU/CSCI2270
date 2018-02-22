//
//  main.cpp
//  Assignment5
//
//  Created by David Kopala on 2/22/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#include <iostream>
#include "Queue.h"

using namespace std;

void enqueue(Queue *q) {
    cout<<"word: ";
    string word;
    cin>>word;
    q->enqueue(word);
}

void dequeue(Queue *q) {
    q->dequeue();
}

void print(Queue *q) {
    q->printQueue();
}

void sentence(Queue *q) {
    cout<<"sentence: ";
    string sent;
    while (sent == "") {
        getline(cin, sent);
    }
    q->enqueueSentence(sent);
}

void menu(Queue *q) {
    cout<<"======Main Menu====="<<endl;
    cout<<"1. Enqueue word"<<endl;
    cout<<"2. Dequeue word"<<endl;
    cout<<"3. Print queue"<<endl;
    cout<<"4. Enqueue sentence"<<endl;
    cout<<"5. Quit"<<endl;
    int option;
    cin>>option;
    switch(option) {
        case 1:
            enqueue(q);
            break;
        case 2:
            dequeue(q);
            break;
        case 3:
            print(q);
            break;
        case 4:
            sentence(q);
            break;
        case 5:
            delete q;
            cout<<"Goodbye!"<<endl;
            return;
        default:
            cout<<"Invalid Option, Try again"<<endl;
            break;
    }
    menu(q);
}

int main(int argc, const char * argv[]) {
    Queue *q = new Queue(10);
    menu(q);
    return 0;
}

