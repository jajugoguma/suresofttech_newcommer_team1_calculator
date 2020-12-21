#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Node {
	string val;
	Node* leftChild;
	Node* rightChild;
public:
	Node();
	Node(string s);
	Node(string s, Node* a, Node* b);
	~Node() = default;
	string getVal();
	Node* getLeftChild();
	Node* getRightChild();
};

Node::Node()
{
	val = "";
	leftChild = NULL;
	rightChild = NULL;
}

Node::Node(string s)
{
	val += s;
	leftChild = NULL;
	rightChild = NULL;
}

Node::Node(string s, Node* a, Node* b)
{
	val += s;
	leftChild = a;
	rightChild = b;
}

inline string Node::getVal()
{
	return val;
}

inline Node* Node::getLeftChild()
{
	return leftChild;
}

inline Node* Node::getRightChild()
{
	return rightChild;
}

