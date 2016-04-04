#include "localdata.h"


bool LocalData::create_ng(string title){
	for(Newsgroup n : newsgroups){
		if(n.title == title){
			return false;
		}
	}
	newsgroups.push_back(new Newsgroup(++newsGroupsNbr, title))
	return true;
}

bool LocalData::delete_ng(int nbr){
	auto pos = newsgroups.erase(remove(newsgroups.begin(), newsgroups.end(), nbr), newsgroups.end());
	return pos != newsgroups.end();
}

Newsgroup LocalData::list_a(int newsGroupsNbr){
	for(Newsgroup n : newsgroups){
		if(n.newsGroupsNbr == newsGroupsNbr){
			return n;
		}
	}
	return NULL;
}

bool LocalData::create_a(int newsGroupsNbr, string title, string author, string text){
	for(Newsgroup n : newsgroups){
		if(n.newsGroupsNbr == newsGroupsNbr){
			n.articles.push_back(new Article(++articleNbr, newsGroupsNbr, title, author, text));
			return true;
		}
	}
	return false;
}

int LocalData::delete_a(int newsGroupsNbr, int articleNbr){

	for(Newsgroup n : newsgroups){
		if(n.newsGroupsNbr == newsGroupsNbr){
			auto pos = n.articles.erase(remove(n.articles.begin(), n.articles.end(), articleNbr), n.articles.end());
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
		}
	}
	return NULL;
}