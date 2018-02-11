//
//  main.cpp
//  Assignment3
//
//  Created by David Kopala on 2/10/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct city {
    city *next;
    string cityName;
    string message;
    city() {};
    city(string name, city *nextNode, string msg) {
        cityName = name;
        next = nextNode;
        message = msg;
    };
};

city *buildNetwork() {
    city *head = new city();
    head->next = nullptr;
    //Reverse propogation
    string cities[] = {"Los Angeles", "Phoenix", "Denver", "Dallas", "St. Louis", "Chicago", "Atlanta", "Washington, D.C.", "New York", "Boston"};
    city *prevCity = nullptr;
    for (int i = 9; i >= 0; i--) {
        city *newCity = new city(cities[i], prevCity, "");
        prevCity = newCity;
    }
    head->next = prevCity;
    return head;
}

city *findCity(city *head, string name) {
    if (name == "First") {
        return head;
    }
    while ((head=head->next) != nullptr) {
        if (head->cityName == name) {
            return head;
        }
    }
    if (name == "") {
        return head;
    }
    return nullptr;
}

city *addCity(city *head, city *prev, string name) {
    city *next = prev->next;
    city *newCity = new city(name, next, "");
    prev->next = newCity;
    return head;
}

void transmitMsg(city *head) {
    if (head == nullptr || head->next == nullptr) {
        cout<<"Empty list"<<endl;
        return;
    }
    ifstream file;
    file.open("messageIn.txt");
    if (!file.is_open()) {
        file.open("/Users/davidkopala/Documents/CUBoulder/CSCI2270/Assignment3/messageIn.txt");
        if (!file.is_open()) {
            cout<<"Could not open file!"<<endl;
            return;
        }
    }
    string line;
    while (!file.eof()) {
        getline(file, line);
        string word;
        stringstream ss(line);
        while (ss>>word) {
            city *sender = head;
            sender->next->message = word;
            cout<<sender->next->cityName<<" received "<<sender->next->message<<endl;
            while ((sender=sender->next)->next != nullptr) {
                sender->next->message = sender->message;
                sender->message = "";
                cout<<sender->next->cityName<<" received "<<sender->next->message<<endl;
            }
        }
    }
}

void printPath(city *head) {
    cout<<"===CURRENT PATH==="<<endl;
    while((head=head->next) != nullptr) {
        cout<<head->cityName<<" -> ";
    }
    cout<<" NULL"<<endl;
    cout<<"=================="<<endl;
}

void menu(city *head) {
    cout<<"======Main Menu======"<<endl;
    cout<<"1. Build Network"<<endl;
    cout<<"2. Print Network Path"<<endl;
    cout<<"3. Transmit Message Coast-To-Coast"<<endl;
    cout<<"4. Add City"<<endl;
    cout<<"5. Quit"<<endl;
    
    int option;
    cin>>option;
    switch(option) {
        case 1:
            head = buildNetwork();
            break;
        case 2:
            printPath(head);
            break;
        case 3:
            transmitMsg(head);
            break;
        case 4:
        {
            cout<<"Enter a City name: "<<endl;
            string cityName;
            cin>>cityName;//getline(cin, cityName);
            cout<<"Enter a previous City name: "<<endl;
            string prevCity;
            cin>>prevCity;//getline(cin, prevCity);
            head = addCity(head, findCity(head, prevCity), cityName);
            break;
        }
        case 5:
            cout << "Goodbye!" << endl;
            return;
        default:
            cout<<"Unknown Command! Please try again."<<endl;
            break;
    }
    menu(head);
}

int main(int argc, const char * argv[]) {
    menu(nullptr);
    return 0;
}
