#ifndef _DATA_INTERFACE
#define _DATA_INTERFACE

#include <vector>
#include <string>

using namespace std;


class DataInterface{



public:	
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

	virtual bool create_ng(string title) = 0;
	virtual bool delete_ng(int nbr) = 0;
	virtual Newsgroup list_a(int newsGroupsNbr) = 0;
	virtual bool create_a(int newsGroupsNbr, string title, string author, string text) = 0;
	virtual int delete_a(int newsGroupsNbr, int articleNbr) = 0;
	virtual Article get_a(int newsGroupsNbr, int articleNbr) = 0;

};
//extern vector<DataInterface::Article> DataInterface::Newsgroup::articles;

#endif