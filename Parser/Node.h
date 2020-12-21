#pragma once
#include <iostream>
#include <string>

class Node {
	std::string val;
	Node* leftChild;
	Node* rightChild;
public:
	Node();
	Node(std::string s);
	Node(std::string s, Node* a, Node* b);
	~Node() = default;
	std::string getVal();
	Node* getLeftChild();
	Node* getRightChild();
};

Node::Node()
{
	val = "";
	leftChild = NULL;
	rightChild = NULL;
}

Node::Node(std::string s)
{
	val += s;
	leftChild = NULL;
	rightChild = NULL;
}

Node::Node(std::string s, Node* a, Node* b)
{
	val += s;
	leftChild = a;
	rightChild = b;
}

inline std::string Node::getVal()
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

