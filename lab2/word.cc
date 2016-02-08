#include <string>
#include <vector>
#include "word.h"

using namespace std;

Word::Word(const string& w, const vector<string>& t) : myWord(w), triagrams(t) {

}

string Word::get_word() const {
	return myWord;
}

unsigned int Word::get_matches(const vector<string>& t) const {
	int resultCounter = 0;
	size_t counter1 = 0;
	size_t counter2 = 0;
	while (counter1 < t.size() && counter2 < triagrams.size()){
		if (t[counter1] == triagrams[counter2]){
			resultCounter++;
		}
		if (t[counter1] < triagrams[counter2]){
			counter1++;
		} else{
			counter2++;
		}
	}
	return resultCounter;
}
