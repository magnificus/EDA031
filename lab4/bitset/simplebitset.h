/*
 * A SimpleBitset is an "array of bits", stored in a word (unsigned
 * long). The word contains BPW ("bits per word") bits.
*/

#ifndef SIMPLE_BITSET_H
#define SIMPLE_BITSET_H

#include <cstddef> /* size_t */
#include <limits>  /* numeric_limits */
using namespace std;

class SimpleBitset{
public:
	SimpleBitset();
	size_t size() const;
	bool get(size_t pos) const;
	void set(size_t pos, bool b);
	bool operator[](size_t idx);


private:
	using BitStorage = unsigned long;
	BitStorage bits;
	static const std::size_t
	    BPW = std::numeric_limits<BitStorage>::digits;
};

#endif
