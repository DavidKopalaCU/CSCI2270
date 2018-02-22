//
//  CommnuicationNetwork.cpp
//  Assignment4
//
//  Created by David Kopala on 2/18/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#include <stdio.h>
#include "CommunicationNetwork.h"

City* findCity(City *head, std::string cityName)
{
    City *newHead = new City();
    newHead->next = head;
    while((newHead = newHead->next) != nullptr) {
        if (newHead->cityName == cityName) {
            return newHead;
        }
    }
    return nullptr;
}

void CommunicationNetwork::addCity(std::string newName, std::string prevName)
{
    if (head == nullptr || tail == nullptr) {
        head = new City(newName, nullptr, nullptr, "");
        tail = head;
        return;
    }
    City *prevCity = findCity(head, prevName);
    City *newCity = new City(newName, prevCity->next, prevCity, "");
    prevCity->next->previous = newCity;
    prevCity->next = newCity;
}

void CommunicationNetwork::transmitMsg(char *message)
{
    
}

void CommunicationNetwork::printNetwork()
{
    
}

void CommunicationNetwork::buildNetwork()
{
    
}

void CommunicationNetwork::deleteCity(std::string cityName)
{
    
}

void CommunicationNetwork::deleteNetwork()
{
    
}
