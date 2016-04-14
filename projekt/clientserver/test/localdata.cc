#include "localdata.h"
#include "protocol.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>


bool LocalData::create_ng(string title){
	for(Newsgroup n : newsgroups){
		if(n.title == title){
			cout << n.title << " " << title << endl;
			return false;
		}
	}
	Newsgroup newG;
	newG.newsGroupsNbr = ++newsGroupsNbr;
	newG.title = title;
	newsgroups.push_back(newG);
	cout << newsgroups.size();
	return true;
}

bool LocalData::delete_ng(int nbr){
	auto pos = newsgroups.erase(remove_if(newsgroups.begin(), newsgroups.end(), [nbr](Newsgroup g){return g.newsGroupsNbr == nbr;}), newsgroups.end());
	return pos != newsgroups.end();
}

Newsgroup LocalData::list_a(int newsGroupsNbr){
	for(Newsgroup n : newsgroups){
		if(n.newsGroupsNbr == newsGroupsNbr){
			return n;
		}
	}
	throw char(Protocol::ERR_NG_DOES_NOT_EXIST);
}

bool LocalData::create_a(int newsGroupsNbr, string title, string author, string text){
	for(Newsgroup n : newsgroups){
		if(n.newsGroupsNbr == newsGroupsNbr){
			Article a;
			a.articleNbr = ++articleNbr;
			a.newsGroupsNbr = newsGroupsNbr;
			a.title = title;
			a.author = author;
			a.text = text;
			n.articles.push_back(a);
			return true;
		}
	}
	return false;
}

int LocalData::delete_a(int newsGroupsNbr, int articleNbr){

	for(Newsgroup n : newsgroups){
		if(n.newsGroupsNbr == newsGroupsNbr){
			auto pos = n.articles.erase(remove_if(n.articles.begin(), n.articles.end(), [articleNbr](Article a){return a.articleNbr == articleNbr;}), n.articles.end());
			return pos != n.articles.end() ? 0 : -1; //ArticleNbr exist?
		}
	}
	return -2; //Newsgroupsnbr does not exist
}

Article LocalData::get_a(int newsGroupsNbr, int articleNbr){
	for(Newsgroup n : newsgroups){
		if(n.newsGroupsNbr == newsGroupsNbr){
			for(Article a : n.articles){
				if(a.articleNbr == articleNbr){
					return a;
				}
			}
			throw char(Protocol::ERR_ART_DOES_NOT_EXIST);
			
		}
	}
	throw char(Protocol::ERR_NG_DOES_NOT_EXIST);
}