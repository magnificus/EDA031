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
	std::vector<std::string> get_suggestions(const std::string& word) const;
private:
	std::unordered_set<std::string> strings;
	std::vector<Word> words[100];
};

#endif
