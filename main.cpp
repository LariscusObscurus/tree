#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

typedef struct node_s {
	int key;
	node_s* left;
	node_s* right;
} node_s;

template <typename T>
std::string numberToString (T Number)
{
	std::stringstream ss;
	ss << Number;
	return ss.str();
}

template <typename T>
T stringToNumber (const std::string &Text)
{
	std::stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}

bool createTree(ifstream& inputFile, node_t*& tree);
void printTree(node_t* tree);
int min(node_t* tree);
int max(node_t* tree);
int avg(node_t* tree);
bool avl(node_t* tree, int& level);

int main(int argc, char** argv)
{
	node_t* tree = 0;
	
	if (argc != 2) {
		cerr << "usage: " << argv[0] << " filename" << endl;
		_exit(EXIT_FAILURE);
	}
	ifstream inputFile(argv[1]);
	
	if (!inputFile.good()) {
		cerr << "couldn't open input file: " << argv[1] << endl;
		_exit(EXIT_FAILURE);
	}
	
	if (!createTree(inputFile, tree)) {
		cerr << "couldn't create tree" << endl;
		_exit(EXIT_FAILURE);
	}
	printTree(tree);
	delete tree;
	
	return EXIT_SUCCESS;
}

bool createTree(ifstream inputFile, node_t*& tree)
{
	list<int> lst;
	list<int>::iterator it;
	int i;
	node_t* treeIt = 0;
	
	while (inputFile >> i) {
		lst.push_back(i);
	}
	
	if (!lst.size()) {
		return false;
	}
	tree = new node_t();
	tree->key = lst.front();
	treeIt = tree;
	it = lst.begin();
	it++;
	
	while(it != lst.end()) {
		i = *it;
		
		if (i < treeIt->key) {
		} else if (i > treeIt->key) {
		}
		it++;
	}
}

void printTree(node_t* tree)
{
}

int min(node_t* tree)
{
}	

int max(node_t* tree)
{
}

int avg(node_t* tree)
{
}

bool avl(node_t* tree, int& level)
{
}