#include <iostream>
#include <cstring>
#include "node.h"
using namespace std;

void add(int value, Node** treeArray);
void Delete(Node** treeArray);
void DeleteAll(Node** treeArray);

int main(){

	//Basic var instantiation
	char command[1000];
	Node* tree[101] = new Node*[101];
	bool runProgram = true;
	for (int i = 0; i <= 101;i++){
		tree[i] = nullptr;
	}

	//Valid Command prompts
	char del[] = "DELETE";
	char delAll[] = "DELETEALL";
	char add[] = "ADD";
	char quit[] = "QUIT";

	while (runProgram){
		cout << "\nEnter Command(DELETE, DELETEALL, ADD, QUIT): ";
		cin >> command;
		command[9] = '\0';

		//Command recognition
		if (strcmp(command, del) == 0){
			cout << "Deletes stuff" << endl;
		}
		else if (strcmp(command, delAll) == 0){
			cout << "Deletes everything" << endl;
		}
		else if (strcmp(command, add) == 0){
			cout << "Adds node" << endl;
		}
		else if (strcmp(command, quit) == 0){
			cout << "Quitting..." << end;
			runProgram = false;
		}
		else{
			cout << "Command prompt unrecognized" << endl;
		}
	}

	return 0;
}

void add(int value, Node** treeArray){
	Node *newNode = new Node(value);
	//root case
	if (treeArray[1] == nullptr){
		treeArray[1] = newNode;
	}
	else{
		//Fix this logic so that is searches correctly
		int searchIndex = 1;
		while (treeArray[searchIndex] != nullptr){
			searchIndex = (searchIndex*2)+1;
			int numOfreps = (searchIndex / 2);
			
			while (treeArray[searchIndex] != nullptr and numOfreps >= 0){
				searchIndex--;
				numOfreps--;
			}
		}
		treeArray[searchIndex] = newNode;
	}
}
