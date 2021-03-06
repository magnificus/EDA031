#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <list>
#include "dictionary.h"


using namespace std;

typedef std::pair<std::string, int> ratings_pair;

int main(){
	Dictionary dict;
	string word;
	while (cin >> word) {
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		if (dict.contains(word)) {
			cout << "Correct." << endl;
		} else {
			vector<string> suggestions = dict.get_suggestions(word);
			if (suggestions.empty()) {
				cout << "Wrong, no suggestions." << endl;
			} else {
				cout << "Wrong. Suggestions:" << endl;
				for (const auto& w : suggestions) {
					cout << "    " << w << endl;
				}
			}
		}
	}
}

Dictionary::Dictionary() {
	ifstream file("words.txt");
	string str;
	while (getline(file, str)){
		string word = str.substr(0, str.find(" "));
		vector<string> trigs = {};
		strings.insert(word);

		size_t pos = 0;
		string token;
		pos = str.find(" ");
		str.erase(0, pos + 1);
		//pos = str.find(" ");
	//	str.erase(0, pos + 1);
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

vector<string> Dictionary::get_trigs_suggestions(const string& word) {
	vector<string> trigs = {};
	vector<string> suggestions = {};
	for (size_t i = 3; i <= word.length(); i++){
		trigs.push_back(word.substr(i-3,3));
	}
	sort(trigs.begin(), trigs.end());
	u_int best_yet = 0;

	for (int i = -1; i <= 1; i++){
		for (Word w : words[word.size()+i]){
			if (w.get_matches(trigs) == best_yet){
				suggestions.push_back(w.get_word());
			} else if (w.get_matches(trigs) > best_yet){
				best_yet = w.get_matches(trigs);
				suggestions.clear();
				suggestions.push_back(w.get_word());
			}
		}
	}

	return suggestions;
}





int calculateDist(const std::string s1,const std::string s2){
	const std::size_t len1 = s1.size(), len2 = s2.size();
	std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

	d[0][0] = 0;
	for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
	for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

	for(unsigned int i = 1; i <= len1; ++i)
		for(unsigned int j = 1; j <= len2; ++j)
                      d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });
	return d[len1][len2];
}

vector<string> Dictionary::rank_suggestions(vector<string> list, const string word){
	std::list<ratings_pair> ratings = {};
	for (string s : list){
		int result = calculateDist(s, word);
		ratings_pair my_pair = make_pair(s, result);
		ratings.push_back(my_pair);
	}

	ratings.sort([](const ratings_pair& a, const ratings_pair& b) {return a.second < b.second;});
	vector<string> out = {};
	for (pair<string, int> p : ratings){
		out.push_back(p.first);
	}
	return out;
}

vector<std::string> Dictionary::get_suggestions(const string& word){
	vector<string> sugg = rank_suggestions(get_trigs_suggestions(word), word);


	sugg.resize(5);

	return sugg;
	//return sugg;
	//return (sugg, word);
}
