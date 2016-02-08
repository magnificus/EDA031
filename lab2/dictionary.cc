#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "dictionary.h"


using namespace std;

int main(){
	Dictionary* d = new Dictionary();
	cout << d->contains("hello");
}

Dictionary::Dictionary() {
	ifstream file("words.txt");
	string str;
	while (getline(file, str)){
		string word = str.substr(0, str.find(" "));
		vector<string> trigs = {};

		size_t pos = 0;
		string token;
		pos = str.find(" ");
		str.erase(0, pos + 1);
		pos = str.find(" ");
		str.erase(0, pos + 1);
		while ((pos = str.find(" ")) != string::npos) {
    token = str.substr(0, pos);
		trigs.push_back(token);
    str.erase(0, pos + 1);
}


		Word* w = new Word(word, trigs);
		words[word.size()].push_back(*w);
		}

}

bool Dictionary::contains(const string& word) const {
	std::unordered_set<std::string>::const_iterator got = strings.find(word);
	return got != strings.end();

}

vector<string> Dictionary::get_suggestions(const string& word) const {
	vector<string> trigs = {};
	vector<string> suggestions = {};
	for (size_t i = 3; i <= word.length(); i++){
		trigs.push_back(word.substr(i-3,3));
	}
	u_int best_yet = 0;
	for (Word& w : words[word.size()]){
		if (w.get_matches(trigs) == best_yet){
			suggestions.push_back(*w);
		} else if (w.get_matches(trigs) > best_yet){
			suggestions = {};
			suggestions.push_back(*w);
		}
	}
	return suggestions;
}
