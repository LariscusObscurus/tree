#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdint>
#include "Tree.hpp"

using namespace std;

int main(int argc, char** argv)
{
	Tree<int64_t> tree;
	int64_t i;
	
	if (argc != 2) {
		cerr << "usage: " << argv[0] << " filename" << endl;
		_exit(EXIT_FAILURE);
	}
	ifstream inputFile(argv[1]);
	
	if (!inputFile.good()) {
		cerr << "couldn't open input file: " << argv[1] << endl;
		_exit(EXIT_FAILURE);
	}
	while (inputFile >> i) {
		tree.add(i);
	}
	if (!tree.getSize()) {
		cerr << "couldn't create tree" << endl;
		_exit(EXIT_FAILURE);
	}
	tree.print();
	return EXIT_SUCCESS;
}