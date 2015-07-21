#include <iomanip>
#include <vector>
#include <algorithm>

#include "counter.hh"

namespace Counter {

Collection Collection::all;

void
Collection::print_counters(void)
{
	if (all.counters.empty())
		return;
	std::clog << std::fixed;
	std::vector< std::string > keys;
	for (auto &&keyval : all.counters)
		keys.push_back(keyval.first);
	std::sort(keys.begin(), keys.end());
	std::clog << "\v---------------------------   Counter information   ----------------------------\n";
	for (auto &&key : keys)
		std::clog << std::setw(16) << all[key] << " | " << key << '\n';
	std::clog << "--------------------------------------------------------------------------------\n";
}

Collection::~Collection(void)
{
	print_counters();
}

}
