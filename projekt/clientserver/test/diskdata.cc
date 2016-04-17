#include "diskdata.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>

using namespace std;

string datadir = "data";





int mode = S_IRWXU;

string getArticleName(string path){
	string title = path.substr(path.find_last_of("/") + 1);
	    size_t pos = title.find_last_of(" ");
	    if (pos == string::npos){
	    	return "";
	    } 
	    return title.substr(0, pos);
	    
}


string getNewsGroup(int nbr){
	DIR *dir = opendir (datadir.c_str());

	struct dirent *pent = NULL;


	while ((pent = readdir (dir))) // while there is still something in the directory to list
    {
        string dirname(pent->d_name);
        if (dirname == "." || dirname == "..") continue; 
        string integer = dirname.substr(dirname.find_last_of(" ") + 1);
        int currentnbr = stoi(integer);

        if (nbr == currentnbr){
        	return datadir + "/" + dirname;
        	}

        }

  return "";
}

string getArticle(string dir, int nbr) {
		DIR *nestedDir = opendir(dir.c_str());
    	struct dirent *aent = NULL;

    	while ((aent = readdir(nestedDir))){
    		string aname(aent->d_name);
    		if (aname.find(" ") == string::npos) continue;
    		string integer = aname.substr(aname.find_last_of(" ") + 1);
    		int aNumber = stoi(integer);

    		if (aNumber == nbr){
    			return dir + "/" + aname;
    		}
    	}

    return "";
}


DataInterface::Article readArticle(string path, string title, int aNumber, int nNumber){
	ifstream myfile(path);
  	//myfile.open (path);
  	cout << "opening: " << path << endl;

  	if (!myfile){
  		cout << "failed to open file: " << path << endl;
  		return DataInterface::Article();
  	}
  	string file_contents { istreambuf_iterator<char>(myfile), istreambuf_iterator<char>() };
  	size_t endOfAuthor = file_contents.find(":::");

  	string author (file_contents.substr(0, endOfAuthor));
  	string text (file_contents.substr(endOfAuthor+3));
  	cout << "author: " << author << endl;
  	myfile.close();

  	DataInterface::Article a = {aNumber, nNumber, title, author, text};
  	return a;
}

void createArticle(string path, string author, string text){
	ofstream myfile;
  	myfile.open (path);
  	myfile << author << ":::";
  	myfile << text;
  	myfile.close();
	}


vector<DataInterface::Newsgroup> DiskData::list_ng(){
	DIR *dir = opendir (datadir.c_str());

	struct dirent *pent = NULL;

	vector<Newsgroup> groups;
	while ((pent = readdir (dir)))
    {
        string dirname(pent->d_name);
        if (dirname == "." || dirname == "..") continue; 
        string integer = dirname.substr(dirname.find_last_of(" "));
        int currentnbr = stoi(integer);

        groups.push_back(list_a(currentnbr));

     }

     sort(groups.begin(), groups.end(), [](const DataInterface::Newsgroup n1, const DataInterface::Newsgroup n2) { return n1.newsGroupsNbr < n2.newsGroupsNbr; });

     return groups;
}



DiskData::DiskData(){
	if (opendir (datadir.c_str()) == NULL) {
		mkdir (datadir.c_str(), mode);
  		cout << "created directory " << datadir << endl;
	}  else {
		cout << "found directory " << datadir << endl;
	}

	vector<Newsgroup> groups = list_ng();

	for (Newsgroup n : groups){
		for (Article a : n.articles){
			currentArticleIndex = max(currentArticleIndex, a.articleNbr+1);
		}
		currentGroupIndex = max(currentGroupIndex, n.newsGroupsNbr+1);
	}

	cout << "Group index: " << currentGroupIndex << endl;
	cout << "Article index: " << currentArticleIndex << endl;



}

DiskData::~DiskData(){

}

bool DiskData::create_ng(string title){
	struct dirent *pent = NULL;
	DIR *dir = opendir (datadir.c_str());

	while ((pent = readdir (dir))) 
    {
        string dirname = pent->d_name;
        if (dirname.find(title) != string::npos){
        	return false;
        }
        
    }
    string decided = datadir + "/" + title + " " + to_string(currentGroupIndex++);
	mkdir (decided.c_str(), mode);
	return true;
	

}

bool DiskData::delete_ng(int nbr){
 
	string s = getNewsGroup(nbr);

	if (s != ""){
		cout << "found the ng to delete" << endl;
		Newsgroup g = list_a(nbr);
		for (Article a : g.articles){
			delete_a(nbr, a.articleNbr);
		}
		remove(s.c_str());
		return true;
	}

	cout << "didn't find the ng to delete" << endl;
	return false;


}

DataInterface::Newsgroup DiskData::list_a(int nbr){

	Newsgroup n;
	n.newsGroupsNbr = nbr;

	string s = getNewsGroup(nbr);
	if (s != ""){
		cout << "found the ng to list" << endl;
    	DIR *nestedDir = opendir(s.c_str());

    	struct dirent *aent = NULL;

    	
    	string title = s.substr(s.find("/") + 1);
    	size_t pos = title.find_last_of(" ");
    	title = title.substr(0, pos);
    	n.title = title;

    	while ((aent = readdir(nestedDir))){
    		string aname(aent->d_name);

    		
    		if (aname == "." || aname == "..") continue;
    		string integer = aname.substr(aname.find_last_of(" "));
    		int aNumber = stoi(integer);
    		size_t pos = aname.find_last_of(" ");
    		string title = aname.substr(0, pos);
    		Article a = readArticle(s + "/" + aname, title, aNumber, nbr);
    		n.articles.push_back(a);

    	}
    	sort(n.articles.begin(), n.articles.end(), [](const DataInterface::Article a1, const DataInterface::Article a2) { return a1.articleNbr < a2.articleNbr; });

    	return n;
	}
	cout << "didn't find the ng" << endl;

	throw char(Protocol::ERR_NG_DOES_NOT_EXIST);
    

}

bool DiskData::create_a(int newsGroupsNbr, string title, string author, string text){

	Newsgroup n;
	string s = getNewsGroup(newsGroupsNbr);

	if (s != ""){
		DIR *nestedDir = opendir((s).c_str());
        	struct dirent *aent = NULL;
        	while ((aent = readdir(nestedDir))){
        		string aname(aent->d_name);

        		if (aname.find(title) != string::npos){
        			return false;
        		}
        	}

        createArticle(s + "/" + title + " " + to_string(currentArticleIndex++) + ".txt", author, text);
        return true;
	}

	return false;
	
}

int DiskData::delete_a(int newsGroupsNbr, int articleNbr){

	string s = getNewsGroup(newsGroupsNbr);
	if (s != ""){
		string a = getArticle(s, articleNbr);
		if (a != ""){
			remove(a.c_str());
			return 0;
		}
		return -1;

	}
	return -2;
}

DataInterface::Article DiskData::get_a(int newsGroupsNbr, int articleNbr){


	Newsgroup n = list_a(newsGroupsNbr);
	for (DataInterface::Article a : n.articles){
		if (a.articleNbr == articleNbr){
			return a;
		}
	}

	//string s = getNewsGroup(newsGroupsNbr);
	//if (s != ""){
	//	string a = getArticle(s, articleNbr);
	//	if (a != ""){
	//		return readArticle(s, getArticleName(a), articleNbr, newsGroupsNbr);
//
	//	}
	throw char(Protocol::ERR_ART_DOES_NOT_EXIST);
	//}

	//throw char(Protocol::ERR_NG_DOES_NOT_EXIST);

}

int not_main2(){
	DiskData d;
	d.create_ng("sdd");
	d.create_ng("asd");
	d.create_ng("sdd");
	d.create_ng("dddd");
	d.create_ng("d");
	d.create_ng("123ss");
	d.create_a(2, "hitler", "was", "cool");
	d.create_a(3, "hitler", "was", "very cool");
	for (int i = 0; i < 10; ++i){
		d.delete_ng(i);
	}

	return 0;
}