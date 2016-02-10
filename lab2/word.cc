#include <string>
#include <vector>
#include "word.h"
#include <iostream>


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

	//cout << t.size();
	while (counter1 < t.size() && counter2 < triagrams.size()){
		if (t[counter1].compare(triagrams[counter2]) == 0){
			resultCounter++;
			counter1++;
			counter2++;
		}
		else if (t[counter1].compare(triagrams[counter2]) < 0){
			counter1++;
		} else{
			counter2++;
		}
	}
	//cout << resultCounter;
	return resultCounter;
}
