#include "slist.h"
#include <iostream>

int main()
{
	slist<int> test;

	test.push_back(10);
	test.push_front(5);
	slist<int>::iterator lhs = test.begin();
	slist<int>::iterator rhs = test.end();
	test.insert(++lhs, 7);

	slist<int> sub = test.sub_list(lhs, rhs);

	sub.push_front(19);

	std::cout << test.to_string() << std::endl;
	std::cout << sub.to_string() << std::endl;

	slist<int>::iterator sub_lhs = sub.begin();
	slist<int>::iterator sub_rhs = sub.end();

	sub.set(sub_lhs, 0);

	std::cout << sub.to_string() << std::endl;

	sub.set(sub_lhs, sub_rhs, 0);

	std::cout << sub.to_string() << std::endl;
}