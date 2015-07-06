// compile with g++ -DHAVE_COUNTERS=1 --std=c++11 main.cpp counter.cpp -o test
#include <iostream>

#include "counter.hh"

int main(void)
{
	for (int i = 0; i < 100; i+=12) {
		Counter::ScopeCounter<> sc("bla");
	COUNT_THIS_SCOPE(__PRETTY_FUNCTION__);
		std::cout << i << '\n';
		sc("main loop 2");
	}
	Counter::ScopeCounter<1> sc("only shows when HAVE_COUNTERS > 1");
	return 0;
	Counter::ScopeCounter<> sc2("doesn't show");
}
