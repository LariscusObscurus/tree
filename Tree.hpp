#ifndef TREE_HPP
#define TREE_HPP

#include <map>
#include <iostream>

template <typename T>
class Tree
{
	typedef unsigned uint;
	struct Node {
		T key;
		Node* base;
		Node* left;
		Node* right;
		bool visited;
		
		Node() : key(0), base(0), left(0), right(0), visited(false)
		{
		}
		~Node()
		{
			if (left) {
				delete left;
			}
			if (right) {
				delete right;
			}
		}
	};
	Node* mNodes;
	std::map<T, Node*> mStack;
public:
	Tree() : mNodes(0)
	{
	}
	~Tree()
	{
		if (mNodes) {
			delete mNodes;
		}
	}
	
	size_t getSize() const
	{
		return mStack.size();
	}
	
	bool add(const T& key)
	{
		bool result = false;
		
		if (!mNodes) {
			try {
				mNodes = new Node();
				mNodes->key = key;
				mStack[key] = mNodes;
				return true;
			} catch (...) {
				return false;
			}
		}
		
		for (Node* it = mNodes; it;) {
			if (it && key < it->key) {
				if (it->left) {
					it = it->left;
				} else {
					result = insert(key, it);
				}
			} else if (it && key > it->key) {
				if (it->right) {
					it = it->right;
				} else {
					result = insert(key, it);
				}
			} else if (it && key == it->key) {
				return false;
			} else {
				result = false;
			}
			if (result) {
				mStack[key] = it;
				break;
			}
		}
		return result;
	}
	
	bool remove(const T& key)
	{
		return false;
	}
	
	bool isBalanced()
	{
		int bal = balanceFactor();
		return (bal > -2 && bal < 2);
	}
	
	int balanceFactor()
	{
		int left = 0;
		int right = 0;
		
		for (auto& it : mStack) {
			it.second = false;
		}
		if (mNodes->left) {
			backtrack(mNodes->left, left);
		}
		if (mNodes->right) {
			backtrack(mNodes->right, right);
		}
		return (right - left);
	}
	
	bool exist(const T& key)
	{
		return (find(key));
	}
	
	void print()
	{
		using namespace std;
		bool avl = true;
		
		for (auto& it : mStack) {
			int bal = balanceFactor(it.first);
			if (bal < 2 && bal > -2) {
				cout << "bal(" << it.first << ") = " << bal << "\n";
			} else {
				avl = false;
				cout << "bal(" << it.first << ") = " << bal << " (AVL violation!)\n";
			}
		}
		
		cout << "AVL: " << (avl ? "yes" : "no") << "\n";
		cout << "min: " << min() << ", max: " << max() << ", avg: " << average() << endl;
	}
private:
	bool insert(const T& key, Node* node)
	{
		if (key < node->key) {
			try {
				node->left = new Node();
				node->left->key = key;
				node->left->base = node;
			} catch (...) {
				return false;
			}
		} else if (key > node->key) {
			try {
				node->right = new Node();
				node->right->key = key;
				node->right->base = node;
			} catch (...) {
				return false;
			}
		} else {
			return false;
		}
		return true;
	}
	
	void backtrack(Node* node, int& result)
	{
		int count = 0;
		Node* it = node;
		
		while (true) {
			it->visited = true;
			
			if (it->left && !it->left->visited) {
				it = it->left;
				it->visited = true;
				count++;
			} else if (it->right && !it->right->visited) {
				it = it->right;
				it->visited = true;
				count++;
			} else {
				it = it->base;
				count--;
			}
			if (!it) {
				break;
			} else if (it == node && (it->left && it->left->visited) && (it->right && it->right->visited)) {
				break;
			}
			result = result < count ? count : result;
		}
	}
	
	Node* find(const T& key)
	{
		return mStack[key];
	}
	
	int balanceFactor(const T& key)
	{
		int left = 0;
		int right = 0;
		Node* node = find(key);
		
		for (auto& it : mStack) {
			it.second->visited = false;
		}
		if (node->left) {
			backtrack(node->left, left);
		}
		if (node->right) {
			backtrack(node->right, right);
		}
		
		return (right - left);
	}
	
	T min()
	{
		T result = mStack.begin()->first;
		
		for (auto& it : mStack) {
			if (result > it.first) {
				result = it.first;
			}
		}
		return result;
	}
	
	T max()
	{
		T result = mStack.begin()->first;
		
		for (auto& it : mStack) {
			if (result < it.first) {
				result = it.first;
			}
		}
		return result;
	}
	
	double average()
	{
		double result = .0;
		double div = (double) mStack.size();
		
		for (auto& it : mStack) {
			result += (double) it.first;
		}
		return (div != .0 ? result / div : .0);
	}
};

#endif