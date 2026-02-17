//imports
#include "node.h"
#include <iostream>
#include <cstring>
using namespace std;

//Node constructor
Node::Node(int inputValue){
	value = inputValue;
	right = nullptr;
	left = nullptr;	
}
//Node destructor
Node::~Node(){}

//Get right node
Node* getRight(){
	return right;
}

//Get left node
Node* getLeft(){
	return left;
}

//Set right node
void setRight(Node* inputRight){
	right = inputRight;
}

//Set left node
void setLeft(Node* inputLeft){
	left = inputLeft;
}

//Get value
int getValue(){
	return value;
}

