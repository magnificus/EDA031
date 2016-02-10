#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include "word.h"


class Dictionary {
public:
	Dictionary();
	bool contains(const std::string& word) const;
	std::vector<std::string> get_trigs_suggestions(const std::string& word);
	std::vector<std::string> rank_suggestions(std::vector<std::string> list, const std::string word);
	std::vector<std::string> get_suggestions(const std::string& word);
	//int calculateDist(std::string s1, std::string s2);


private:
	struct string_rating {
		std::string s;
		int rating;
		string_rating (std::string s, int rating) : s(s), rating(rating) {}
	};
	std::unordered_set<std::string> strings;
	std::vector<Word> words[100];
};

#endif
