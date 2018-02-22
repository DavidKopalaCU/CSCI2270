#ifndef doublyLL_H
#define doublyLL_H

using namespace std;

struct Node {
	int id=-1;
	Node* prev = nullptr;
	Node* next = nullptr;
};

class doublyLL {
	private:
		Node* createNode(int,Node*,Node*);
		Node* head = nullptr;
		Node* tail = nullptr;
	public:
		bool insertNodeAtEnd(int);
        bool deleteNode(int);
        void print_list();
        void add_node(int);
		doublyLL();	//default constructor
		doublyLL(int);	//overloaded constructor
		~doublyLL();	//destructor
};

#endif
