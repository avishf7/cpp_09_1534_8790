/*
File: Tree.h
Description:
Course: 150018 C++ Workshop, Exercise 9, Question 2
Author: Dan Zilberstein
Students: eli ialoz 311201354
		& avishay farkash 205918790
*/
#pragma once
#include <iostream>
#include "funcs.h"

enum Mode { PREORDER, INORDER, POSTORDER };

//-----------------------------------
// class BinaryTree (Binary Trees)
// process nodes in Pre/In/Post order
//-----------------------------------
template <typename T, typename Key>
class BinaryTree {
	Mode _mode;

protected:
	//--------------------------------------------------------
	// inner class Node
	// a single Node from a binary tree
	//--------------------------------------------------------
	class Node {
	protected:
		Node* _parent;
		Node* _left;
		Node* _right;
		T _value;
	public:
		Node(T& value, Node* const parent = nullptr, Node* const left = nullptr, Node* const right = nullptr)
			: _value(value), _parent(parent), _left(left), _right(right) {}
		T& value() { return this->_value; }
		void value(const T& value) { _value = value; }
		Node* parent() const { return _parent; }
		void parent(Node* node) { _parent = node; }
		Node* left() const { return _left; }
		void left(Node* node) { _left = node; }
		Node* right() const { return _right; }
		void right(Node* node) { _right = node; }

	}; //end of Node class


	using GetKey = Key(*)(const T&);
	using ValueProc = void(*)(T&);

	GetKey _getKey;
	ValueProc _delete;

	Node* root;
	virtual void process(Node& node, ValueProc process) const { process(node.value()); }

public:

	BinaryTree(GetKey getKey, ValueProc del)
		: root(nullptr), _mode(INORDER), _getKey(getKey), _delete(del) {}
	BinaryTree() : BinaryTree([](const T& value) { return static_cast<Key>(value); },
		[](T& value) {}) {}

	virtual ~BinaryTree() { if (root != nullptr) clear(root); }

	BinaryTree(const BinaryTree&) = delete;
	BinaryTree(BinaryTree&&) = delete;
	BinaryTree& operator=(const BinaryTree&) = delete;
	BinaryTree& operator=(BinaryTree&&) = delete;

	void mode(Mode mode) { _mode = mode; }
	Mode mode() const { return _mode; }

	bool isEmpty() const { return root == nullptr; }
	void clear() { clear(root); root = nullptr; }
	void process(ValueProc) const;
	void process() const { process([](T& value) { std::cout << value << " "; }); };

	virtual void add(T&) = 0;
	virtual bool check(const Key&) const = 0;
	virtual T search(const Key&) const = 0;
	virtual void remove(const Key&) = 0;

private:
	void preOrder(ValueProc process) const { preOrder(root, process); }
	void inOrder(ValueProc process) const { inOrder(root, process); }
	void postOrder(ValueProc process) const { postOrder(root, process); }
	void clear(Node*);
	int leaves(Node*) const;
	int height(Node*) const;
	void swapSons(Node*);
	void reflect(Node*);
	int onlyLeftSons(Node*) const;
	void preOrder(Node*, ValueProc) const;
	void inOrder(Node*, ValueProc) const;
	void postOrder(Node*, ValueProc) const;

public:

	int leaves() const;
	int height() const;
	int onlyLeftSons() const;
	void reflect();



};

//----------------------------------------------------------
// class BinaryTree implementation
//----------------------------------------------------------
template <typename T, typename Key>
void BinaryTree<T, Key>::clear(Node* current) {
	if (current != nullptr) { // Release memory associated with children
		clear(current->left());
		clear(current->right());
		_delete(current->value());
		delete current;
	}
}

template<typename T, typename Key>
int BinaryTree<T, Key>::leaves(Node* node) const
{
	if (!node)
		return 0;

	if (!node->right() && !node->left())
		return 1;

	return leaves(node->right()) + leaves(node->left());
}

template<typename T, typename Key>
int BinaryTree<T, Key>::height(Node* node) const
{
	if (!node)
		return -1;

	return max<int>(1 + height(node->left()), 1 + height(node->right()));
}

template<typename T, typename Key>
void BinaryTree<T, Key>::swapSons(Node* node)
{
	Node& temp = *(node->left());
	node->left(node->right());
	node->right(&temp);
}

template<typename T, typename Key>
void BinaryTree<T, Key>::reflect(Node* node)
{
	if (!node)
		return;

	swapSons(node);
	reflect(node->left());
	reflect(node->right());
}

template<typename T, typename Key>
int BinaryTree<T, Key>::onlyLeftSons(Node* node) const
{
	if (!node || (!node->right() && !node->left()))
		return 0;

	if (node->left() && !node->right())
		return (1 + onlyLeftSons(node->left()));

	return onlyLeftSons(node->left()) + onlyLeftSons(node->right());
}

// preOrder processing of tree rooted at current
template <typename T, typename Key>
void BinaryTree<T, Key>::preOrder(Node* current, ValueProc proc) const {
	// visit Node, left child, right child
	if (current != nullptr) { // process current Node
		process(*current, proc);
		// then visit children
		preOrder(current->left(), proc);
		preOrder(current->right(), proc);
	}
}
// inOrder processing of tree rooted at current
template <typename T, typename Key>
void BinaryTree<T, Key>::inOrder(Node* current, ValueProc proc) const {
	// visit left child, Node, right child
	if (current != nullptr) {
		inOrder(current->left(), proc);
		process(*current, proc);
		inOrder(current->right(), proc);
	}
}
// postOrder processing of tree rooted at current
template <typename T, typename Key>
void BinaryTree<T, Key>::postOrder(Node* current, ValueProc proc) const {
	// visit left child, right child, node
	if (current != nullptr) {
		postOrder(current->left(), proc);
		postOrder(current->right(), proc);
		process(*current, proc);
	}
}

template <typename T, typename Key>
void BinaryTree<T, Key>::process(ValueProc process) const {
	switch (_mode) {
	case PREORDER:
		preOrder(process);
		break;
	case INORDER:
		inOrder(process);
		break;
	case POSTORDER:
		postOrder(process);
		break;
	}
}

template <typename T, typename Key>
int BinaryTree<T, Key>::leaves()  const {
	return leaves(root);
}

template <typename T, typename Key>
int BinaryTree<T, Key>::height() const {
	return height(root);
}

template <typename T, typename Key>
int BinaryTree<T, Key>::onlyLeftSons()  const {
	return onlyLeftSons(root);
}

template <typename T, typename Key>
void BinaryTree<T, Key>::reflect() {
	reflect(root);
}






