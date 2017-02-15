#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>

template<class T>
class btree
{
	struct Node
	{
		Node(const T& _data, Node* _left = nullptr, Node* _right = nullptr):
			data(_data), left(_left), right(_right) {}
		T data;
		// TODO; Node structuring
		Node* left;
		Node* right;
	};

	int count_nodes(Node*);
	btree(std::initializer_list<Node>);

public:

	btree();
	btree(const btree<T>&);

	template<class E>
	friend std::ostream& operator<<(std::ostream&, typename btree<E>::Node*);
	template<class E>
	friend std::istream& operator>>(std::istream&, const btree<E>&);

	iterator insert(const T& data);
	const_iterator insert(const T& data) const;

	std::string to_string();

private:
	Node* root;
};

template<class T>
btree<T>::btree():
	root(new btree<T>::Node(T())) {}

template<class T>
btree<T>::btree(const btree<T>& other):
	root(new btree<T>::Node(T()))
{
	std::ostream& feed;
	feed << other.root;
	for(std::getline())
}

template<class T>
std::ostream& operator<<(std::ostream& os, typename btree<T>::Node* root)
{
	if(root != nullptr)
	{
		os << root->data << ' ';
		os << (root->left);
		os << (root->right);
	}

	return os;
}

template<class T>
std::istream& operator>>(std::istream& is, btree<T>& rhs)
{
	std::stringstream ss(is);
	
}

template<class T>
int btree<T>::count_nodes(Node* root)
{
	if(root == nullptr)
	{
		return 0;
	}
	else
	{
		int count = 1;
		count += count_nodes(root->left);
		count += count_nodes(root->right);

		return count;
	}
}

/*
template<class T>
std::ostream& btree<T>::get_data(std::ostream& os, Node* root)
{
	if(root != NULL)
	{
		os << root->item;
		to_string(os, root->left);
		to_string(os, root->right);
	}

	return os;
}*/

template<class T>
std::string btree<T>::to_string()
{
	std::stringstream ss;
}

#endif

/*
class Btree
{
	private:
		Node *root;
	public:
		btree();
		void insert();
		static Node* search();
		void remove();
		void clear();
		static void display(Node *root) ;
		static void deltree(Node *root) ;
		~btree();
} ;*/