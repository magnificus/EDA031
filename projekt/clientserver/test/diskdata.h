#include "datainterface.h"
#include <dirent.h>
#include <string>
#include "protocol.h"

using namespace std;

class DiskData : DataInterface {


public:
	DiskData();
	~DiskData();
	vector<Newsgroup> list_ng();
	bool create_ng(string title);
	bool delete_ng(int nbr);
	Newsgroup list_a(int newsGroupsNbr);
	bool create_a(int newsGroupsNbr, string title, string author		, string text);
	int delete_a(int newsGroupsNbr, int articleNbr);
	Article get_a(int newsGroupsNbr, int articleNbr);

private:
	int currentGroupIndex = 0;
	int currentArticleIndex = 0;

};