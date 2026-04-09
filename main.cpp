#include <iostream>
#include <string>
#include <fstream>
using namespace std;


struct node{
	node* parent = nullptr;
	node* left = nullptr;
	node* right = nullptr;
	char color = 'R';
	int value;
};

void printTree(node*, int);
void addNode(node* &, node* &);

int main(){

	//Basic var instantiation
	string command;
	node* root = nullptr;
	bool runProgram = true;
	//Program runs
	while (runProgram){
		cout << "\nEnter Command(ADD, PRINT, READ, QUIT): ";
		cin >> command;
		
		//Command recognition
		if (command == "ADD"){ //Adds node objects

			//Get value
			int value;
			cout << "Value: ";
			cin >> value;

			//Create node
			node* addMe = new node();
			addMe->value = value;

			addNode(root, addMe);
		}
		else if (command == "READ"){ //Adds file nodes to tree
			//Adds file
			string fileName;
			cout << "Please enter filename: " << endl;
			cin >> fileName;
			
			ifstream numFile(fileName);

			if (!numFile) {
				cout << "Invalid file name." << endl;
			}
			else{
				int number;
				while (numFile >> number) {
					cout << "Adding " << number << " to the tree." << endl;
					node* addMe = new node();
					addMe->value = number;
					addNode(root, addMe);
			
				}
				numFile.close();
			}

		}
		else if (command == "PRINT"){ //Prints our tree
			if (root != nullptr){
				printTree(root, 0);
			}
		}
		else if (command == "QUIT"){
			//Exits search tree
			runProgram = false;
		}
		else{
			cout << "Command not recognized" << endl;
		}
	}		

	return 0;
}

void printTree(node* current, int depth){
	node* left = current->left;
	node* right = current->right;
	if (right != nullptr){
		printTree(right,depth+1);
	}
	for (int i = 0;i< depth;i++){
		cout << "\t";
	}
	if (current != nullptr){
		if (current->parent){
			cout << current->value << " " << current->color << " " << current->parent->value << endl;
		}
		else{
			cout << current->value << " " << current->color << " N/A" << endl;
		}
	}
	if (left != nullptr){
		printTree(left, depth+1);
	}
}

void addNode(node* &root, node* &newNode){
	if (root == nullptr){
		newNode->color = 'B';
		root = newNode;
	}
	else{
		node* current = root;
		if (newNode->value <= current->value){
			if (current->left == nullptr){
				current->left = newNode;
				newNode->parent = current;
				if (newNode->parent->color == 'R'){
					cout << "PROPERTY VIOLATION" << endl;
				}
			}
			else{
				addNode(current->left, newNode);
			}
		}
		else{
			if (current->right == nullptr){
				current->right = newNode;
				newNode->parent = current;
				if (newNode->parent->color == 'R'){
					cout << "PROPERTY VIOLATION" << endl;
				}
			}
			else{
				addNode(current->right, newNode);
			}
		}
	}

}
