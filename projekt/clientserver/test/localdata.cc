#include "localdata.h"
#include "protocol.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>



vector<DataInterface::Newsgroup> LocalData::list_ng(){
	return newsgroups;
}

int not_main(){
	LocalData d;
	d.create_ng("asd");
	d.create_ng("213123");
	d.create_ng("asda");
	d.create_ng("aszxccd");
	d.create_ng("asxxd");
	d.create_a(1, "ds1d", "dd", "bazinga");
	d.create_a(1, "sasd", "zxd", "bazinga");
	//d.delete_a(1, 1);
	vector<DataInterface::Newsgroup> groups = d.list_ng();

	for (DataInterface::Newsgroup n : groups){
		cout << "Group: " << n.title << endl;
		for (DataInterface::Article a : n.articles){
			cout << "Article: " << a.title << endl;
		}
	}
	//create
}

bool LocalData::create_ng(string title){
	for(DataInterface::Newsgroup n : newsgroups){
		if(n.title == title){
			return false;
		}
	}
	DataInterface::Newsgroup ng;
	ng.newsGroupsNbr = ++newsGroupsNbr;
	ng.title = title;
	newsgroups.push_back(ng);
	//cout << newsgroups.size() << endl;
	return true;
}

bool LocalData::delete_ng(int nbr){
	auto pos = newsgroups.erase(remove_if(newsgroups.begin(), newsgroups.end(), [nbr](Newsgroup g){return g.newsGroupsNbr == nbr;}), newsgroups.end());
	return pos != newsgroups.end();
}

DataInterface::Newsgroup LocalData::list_a(int newsGroupsNbr){
	for(DataInterface::Newsgroup n : newsgroups){
		if(n.newsGroupsNbr == newsGroupsNbr){
			return n;
		}
	}
	throw char(Protocol::ERR_NG_DOES_NOT_EXIST);
}

bool LocalData::create_a(int newsGroupsNbr, string title, string author, string text){
	for(DataInterface::Newsgroup &n : newsgroups){
		if(n.newsGroupsNbr == newsGroupsNbr){
			DataInterface::Article a;
			a.articleNbr = ++articleNbr;
			a.newsGroupsNbr = newsGroupsNbr;
			a.title = title;
			a.author = author;
			a.text = text;

			vector<DataInterface::Article> &arts = n.articles;
			arts.push_back(a);
			return true;
		}
	}
	return false;
}

int LocalData::delete_a(int newsGroupsNbr, int articleNbr){

	for(DataInterface::Newsgroup &n : newsgroups){
		if(n.newsGroupsNbr == newsGroupsNbr){
			auto pos = n.articles.erase(remove_if(n.articles.begin(), n.articles.end(), [articleNbr](Article a){return a.articleNbr == articleNbr;}), n.articles.end());
			return pos != n.articles.end() ? 0 : -1; //ArticleNbr exist?
		}
	}
	return -2; //Newsgroupsnbr does not exist
}

DataInterface::Article LocalData::get_a(int newsGroupsNbr, int articleNbr){
	for(DataInterface::Newsgroup n : newsgroups){
		if(n.newsGroupsNbr == newsGroupsNbr){
			for(DataInterface::Article a : n.articles){
				if(a.articleNbr == articleNbr){
					return a;
				}
			}
			throw char(Protocol::ERR_ART_DOES_NOT_EXIST);
			
		}
	}
	throw char(Protocol::ERR_NG_DOES_NOT_EXIST);
}