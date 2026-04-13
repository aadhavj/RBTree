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
void addNode(node* &, node* &, node*);
void swapColorScheme(node* &, node* &);
void update(node*, node*);
node* getUncle(node*);
node* getGrandfather(node*);
node* rotateLeft(node*);
//node* rotateRight(node*);

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

			addNode(root, addMe, root);
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
					addNode(root, addMe, root);
			
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

node* getGrandfather(node* curr){
	return curr->parent->parent;
}
node* getUncle(node* curr){
	node* grandfather = getGrandfather(curr);
	if (grandfather){
		if (curr->parent == grandfather->left){
			return grandfather->right;
		}
		else{
			return grandfather->left;
		}
	}
	else{
		return nullptr;
	}
}

node* rotateLeft(node* current){
	node* right = current->right;
	node* rightLeft = right->left;
	right->left = current;
	current->right = rightLeft;
	current->parent = right;
	if (rightLeft){
		rightLeft->parent = current;
	}
	return right;
}

node* rotateRight(node* current){
	node* left = current->left;
	node* leftRight = left->right;
	left->right = current;
	current->left = leftRight;
	current->parent = left;
	if (leftRight){
		leftRight->parent = current;
	}
	return left;
}


void swapColorScheme(node* &root, node* &curr){
	node* parent = curr->parent;
	node* uncle = getUncle(curr);
	if (parent != root){
		if (curr->color == 'B'){
			parent->color = 'R';
			if (uncle){
				uncle->color = 'R';
			}
		}
		else{
			parent->color = 'B';
			if (uncle){
				uncle->color = 'B';
			}

		}
		swapColorScheme(root, parent);
	}
}

void update(node* root, node* addedNode){
	if (addedNode->parent->color == 'R'){
		node* uncle = getUncle(addedNode);

		if (uncle && uncle->color == 'R'){ //Uncle red case
			swapColorScheme(root, addedNode);
		}
		else if (uncle && uncle->color == 'B'){ //Uncle black case
			node* grandparent = getGrandfather(addedNode);
			node* parent = addedNode->parent;
			bool leftParent = addedNode->parent->value <= grandparent->value; 
			bool leftChild = addedNode->value <= parent->value;
			if (leftParent && leftChild){ // LL case
				rotateRight(grandparent);
				char grandColor = grandparent->color;
				grandparent->color = parent->color;
				parent->color = grandColor;
			}
			else if (leftParent && !leftChild){ //LR
				rotateLeft(parent);
				rotateRight(grandparent);
				char grandColor = grandparent->color;
				grandparent->color = parent->color;
				parent->color = grandColor;
			}
			else if (!leftParent && !leftChild){ //RR
				rotateLeft(grandparent);
				char grandColor = grandparent->color;
				grandparent->color = parent->color;
				parent->color = grandColor;
			}
			else if (!leftParent && leftChild){ //RL
				rotateRight(parent);
				rotateLeft(grandparent);
				char grandColor = grandparent->color;
				grandparent->color = parent->color;
				parent->color = grandColor;
			}
		}
		else{
			cout << "PROPERTY VIOLATION" << endl;
		}
	}
	
}
void addNode(node* &curr, node* &newNode, node* root){
	if (curr == nullptr){
		newNode->color = 'B';
		curr = newNode;
	}
	else{
		node* current = curr;
		if (newNode->value <= current->value){
			if (current->left == nullptr){
				current->left = newNode;
				newNode->parent = current;
				update(root, newNode);
			}
			else{
				addNode(current->left, newNode, root);
			}
		}
		else{
			if (current->right == nullptr){
				current->right = newNode;
				newNode->parent = current;
				update(root, newNode);
			}
			else{
				addNode(current->right, newNode, root);
			}
		}
	}

}
