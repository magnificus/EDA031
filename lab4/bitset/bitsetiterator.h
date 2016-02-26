/*
 * A BitsetIterator is an iterator for Bitsets.
 * Postfix ++, ==, and -> are not implemented.
 */

#ifndef BITSET_ITERATOR_H
#define BITSET_ITERATOR_H

#include "bitreference.h"
#include <iterator>

class BitsetIterator : public std::iterator<std::forward_iterator_tag, bool> {
public:
	BitsetIterator(Bitset::BitStorage* pb, std::size_t p) : ref(pb, p) {}

	BitsetIterator& operator++() {
		ref.pos++;
		return *this;
		}

	BitReference operator*(){
		return ref;
	}

	bool operator!=(const BitsetIterator& bsi) const {
		return bsi.ref.pos != this->ref.pos || bsi.ref.p_bits != this->ref.p_bits;
	}
	BitsetIterator& operator=(const BitsetIterator& rhs) {
		ref.p_bits = rhs.ref.p_bits;
		ref.pos = rhs.ref.pos;
		return *this;
	}
private:
	BitReference ref;
};



#endif
