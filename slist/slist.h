#ifndef SLIST_H
#define SLIST_H

#include <iostream>
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

	// assignment operator
	slist<T>& operator=(const slist<T>& other);

	// comparator specialization
	template<class E>
	friend bool operator==(const slist<E>&, const slist<E>&);
	template<class E>
	friend bool operator!=(const slist<E>&, const slist<E>&);
	template<class E>
	friend std::ostream& operator<<(std::ostream& os, const slist<E>& s_l);

	// swap the payload data of two nodes in the list
	void swap(iterator& lhs, iterator& rhs);

	// rotate the list to the provided position
	void rotate(iterator it);
	void rotate(const_iterator it);

	// reverse the list
	void reverse();

	// compare the list
	bool equals(const slist<T>&) const;

	// return true if empty
	bool empty() const;

	// return size of list
	size_type size() const;

	// clear list
	void clear();

	// append element to end of list
	void add(const T&);
	void add(T&&);

	// append element to end of list
	void push_back(const T&);
	void push_back(T&&);

	// erase last element in list
	void pop_back();

	// insert element at front of list
	void push_front(const T&);
	void push_front(T&&);

	// erase first element in list
	void pop_front();

	// insert element at position
	void insert(const iterator&, const T&);
	void insert(const iterator&, T&&);
	void insert(const const_iterator&, const T&);
	void insert(const const_iterator&, T&&);

	// return data at position
	const_reference get(const iterator&) const;
	const_reference get(const const_iterator&) const;
	// return data in range
	const std::vector<const_reference>& get(iterator&, const iterator&) const;
	const std::vector<const_reference>& get(const_iterator&, const const_iterator&) const;

	iterator begin();
	const const_iterator begin() const;
	const const_iterator cbegin() const;

	iterator end();
	const const_iterator end() const;
	const const_iterator cend() const;

	T front ();
	const T front() const;

	T back();
	const T back() const;

	// create sub list of this list
	slist<T>& sub_list(slist<T>::iterator&, size_type);
	slist<T>& sub_list(slist<T>::const_iterator&, size_type);
	slist<T>& sub_list(slist<T>::iterator&, slist<T>::iterator&);
	slist<T>& sub_list(slist<T>::const_iterator&, slist<T>::const_iterator&);

	// set data of index
	void set(iterator&, const T&);
	void set(iterator&, T&&);
	void set(const_iterator&, const T&);
	void set(const_iterator&, T&&);
	void set(iterator&, iterator&, const T&);
	void set(iterator&, iterator&, T&&);
	void set(const_iterator&, const_iterator&, const T&);
	void set(const_iterator&, const_iterator&, T&&);

	// erase data at index
	void erase(iterator);
	void erase(const_iterator);
	void erase(iterator, iterator);
	void erase(const_iterator, const_iterator);

	// convert to string
	std::string to_string();
	std::string to_string() const;

	// destroy
	~slist();
};

template<class T>
class slist<T>::const_iterator:
	virtual public std::iterator<std::bidirectional_iterator_tag, T>
{

	friend class slist;
	friend class iterator;

	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;

public:
	const_iterator(const slist<T>::Node* _ref = nullptr):
		ref(_ref) {}
	const_iterator(const iterator& other):
		ref(other.ref) {}
	const_iterator(const const_iterator& other):
		ref(other.ref) {}

	inline bool operator==(const typename slist<T>::const_iterator& rhs)
	{
		return this->ref == rhs.ref;
	}
	inline bool operator!=(const typename slist<T>::const_iterator& rhs)
	{
		return this->ref != rhs.ref;
	}

	inline const_iterator& operator=(const iterator& rhs)
	{
		this->ref = rhs.ref;
	}
	inline const_iterator& operator=(const const_iterator& rhs)
	{
		this->ref = rhs.ref;
	}

	inline const_iterator& operator++() 
	{
		ref = ref->next;
		return *this;
	}
	inline const_iterator operator++(int)
	{
		const_iterator tmp(*this);
		ref = ref->next;
		return tmp;
	}

	inline const_iterator& operator--()
	{
		ref = ref->prev;
		return *this;
	}
	inline const_iterator operator--(int)
	{
		const_iterator tmp(*this);
		ref = ref->prev;
		return tmp;
	}

	inline const reference operator*() const
	{
		return ref->next->data;
	}
	inline const Node* operator->() const
	{
		return ref->next;
	}

	~const_iterator() {}
private:
	const Node* ref;
};

template<class T>
class slist<T>::iterator:
	virtual public std::iterator<std::bidirectional_iterator_tag, T>,
	public slist<T>::const_iterator
{

	friend class slist;
	friend class const_iterator;

	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;

public:
	iterator(slist<T>::Node* _ref = nullptr):
		ref(_ref) {}
	iterator(const iterator& other):
		ref(other.ref) {}

	inline bool operator==(const typename slist<T>::iterator& rhs)
	{
		return this->ref == rhs.ref;
	}
	inline bool operator!=(const typename slist<T>::iterator& rhs)
	{
		return this->ref != rhs.ref;
	}

	inline iterator& operator=(const iterator& rhs)
	{
		this->ref = rhs.ref;
	}

	inline iterator& operator++() 
	{
		ref = ref->next;
		return *this;
	}
	inline iterator operator++(int)
	{
		iterator tmp(*this);
		ref = ref->next;
		return tmp;
	}

	inline iterator& operator--()
	{
		ref = ref->prev;
		return *this;
	}
	inline iterator operator--(int)
	{
		iterator tmp(*this);
		ref = ref->prev;
		return tmp;
	}

	inline slist<T>::iterator::reference operator*() const
	{
		return ref->next->data;
	}
	inline slist<T>::iterator::pointer operator->() const
	{
		return ref->next;
	}	

	~iterator() {}
private:
	Node* ref;
};

template<class T>
inline bool operator==(const slist<T>& lhs, const slist<T>& rhs)
{
	if(lhs.size() != rhs.size()) return 0;

	slist<int>::const_iterator lhs_it = lhs.begin();
	slist<int>::const_iterator rhs_it = rhs.begin();

	while((lhs_it != lhs.end()) && (rhs_it != rhs.end()))
	{
		if((*lhs_it) != (*rhs_it)) return false;
		lhs_it++;
		rhs_it++;
	}

	return true;
}

template<class T>
inline bool operator!=(const slist<T>& lhs, const slist<T>& rhs)
{
	if(lhs.size() != rhs.size()) return true;

	slist<int>::const_iterator lhs_it = lhs.begin();
	slist<int>::const_iterator rhs_it = rhs.begin();

	while((lhs_it != lhs.end()) && (rhs_it != rhs.end()))
	{
		if((*lhs_it) != (*rhs_it)) return true;
		lhs_it++;
		rhs_it++;
	}

	return false;
}

template<class T>
inline std::ostream& operator<<(std::ostream& os, const slist<T>& s_l)
{
	os << (s_l.to_string());
	return os;
}

// Constructor
template<class T>
slist<T>::slist():
	tail(new Node(T()))
{
	tail->next = tail;
	tail->prev = tail;
}

// copy constructor
template<class T>
slist<T>::slist(const slist<T>& other):
	tail(new Node(T()))
{
	tail->next = tail;
	tail->prev = tail;

	for(slist<T>::const_iterator it = other.begin();
		it != other.end();
		it++)
	{
		this->push_back(*it);
	}
}
// Destructor
template<class T>
inline slist<T>::~slist()
{
	clear();
	delete tail;
}

// push_back(value)			//adds a new value to the end of this list.
template<class T>
inline void slist<T>::push_back(const T& data)
	{ insert(end(), data); }

template<class T>
inline void slist<T>::push_back(T&& data)
	{ insert(end(), data); }

// pop_back() 				//erase value at end of list
template<class T>
inline void slist<T>::pop_back()
	{ erase(end()); }

// push_front(value)		//adds a new value to the start of this list
template<class T>
inline void slist<T>::push_front(const T& data)
	{ insert(begin(), data); }

template<class T>
inline void slist<T>::push_front(T&& data)
	{ insert(begin(), data); }

// pop_front()				//erase value at front of list
template<class T>
inline void slist<T>::pop_front()
	{ erase(begin()); }

// clear()					//erases all elements from this list.
template<class T>
inline void slist<T>::clear()
{
	while(!empty())
	{
		pop_front();
	}
}

// equals(list)				//Returns true if the two lists contain the same elements in the same order.
template<class T>
inline bool slist<T>::equals(const slist<T>& other) const
	{ return tail == other.tail; }

//get(index)				//Returns the element at the specified index in this list.
template<class T>
inline typename slist<T>::const_reference slist<T>::get(const slist<T>::iterator& pos) const
	{ return (*pos); }

template<class T>
inline typename slist<T>::const_reference slist<T>::get(const slist<T>::const_iterator& pos) const
	{ return (*pos); }

template<class T>
inline const std::vector<typename slist<T>::const_reference>& slist<T>::get(slist<T>::iterator& lhs, const slist<T>::iterator& rhs) const
{
	std::vector<typename slist<T>::const_reference> rvec = new std::vector<typename slist<T>::const_reference>();

	while(lhs != rhs)
	{
		rvec.push_back(*lhs);
		lhs++;
	}

	return *rvec;
	
}

template<class T>
inline const std::vector<typename slist<T>::const_reference>& slist<T>::get(slist<T>::const_iterator& lhs, const slist<T>::const_iterator& rhs) const
{
	std::vector<typename slist<T>::const_reference> rvec = new std::vector<typename slist<T>::const_reference>();
	
	while(lhs != rhs)
	{
		rvec.push_back(*lhs);
		lhs++;
	}

	return *rvec;
}

//begin()					//returns iterator to first element
template<class T>
inline typename slist<T>::iterator slist<T>::begin()
	{ return typename slist<T>::iterator(tail->next); }

template<class T>
inline const typename slist<T>::const_iterator slist<T>::begin() const
	{ return typename slist<T>::const_iterator(tail->next); }

template<class T>
inline const typename slist<T>::const_iterator slist<T>::cbegin() const
	{ return typename slist<T>::const_iterator(tail->next); }

//end() 					//returns iterator to last element
template<class T>
inline typename slist<T>::iterator slist<T>::end()
	{ return typename slist<T>::iterator(tail); }

template<class T>
inline const typename slist<T>::const_iterator slist<T>::end() const
	{ return typename slist<T>::const_iterator(tail); }

template<class T>
inline const typename slist<T>::const_iterator slist<T>::cend() const
	{ return typename slist<T>::const_iterator(tail); }

//front() 					//returns value of elemnt at front of list
template<class T>
inline T slist<T>::front()
	{ return *begin(); }
template<class T>
inline const T slist<T>::front() const
	{ return *begin(); } 

//bacK()					//returns value of element at end of list
template<class T>
inline T slist<T>::back()
	{ return *end(); }
template<class T>
inline const T slist<T>::back() const
	{ return *end(); }

//insert(value, index)		//Inserts the element into this list before the specified index.
template<class T>
inline void slist<T>::insert(const typename slist<T>::iterator& pos, const T& data)
{
	Node* n = new Node(data, pos.ref->next, pos.ref);
	if(pos.ref == tail) tail = n;
	pos.ref->next = n;
}

template<class T>
inline void slist<T>::insert(const typename slist<T>::iterator& pos, T&& data)
{
	Node* n = new Node(data, pos.ref->next, pos.ref);
	if(pos.ref == tail) tail = n;
	pos.ref->next = n;
}

template<class T>
inline void slist<T>::insert(const typename slist<T>::const_iterator& pos, const T& data)
{
	const Node* n = new Node(data, pos.ref->next, pos.ref);
	if(pos.ref == tail) tail = n;
	pos.ref->next = n;
}

template<class T>
inline void slist<T>::insert(const typename slist<T>::const_iterator& pos, T&& data)
{
	const Node* n = new Node(data, pos.ref->next, pos.ref);
	if(pos.ref == tail) tail = n;
	pos.ref->next = n;
}

//swap(index1, index2)		//Switches the payload data of specified indexex.
template<class T>
inline void slist<T>::swap(slist<T>::iterator& lhs, slist<T>::iterator& rhs)
{
	T _data = lhs.ref->data;
	lhs.ref->data = rhs.ref->data;
	rhs.ref->data = _data;
}

//reverse()					// reverse the linked circular_list (end->beginning; beginning->end)
template<class T>
void slist<T>::reverse() {
	if (this->empty()) { return; }

	Node* new_tail = tail->next->next;
	Node* i = tail->next;
	Node* p = tail;
	Node* n;

	// 	avoid out of bounds by doing one cycle before\
		terminal condition check
	do {
		n = i->next;
		i->next = p;
		p = i;
		i = n;
	} while (p != tail);

	tail = new_tail;
}

//rotate(index)				//rotates specified index to front
template<class T>
void slist<T>::rotate(typename slist<T>::iterator it)
{
	if (it == end()) return;
	Node* sent = tail->next;
	tail->next = tail->next->next;
	sent->next = it.ref->next;
	it.ref->next = sent;
	tail = it.ref;
}

template<class T>
void slist<T>::rotate(typename slist<T>::const_iterator it)
{
	if (it == cend()) return;
	Node* sent = tail->next;
	tail->next = tail->next->next;
	sent->next = it.ref->next;
	it.ref->next = sent;
	tail = it.ref;
}

// empty()					//Returns true if this list contains no elements.
template<class T>
inline bool slist<T>::empty() const
	{ return tail == tail->next; }

// erase(index)				//erases the element at the specified index from this list.
template<class T>
void slist<T>::erase(slist<T>::iterator pos)
{
	if(pos == this->end())
	{
		 pop_back();
		 return;
	}
	if(pos.ref->next == tail) tail = pos.ref;
	Node* n = pos.ref->next;
	pos.ref->next = pos.ref->next->next;
	delete n;
}

template<class T>
void slist<T>::erase(slist<T>::const_iterator pos)
{
	if(pos == this->end())
	{
		 pop_back();
		 return;
	}
	if(pos.ref->next == tail) tail = pos.ref;
	Node* n = pos.ref->next;
	pos.ref->next = pos.ref->next->next;
	delete n;
}

template<class T>
inline void slist<T>::erase(slist<T>::iterator lhs, slist<T>::iterator rhs)
{
	while(lhs->next != rhs)
	{
		typename slist<T>::iterator tmp(*lhs);
		lhs++;
		erase(tmp);
	}
}

template<class T>
inline void slist<T>::erase(slist<T>::const_iterator lhs, slist<T>::const_iterator rhs)
{
	while(lhs->next != rhs)
	{
		typename slist<T>::iterator tmp(*lhs);
		lhs++;
		erase(tmp);
	}
}

// set(index, value)		//Replaces the element at the specified index in this list with a new value.
template<class T>
inline void slist<T>::set(typename slist<T>::iterator& pos, const T& _data)
	{ pos.ref->next->data = _data; }

template<class T>
inline void slist<T>::set(typename slist<T>::iterator& pos, T&& _data)
	{ pos.ref->next->data = _data; }

template<class T>
inline void slist<T>::set(typename slist<T>::const_iterator& pos, const T& _data)
	{ pos.ref->next->data = _data; }

template<class T>
inline void slist<T>::set(typename slist<T>::const_iterator& pos, T&& _data)
	{ pos.ref->next->data = _data; }

template<class T>
void slist<T>::set(
	typename slist<T>::iterator& lhs,
	typename slist<T>::iterator& rhs,
	const T& data)
{
	while(lhs->next != rhs)
	{
		typename slist<T>::iterator tmp(lhs);
		lhs++;
		set(tmp, data);
	}
}

template<class T>
void slist<T>::set(
	typename slist<T>::iterator& lhs,
	typename slist<T>::iterator& rhs,
	T&& data)
{
	while(lhs != rhs)
	{
		typename slist<T>::iterator tmp(lhs);
		lhs++;
		set(tmp, data);
	}	
}

template<class T>
void slist<T>::set(
	typename slist<T>::const_iterator& lhs,
	typename slist<T>::const_iterator& rhs,
	const T& data)
{
	while(lhs != rhs)
	{
		typename slist<T>::iterator tmp(lhs);
		lhs++;
		set(tmp, data);
	}
}

template<class T>
void slist<T>::set(
	typename slist<T>::const_iterator& lhs,
	typename slist<T>::const_iterator& rhs,
	T&& data)
{
	while(lhs != rhs)
	{
		typename slist<T>::iterator tmp(lhs);
		lhs++;
		set(tmp, data);
	}
}
// size()					//Returns the number of elements in this list.
template<class T>
typename slist<T>::size_type slist<T>::size() const
{
	typename slist<T>::const_iterator it = begin();
	typename slist<T>::size_type count = 0;
	while(it != end())
	{
		count++;
		it++;
	}
	return count;
}

// subList(start, length)	//Returns a new list containing elements from a sub-range of this list.
template<class T>
slist<T>& slist<T>::sub_list(slist<T>::iterator& pos, slist<T>::size_type count)
{
	slist<T> *n_list = new slist<T>();

	do
	{
		n_list->push_back(*pos);
		pos++;
	} while(count--);

	return *n_list;
}

template<class T>
slist<T>& slist<T>::sub_list(slist<T>::const_iterator& pos, slist<T>::size_type count)
{
	slist<T> *n_list = new slist<T>();

	do
	{
		n_list->push_back(*pos);
		pos++;
	} while(count--);

	return *n_list;
}

template<class T>
slist<T>& slist<T>::sub_list(slist<T>::iterator& lhs, slist<T>::iterator& rhs)
{
	slist<T> *n_list = new slist<T>();

	while(lhs != rhs)
	{
		n_list->push_back(*lhs);
		lhs++;
	}

	return *n_list;
}

template<class T>
slist<T>& slist<T>::sub_list(slist<T>::const_iterator& lhs, slist<T>::const_iterator& rhs)
{
	slist<T> *n_list = new slist<T>();

	while(lhs != rhs)
	{
		n_list->push_back(*lhs);
		lhs++;
	}

	return *n_list;
}

// toString()				//Converts the list to a printable string representation.
template<class T>
std::string slist<T>::to_string()
{
	std::stringstream ss;

	int count = 0;

	for(slist<T>::iterator it = begin();
		it != end();
		++it)
	{
		ss << (*it) << ' ';
	}

	return ss.str();
}

template<class T>
std::string slist<T>::to_string() const
{
	std::stringstream ss;

	int count = 0;

	for(slist<T>::const_iterator it = begin();
		it != end();
		++it)
	{
		ss << (*it) << ' ';
	}

	return ss.str();
}

#endif