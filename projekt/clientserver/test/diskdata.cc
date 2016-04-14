#include "diskdata.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

string datadir = "data";


int mode = S_IRWXU;

Article readArticle(string path, string title, int aNumber, int nNumber){
	ifstream myfile;
  	myfile.open (path);

  	string author;
  	string text;
  	getline(myfile, author);
  	getline(myfile, text);
  	myfile.close();

  	Article a = {aNumber, nNumber, title, author, text};
  	return a;

  	//struct Article {
	//int articleNbr;
	//int newsGroupsNbr;
	//string title;
	//string author;
	//string text;
}

void createArticle(string path, string author, string text){
	ofstream myfile;
  	myfile.open (path);
  	myfile << author << endl;
  	myfile << text << endl;
  	myfile.close();
	}


DiskData::DiskData(){
	if (opendir (datadir.c_str()) == NULL) {
		mkdir (datadir.c_str(), mode);
		//opendir (datadir.c_str());	
  		cout << "created directory" << endl;
	}  else {
		cout << "found directory" << endl;
	}

}

DiskData::~DiskData(){
}

bool DiskData::create_ng(string title){
	const char* dirtitle = datadir.c_str();
	struct dirent *pent = NULL;
	DIR *dir = opendir (datadir.c_str());

	while (pent = readdir (dir)) // while there is still something in the directory to list
    {
        string dirname = pent->d_name;
        cout << dirname << endl;
        if (dirname.find(title) != string::npos){
        	return false;
        }
    }
    string decided = datadir + "/" + title + " " + to_string(currentGroupIndex++);
	mkdir (decided.c_str(), mode);
	return true;
	

}

bool DiskData::delete_ng(int nbr){
	DIR *dir = opendir (datadir.c_str());

	struct dirent *pent = NULL;

	while (pent = readdir (dir)) // while there is still something in the directory to list
    {
        string dirname(pent->d_name);
        if (dirname == "." || dirname == "..") continue;
        cout << dirname << endl;
        
        string integer = dirname.substr(dirname.find(" "));
        int currentnbr = stoi(integer);
        if (nbr == currentnbr){
        	cout << "found the ng to delete" << endl;
        	remove((datadir + "/" + pent->d_name).c_str());
        	return true;
        }
    }
    cout << "didn't find the ng to delete" << endl;
	return false;

}

Newsgroup DiskData::list_a(int nbr){
	DIR *dir = opendir (datadir.c_str());


	Newsgroup n;
	struct dirent *pent = NULL;

	while (pent = readdir (dir)) // while there is still something in the directory to list
    {
        string dirname(pent->d_name);
        if (dirname == "." || dirname == "..") continue;        
        string integer = dirname.substr(dirname.find(" "));
        int currentnbr = stoi(integer);
        if (nbr == currentnbr){
        	cout << "found the ng to print" << endl;
        	DIR *nestedDir = opendir((datadir + "/" + dirname).c_str());

        	struct dirent *aent = NULL;

        	while (aent = readdir(nestedDir)){
        		string aname(pent->d_name);

        		string integer = dirname.substr(dirname.find(" "));
        		int aNumber = stoi(integer);

        		if (dirname == "." || dirname == "..") continue;

        		Article a = (readArticle(datadir + "/" + dirname + "/" + aname, "bazinga", aNumber, currentnbr));

        	}
        }
    }
    cout << "didn't find the ng to delete" << endl;
	return Newsgroup();

}

bool DiskData::create_a(int newsGroupsNbr, string title, string author, string text){
	DIR *dir = opendir (datadir.c_str());


	Newsgroup n;
	struct dirent *pent = NULL;

	while (pent = readdir (dir)) // while there is still something in the directory to list
    {
        string dirname(pent->d_name);
        if (dirname == "." || dirname == "..") continue;        
        string integer = dirname.substr(dirname.find(" "));
        int currentnbr = stoi(integer);
        if (newsGroupsNbr == currentnbr){
        	cout << "found the ng where to place the article" << endl;
        	DIR *nestedDir = opendir((datadir + "/" + dirname).c_str());
        	struct dirent *aent = NULL;

        	while (aent = readdir(nestedDir)){
        		string aname(pent->d_name);

        		string integer = dirname.substr(dirname.find(" "));
        		int aNumber = stoi(integer);

        		if (aname.find(title) != string::npos){
        			cout << "An article with the same name was found" << endl;
        			return false;
        		}
        	}

        	createArticle(datadir + "/" + dirname + "/" + title + " " + to_string(currentArticleIndex++) + ".txt", author, text);
			return true;
        }
    }
	return false;
}

int DiskData::delete_a(int newsGroupsNbr, int articleNbr){

	return 0;
}

Article DiskData::get_a(int newsGroupsNbr, int articleNbr){

	return Article();
}

int main(){
	DiskData d;
	d.create_ng("niggers");
	d.create_a(0, "hitler", "was", "cool");
	//d.delete_ng(1);
}