#ifndef _DATA_INTERFACE
#define _DATA_INTERFACE

#include <vector>
#include <string>

using namespace std;

struct Article {
	int articleNbr;
	int newsGroupsNbr;
	string title;
	string author;
	string text;
};

struct Newsgroup{
	int newsGroupsNbr;
	string title;
	vector<Article> articles;
};

class DataInterface{

public:	
	virtual bool create_ng(string title) = 0;
	virtual bool delete_ng(int nbr) = 0;
	virtual Newsgroup list_a(int newsGroupsNbr) = 0;
	virtual bool create_a(int newsGroupsNbr, string title, string author, string text) = 0;
	virtual int delete_a(int newsGroupsNbr, int articleNbr) = 0;
	virtual Article get_a(int newsGroupsNbr, int articleNbr) = 0;

};

#endif