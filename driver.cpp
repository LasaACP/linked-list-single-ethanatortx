#include "slist.h"
#include <cstdlib>
#include <iostream>

int main()
{
	slist<int> test;

	test.push_back(10);
	test.push_front(5);
	slist<int>::iterator lhs = test.begin();
	slist<int>::iterator rhs = test.end();
	test.insert(++lhs, 7);

	slist<int> test_cpy(test);

	slist<int> sub = test.sub_list(lhs, rhs);
	sub.push_front(19);

	int limit;
	std::cin >> limit;

	for(int i = 0; i < limit; i += ( std::rand() % (limit - i + 1)))
	{
		sub.push_back(i);
	}

	slist<int>::iterator sub_lhs = sub.begin();
	slist<int>::iterator sub_rhs = sub.end();

	std::cout << sub;

	return 0;
}