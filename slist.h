#ifndef SLIST_H
#define SLIST_H

#include <iterator>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

template<class T>
class slist
{
	struct Node
	{
		Node(const T& _data, Node* _next = nullptr, Node* _prev = nullptr):
			data(_data), next(_next), prev(_prev) {}

		T data;
		Node* next;
		Node* prev;
	};

	Node* tail;

	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef std::size_t size_type;

public:
	slist();
	slist(const slist<T>& other);

	class iterator;
	class const_iterator;

	slist<T>& operator=(const slist<T>& other);
	template<class E>
	friend bool operator==(const slist<E>&, const slist<E>&);
	template<class NE>
	friend bool operator!=(const slist<NE>&, const slist<NE>&);

	void swap(iterator& lhs, iterator& rhs);

	void rotate(iterator it);
	void rotate(const_iterator it);

	void reverse();

	bool equals(const slist<T>&) const;

	bool empty() const;

	size_type size() const;

	void clear();

	void add(const T&);
	void add(T&&);

	void push_back(const T&);
	void push_back(T&&);

	void pop_back();

	void push_front(const T&);
	void push_front(T&&);

	void pop_front();

	void insert(const iterator&, const T&);
	void insert(const iterator&, T&&);
	void insert(const const_iterator&, const T&);
	void insert(const const_iterator&, T&&);

	const_reference get(iterator) const;
	const_reference get(const_iterator) const;
	const std::vector<const_reference>& get(iterator, size_type) const;
	const std::vector<const_reference>& get(const_iterator, size_type) const;

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

	slist<T>& sub_list(slist<T>::iterator&, size_type);
	slist<T>& sub_list(slist<T>::const_iterator&, size_type);

	void set(const iterator&, const T&);
	void set(const iterator&, T&&);
	void set(const const_iterator&, const T&);
	void set(const const_iterator&, T&&);
	void set(const iterator&, const iterator&, const T&);
	void set(const iterator&, const iterator&, T&&);
	void set(const const_iterator&, const const_iterator&, const T&);
	void set(const const_iterator&, const const_iterator&, T&&);

	void erase(iterator&);
	void erase(const_iterator&);
	void erase(iterator&, iterator&);
	void erase(const_iterator&, const_iterator&);

	std::string to_string();

	~slist();
};



#endif