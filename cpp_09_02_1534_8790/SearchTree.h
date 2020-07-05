#ifndef __SEARCH_TREE_H_
#define __SEARCH_TREE_H_

#include "Tree.h"
#include "funcs.h"

template <typename T, typename Key>
class SearchTree : public BinaryTree<T, Key> {
	using typename BinaryTree<T, Key>::GetKey;
	using typename BinaryTree<T, Key>::ValueProc;
	using typename BinaryTree<T, Key>::Node;
	using BinaryTree<T, Key>::root;
	using BinaryTree<T, Key>::_getKey;
	using BinaryTree<T, Key>::_delete;
public:
	SearchTree() {}
	SearchTree(GetKey getKey, ValueProc del) : BinaryTree<T,Key>(getKey,del) {}
	SearchTree(const SearchTree&) = delete;
	SearchTree(SearchTree&&) = delete;
	SearchTree& operator=(const SearchTree&) = delete;
	SearchTree& operator=(SearchTree&&) = delete;

	// protocol for search trees
	void add(T& value) override;
	bool check(const Key& key) const override { return check(root, key); }
	T search(const Key& key) const override { return search(root, key); }
	void remove(const Key&) override;
	
	int level(const Key& key) const;
	Node* ascended(Node*);

private:
	void add(Node*, T&);
	bool check(Node* current, const Key& key) const;
	T search(Node* current, const Key& key) const;
	int level(Node* current, const Key& key) const;
	Node* getNode(Node* current, const Key& key) const;
	Node* getNode(const Key& key) const { return getNode(root, key); }
	void remove(Node* current, const Key& key);
};

template <typename T>
class SearchTreeSimple : public SearchTree<T, T> {
public:
	SearchTreeSimple() {}
	SearchTreeSimple(const SearchTreeSimple&) = delete;
	SearchTreeSimple(SearchTreeSimple&&) = delete;
	SearchTreeSimple& operator=(const SearchTreeSimple&) = delete;
	SearchTreeSimple& operator=(SearchTreeSimple&&) = delete;
};

template <typename T, typename Key>
void SearchTree<T, Key>::add(T& value) {
	// add value to binary search tree
	if (root == nullptr) {
		root = new Node(value);
	}
	else
		add(root, value);
}

template <typename T, typename Key>
bool SearchTree<T, Key>::check(Node* current, const Key& key) const {
	// see if argument value occurs in tree
	if (current == nullptr)
		return false; // not found
	if (_getKey(current->value()) == key)
		return true;
	if (_getKey(current->value()) < key)
		return check(current->right(), key);
	else
		return check(current->left(), key);
}

template <typename T, typename Key>
T SearchTree<T, Key>::search(Node* current, const Key& key) const {
	// see if argument value occurs in tree
	if (current == nullptr)
		throw "not found:"; // not found
	if (_getKey(current->value()) == key)
		return current->value();
	if (_getKey(current->value()) < key)
		return search(current->right(), key);
	else
		return search(current->left(), key);
}

template<typename T, typename Key>
int SearchTree<T, Key>::level(Node* current, const Key& key) const
{
	if (current == nullptr)
		return -1; // not found
	if (_getKey(current->value()) == key)
		return 0;
	if (_getKey(current->value()) < key)
		return 1 + level(current->right(), key);
	else
		return 1 + level(current->left(), key);
}

template <typename T, typename Key>
typename SearchTree<T, Key>::Node* SearchTree<T, Key>::getNode(Node* current, const Key& key) const {
	// see if argument value occurs in tree
	if (current == nullptr)
		throw "not found:"; // not found
	if (_getKey(current->value()) == key)
		return current;
	if (_getKey(current->value()) < key)
		return getNode(current->right(), key);
	else
		return getNode(current->left(), key);
}

template <typename T, typename Key>
void SearchTree<T, Key>::add(Node* current, T& value) {
	if (_getKey(current->value()) < _getKey(value))
		// add to right subtree
		if (current->right() == nullptr)
			current->right(new Node(value, current));
		else
			add(current->right(), value);
	else
		// add to left subtree
		if (current->left() == nullptr)
			current->left(new Node(value, current));
		else
			add(current->left(), value);
}

template <typename T, typename Key>
void SearchTree<T, Key>::remove(Node* current, const Key& key) {

	if (current->right())
	{
		Node* ascNode = ascended(current);
		mySwap(current->value(), ascNode->value());
		remove(ascNode, _getKey(ascNode->value()));
	}
	else
	{
		if (current->left())
		{
			current->left()->parent(current->parent());

			if (current->parent()->right() == current)
				current->parent()->right(current->left());
			else
				current->parent()->left(current->left());
		}
		else
		{
			if (current->parent()->right() == current)
				current->parent()->right(nullptr);
			else
				current->parent()->left(nullptr);
		}

		_delete(current->value());
		delete current;
	}
}

template<typename T, typename Key>
void SearchTree<T, Key>::remove(const Key& key)
{
	remove(getKey(key), key);
}

template <typename T, typename Key>
int SearchTree<T, Key>::level(const Key& key) const {

	return level(root, key);
}

template<typename T, typename Key>
typename SearchTree<T, Key>::Node* SearchTree<T, Key>::ascended(SearchTree<T, Key>::Node* node)
{
	if (!node || !node->right())
		return nullptr;

	if (!node->right()->left())
		return node->right();

	auto i = node->right();
	while (i->left()) { i = i->left(); };

	return i;
}

#endif // __SEARCH_TREE_H_
