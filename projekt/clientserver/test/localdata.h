#include <vector>

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

class LocalData{
public:
	LocalData(){};
	vector<Newsgroup> list_ng(){ return newsgroups; };
	bool create_ng(string title);
	bool delete_ng(int nbr);
	Newsgroup list_a(int newsGroupsNbr);
	bool create_a(int newsGroupsNbr, string title, string author, string text);
	int delete_a(int newsGroupsNbr, int articleNbr);
	Article get_a(int newsGroupsNbr, int articleNbr);


private:
	vector<Newsgroup> newsgroups;
	int newsGroupsNbr = 0;
	int articleNbr = 0;
}