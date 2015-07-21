#ifndef TIMER_HH
#define TIMER_HH

#include <iostream>
#include <unordered_map>

#ifndef HAVE_COUNTERS
# define HAVE_COUNTERS 0
# warning Note that you have to set HAVE_COUNTERS if you want timing information. You can do this by compiling with -DHAVE_TIMERS=1
#endif

namespace Counter {

class CounterImpl;

class Collection {
	std::size_t& operator[](const std::string &id) {
		return counters[id];
	}

	~Collection(void);

	static Collection all;

	std::unordered_map< std::string, std::size_t > counters;

	friend CounterImpl;

      public:
	static void print_counters(void);
};


class CounterImpl {
      public:
	CounterImpl(void) = default;

	/* perfect forwarding */
	template < typename T >
	CounterImpl(T &&_id) {
		Collection::all[std::forward< T >(_id)]++;
	}

	template < typename T >
	void operator()(T &&_id) {
		Collection::all[std::forward< T >(_id)]++;
	}
};

struct NoopCounterImpl {
	NoopCounterImpl(void) = default;
	template < typename T > NoopCounterImpl(T&&) { };
	template < typename T > void operator()(T&&) { }
};

#if HAVE_COUNTERS

template < int urgency = 0 >
using ScopeCounter = typename std::conditional< (urgency < HAVE_COUNTERS),
				CounterImpl, NoopCounterImpl >::type;

#else

template < int urgency = 0 > using ScopeCounter = NoopCounterImpl;

#endif /* HAVE_COUNTERS */


} /* namespace Counter */


#define COUNT_THIS_SCOPE(id) Counter::ScopeCounter< 0 > counter_scope_counter_autogenerated(id)
#define COUNT_THIS_SCOPE_N(urgency, id) Counter::ScopeCounter< urgency > counter_scope_counter_autogenerated(id)

#endif /* TIMER_HH */
