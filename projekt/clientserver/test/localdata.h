#include "datainterface.h"
#include <string>
using namespace std;


class LocalData : DataInterface{
public:
	LocalData() : newsGroupsNbr(0), articleNbr(0) {};
	vector<Newsgroup> list_ng(){ return newsgroups; };
	bool create_ng(string title);
	bool delete_ng(int nbr);
	Newsgroup list_a(int newsGroupsNbr);
	bool create_a(int newsGroupsNbr, string title, string author, string text);
	int delete_a(int newsGroupsNbr, int articleNbr);
	Article get_a(int newsGroupsNbr, int articleNbr);

private:
	vector<Newsgroup> newsgroups;
	int newsGroupsNbr;
	int articleNbr;
};