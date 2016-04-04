#include "datainterface.h"

using namespace std;


class LocalData : DataInterface{
public:
	LocalData(){};
	vector<Newsgroup> list_ng(){ return newsgroups; };

private:
	vector<Newsgroup> newsgroups;
	int newsGroupsNbr = 0;
	int articleNbr = 0;
};