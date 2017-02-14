#include "slist.h"

template<class T>
inline bool operator==(const slist<T>& lhs, const slist<T>& rhs)
{
	return lhs.tail == rhs.tail;
}
template<class T>
inline bool operator!=(const slist<T>& lhs, const slist<T>& rhs)
{
	return lhs.tail != rhs.tail;
}

template<class T>
inline bool operator==(const typename slist<T>::iterator& lhs, const typename slist<T>::iterator& rhs)
{
	return lhs.ref == rhs.ref;
}
template<class T>
inline bool operator!=(const typename slist<T>::iterator& lhs, const typename slist<T>::iterator& rhs)
{
	return lhs.ref != rhs.ref;
}

template<class T>
inline bool operator==(const typename slist<T>::const_iterator& lhs, const typename slist<T>::const_iterator& rhs)
{
	return lhs.ref == rhs.ref;
}
template<class T>
inline bool operator!=(const typename slist<T>::const_iterator& lhs, const typename slist<T>::const_iterator& rhs)
{
	return lhs.ref != rhs.ref;
}

template<class T>
class slist<T>::const_iterator:
	public std::iterator<std::bidirectional_iterator_tag, T>
{

	friend class slist;
	friend class iterator;

	using value_type = typename std::iterator<std::bidirectional_iterator_tag, T>::value_type;
	using reference = typename std::iterator<std::bidirectional_iterator_tag, T>::reference;
	using pointer = typename std::iterator<std::bidirectional_iterator_tag, T>::pointer;

public:
	const_iterator(const slist<T>::Node* _ref = nullptr):
		ref(_ref) {}
	const_iterator(const iterator& other):
		ref(other.ref) {}
	const_iterator(const const_iterator& other):
		ref(other.ref) {}

	template<class E>
	friend inline bool operator==(const typename slist<E>::const_iterator& lhs, const typename slist<E>::const_iterator& rhs);
	template<class NE>
	friend inline bool operator!=(const typename slist<NE>::const_iterator& lhs, const typename slist<NE>::const_iterator& rhs);

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
	inline const pointer operator->() const
	{
		return ref->next;
	}

	~const_iterator() {}
private:
	const Node* ref;
};

template<class T>
class slist<T>::iterator:
	public std::iterator<std::bidirectional_iterator_tag, T>,
	public slist<T>::const_iterator
{

	friend class slist;
	friend class const_iterator;


public:
	iterator(slist<T>::Node* _ref = nullptr):
		ref(_ref) {}
	iterator(const iterator& other):
		ref(other.ref) {}

	template<class E>
	friend bool operator==(const typename slist<E>::iterator& lhs, const typename slist<E>::iterator& rhs);
	template<class NE>
	friend bool operator!=(const typename slist<NE>::iterator& lhs, const typename slist<NE>::iterator& rhs);

	~iterator() {}
private:
	Node* ref;
};

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

	for(slist<T>::iterator it = other.begin();
		it != other.end();
		it++)
	{
		this->push_back(*it);
	}
}
// Destructor
template<class T>
slist<T>::~slist()
{
	clear();
	delete tail;
}

// push_back(value)			//adds a new value to the end of this list.
template<class T>
inline void slist<T>::push_back(const T& data)
	{ insert(data, end()); }

template<class T>
inline void slist<T>::push_back(T&& data)
	{ insert(data, end()); }

// pop_back() 				//erase value at end of list
template<class T>
inline void slist<T>::pop_back()
	{ erase(end()); }

// push_front(value)		//adds a new value to the start of this list
template<class T>
inline void slist<T>::push_front(const T& data)
	{ insert(data, begin()); }

template<class T>
inline void slist<T>::push_front(T&& data)
	{ insert(data, begin()); }

// pop_front()				//erase value at front of list
template<class T>
inline void slist<T>::pop_front()
	{ erase(end()); }

// clear()					//erases all elements from this list.
template<class T>
void slist<T>::clear()
{
	while(!empty())
	{
		pop_front();
	}
}

// equals(list)				//Returns true if the two lists contain the same elements in the same order.
template<class T>
bool slist<T>::equals(const slist<T>& other) const
{
	return tail == other.tail;
}

//get(index)				//Returns the element at the specified index in this list.
template<class T>
inline typename slist<T>::const_reference slist<T>::get(slist<T>::iterator pos) const
	{ return (*pos); }

template<class T>
inline typename slist<T>::const_reference slist<T>::get(slist<T>::const_iterator pos) const
	{ return (*pos); }

template<class T>
inline const std::vector<typename slist<T>::const_reference>& slist<T>::get(slist<T>::iterator pos, slist<T>::size_type count) const
{
	std::vector<typename slist<T>::const_reference> rvec;
	do
	{
		rvec.push_back(*pos);
		pos++;
	} while(count--);

	return rvec;
}

template<class T>
inline const std::vector<typename slist<T>::const_reference>& slist<T>::get(slist<T>::const_iterator pos, slist<T>::size_type count) const
{
	std::vector<typename slist<T>::const_reference> rvec;
	do
	{
		rvec.push_back(*pos);
		pos++;
	} while(count--);

	return rvec;
}

//begin()					//returns iterator to first element
template<class T>
inline typename slist<T>::iterator slist<T>::begin()
	{ return typename slist<T>::iterator(tail->next); }

template<class T>
inline typename slist<T>::const_iterator slist<T>::begin() const
	{ return typename slist<T>::const_iterator(tail->next); }

template<class T>
inline typename slist<T>::const_iterator slist<T>::cbegin() const
	{ return typename slist<T>::const_iterator(tail->next); }

//end() 					//returns iterator to last element
template<class T>
inline typename slist<T>::iterator slist<T>::end()
	{ return typename slist<T>::iterator(tail); }

template<class T>
inline typename slist<T>::const_iterator slist<T>::end() const
	{ return typename slist<T>::const_iterator(tail); }

template<class T>
inline typename slist<T>::const_iterator slist<T>::cend() const
	{ return typename slist<T>::const_iterator(tail); }

//insert(value, index)		//Inserts the element into this list before the specified index.
template<class T>
void slist<T>::insert(const typename slist<T>::iterator& pos, const T& data)
{
	Node* n = new Node(data, pos.ref, pos.ref->prev);
	pos.ref->next = n;
}

template<class T>
void slist<T>::insert(const typename slist<T>::iterator& pos, T&& data)
{
	Node* n = new Node(data, pos.ref, pos.ref->prev);
	pos.ref->next = n;
}

template<class T>
void slist<T>::insert(const typename slist<T>::const_iterator& pos, const T& data)
{
	const Node* n = new Node(data, pos.ref, pos.ref->prev);
	pos.ref->next = n;
}

template<class T>
void slist<T>::insert(const typename slist<T>::const_iterator& pos, T&& data)
{
	const Node* n = new Node(data, pos.ref, pos.ref->prev);
	pos.ref->next = n;
}

//swap(index1, index2)		//Switches the payload data of specified indexex.
template<class T>
void slist<T>::swap(slist<T>::iterator& lhs, slist<T>::iterator& rhs)
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
bool slist<T>::empty() const
	{ return tail == tail->next; }

// erase(index)				//erases the element at the specified index from this list.
template<class T>
void slist<T>::erase(slist<T>::iterator& pos)
{
	if(pos == end())
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
void slist<T>::erase(slist<T>::const_iterator& pos)
{
	if(pos == end())
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
void slist<T>::erase(slist<T>::iterator& lhs, slist<T>::iterator& rhs)
{
	while(lhs->next != rhs)
	{
		typename slist<T>::iterator tmp(*lhs);
		lhs++;
		erase(tmp);
	}
}

template<class T>
void slist<T>::erase(slist<T>::const_iterator& lhs, slist<T>::const_iterator& rhs)
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
inline void slist<T>::set(const typename slist<T>::iterator& pos, const T& _data)
	{ pos.ref->next->data = _data; }

template<class T>
inline void slist<T>::set(const typename slist<T>::iterator& pos, T&& _data)
	{ pos.ref->next->data = _data; }

template<class T>
inline void slist<T>::set(const typename slist<T>::const_iterator& pos, const T& _data)
	{ pos.ref->next->data = _data; }

template<class T>
inline void slist<T>::set(const typename slist<T>::const_iterator& pos, T&& _data)
	{ pos.ref->next->data = _data; }

template<class T>
void slist<T>::set(
	const typename slist<T>::iterator& lhs,
	const typename slist<T>::iterator& rhs,
	const T& data)
{
	while(lhs->next != rhs)
	{
		typename slist<T>::iterator tmp(*lhs);
		lhs++;
		set(tmp);
	}
}

template<class T>
void slist<T>::set(
	const typename slist<T>::iterator& lhs,
	const typename slist<T>::iterator& rhs,
	T&& data)
{
	while(lhs->next != rhs)
	{
		typename slist<T>::iterator tmp(*lhs);
		lhs++;
		set(tmp);
	}	
}

template<class T>
void slist<T>::set(
	const typename slist<T>::const_iterator& lhs,
	const typename slist<T>::const_iterator& rhs,
	const T& data)
{
	while(lhs->next != rhs)
	{
		typename slist<T>::iterator tmp(*lhs);
		lhs++;
		set(tmp);
	}
}
// size()					//Returns the number of elements in this list.
template<class T>
typename slist<T>::size_type slist<T>::size() const
{
	typename slist<T>::iterator it = begin();
	typename slist<T>::size_type count = 0;
	while(it != end())
	{
		count++;
	}
	return count;
}

// subList(start, length)	//Returns a new list containing elements from a sub-range of this list.
template<class T>
slist<T>& slist<T>::sub_list(slist<T>::iterator& pos, slist<T>::size_type count)
{

}

template<class T>
slist<T>& slist<T>::sub_list(slist<T>::const_iterator& pos, slist<T>::size_type count)
{

}

// toString()				//Converts the list to a printable string representation.
template<class T>
std::string slist<T>::to_string()
{

}