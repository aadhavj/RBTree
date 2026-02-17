//Header guards and imports
#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>

using namespace std;

//Creates Node class
class Node{
	//public constructor, destructor, and functions
	public:
		Node(int);
		~Node();
		Node* getRight();
		Node* getLeft();
		void setRight(Node*);
		void setLeft(Node*);
		int getValue();
	//private variables
	private:
		int value;
		Node* right;
		Node* left;
};
//end of header guard
#endif
