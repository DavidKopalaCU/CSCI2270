#include <iostream>
#include "doublyLL.h"
using namespace std;

doublyLL::doublyLL() {

}

doublyLL::doublyLL(int nodeID) {
	//create head node
	head = createNode(nodeID, nullptr, nullptr);
	tail = head;
}

doublyLL::~doublyLL() {
    
}


Node* doublyLL::createNode(int nodeID, Node* nodePrev, Node* nodeNext) {
	Node* newNode = new Node;
	newNode->id = nodeID;
	newNode->next = nodeNext;
	newNode->prev = nodePrev;
    
    if (nodePrev != nullptr) {
        nodePrev->next = newNode;
    }

	return newNode;
}

bool doublyLL::insertNodeAtEnd(int nodeID) {
	if (head == nullptr) {
		//nothing in the list
		head = createNode(nodeID, nullptr, nullptr);
		tail = head;
	}
	else {
		Node* newNode = createNode(nodeID, tail, nullptr);
		tail->next = newNode;
		tail = newNode;
	}
	return true;
}

bool doublyLL::deleteNode(int id) {
    Node *temp = createNode(-1, nullptr, head);
    while((temp = temp->next) != nullptr) {
        if (temp->id == id) {
            temp->prev->next = temp ->next;
            temp->next->prev = temp->prev;
        }
    }
    return true;
}

void doublyLL::print_list() {
    Node *temp = createNode(-1, nullptr, head);
    while ((temp = temp->next) != nullptr) {
        cout<<temp->id<<" -> ";
    }
    cout<<"NULL"<<endl;
}

void doublyLL::add_node(int id) {
    Node *newNode = createNode(id, tail, nullptr);
    tail = newNode;
}









