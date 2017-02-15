
#include <iostream>

// reg recursion
void bottles_recursion(unsigned long long amount)
{
	for(; amount > 0; --amount)
	{
		std::cout << amount << " bottles of beer on the wall, " << amount << " bottles of beer! Take one down, pass it around, " << amount-1 << " bottles of beer on the wall!" << std::endl;
	}
}

// tail recursion
void bottles(unsigned long long amount)
{
	if(amount != 1) std::cout << amount << " bottles of beer on the wall, " << amount << " bottles of beer! Take one down, pass it around, " << amount-1 << " bottles of beer on the wall!" << std::endl;
	else if(amount == 1) std::cout << amount << " bottle of beer on the wall, " << amount << " bottle of beer! Take one down, pass it around, " << amount-1 << " bottles of beer on the wall!" << std::endl;
	if(--amount > 0) bottles(amount);
}

int main()
{
	//bottles(99);
	bottles_recursion(99);
	return 0;
}