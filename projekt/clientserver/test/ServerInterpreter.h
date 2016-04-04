#include "GeneralInterpreter.h"
#include <vector>

using namespace std;

struct Article {
	int articleNbr;
	int newsGroupNbr;
	string title;
	string author;
	string text;
};

struct Newsgroup {
	int newsGroupNbr;
	string groupName;
	vector<Article> articles;
};

class ServerInterpreter : GeneralInterpreter{
public:
	ServerInterpreter(shared_ptr<Connection> conn) : GeneralInterpreter(conn) {};

	string parse();
private: 
	vector<Newsgroup> nGroups;
};


