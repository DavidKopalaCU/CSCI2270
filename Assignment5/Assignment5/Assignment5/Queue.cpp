//
//  Queue.cpp
//  Assignment5
//
//  Created by David Kopala on 2/22/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#include <stdio.h>
#include <sstream>
#include "Queue.h"

Queue::Queue(int cap)
{
    queueSize = cap;
    arrayQueue = new std::string[cap];
    queueHead = 0;
    queueTail = 0;
    queueCount = 0;
}

Queue::~Queue()
{
    delete [] arrayQueue;
    arrayQueue = nullptr;
}

void Queue::enqueue(std::string word)
{
    if (queueIsFull()) {
        std::cout<<"Queue is full."<<std::endl;
        return;
    }
    arrayQueue[queueTail++] = word;
    queueCount++;
    if (queueTail == queueSize) {
        queueTail = 0;
    }
    std::cout<<"E: "<<word<<std::endl;
    std::cout<<"H: "<<queueHead<<std::endl;
    std::cout<<"T: "<<queueTail<<std::endl;
}

void Queue::dequeue()
{
    if (queueIsEmpty()) {
        std::cout<<"Queue is empty"<<std::endl;
        return;
    }
    std::string word = arrayQueue[queueHead++];
    queueCount--;
    if (queueHead == queueSize) {
        queueHead = 0;
    }
    std::cout<<"H: "<<queueHead<<std::endl;
    std::cout<<"T: "<<queueTail<<std::endl;
    std::cout<<"word: "<<word<<std::endl;
}

void Queue::printQueue()
{
    if (queueCount == 0) {
        std::cout<<"Empty"<<std::endl;
        return;
    }
    for (int i = 0; i < queueCount; i++) {
        int index = queueHead + i;
        if (index >= queueSize) {
            index -= queueSize;
        }
        std::cout<<index<<": "<<arrayQueue[index]<<std::endl;
    }
}

void Queue::enqueueSentence(std::string sentence)
{
    std::stringstream ss(sentence);
    std::string word;
    while (ss>>word) {
        enqueue(word);
    }
}

bool Queue::queueIsFull() {
    if (queueCount == queueSize) {
        return true;
    } else {
        return false;
    }
}

bool Queue::queueIsEmpty() {
    if (queueCount == 0) {
        return true;
    } else {
        return false;
    }
}
