#include "ServerInterpreter.h"
#include <iostream>

using namespace std;

string ServerInterpreter::parse(){
	LocalData ld();
	string result;
	unsigned char in = c->read();
	switch(in){
		case Protocol::COM_LIST_NG: 
			result += Protocol::ANS_LIST_NG + " ";
			vector<Newsgroup> list = ld.list_ng();
			result += list.size() + " ";
			for(Newsgroup n : list){
				result += n.newsgroupsNbr + " " + n.title + " ";
			}
			break;

		case Protocol::COM_CREATE_NG: 
			result += Protocol::ANS_CREATE_NG + " ";
			string parameter1 = parse_string();
			result += ld.create_ng(parameter1) ? Protocol::ANS_ACK : Protocol::ANS_NAK + " " + Protocol::ERR_NG_ALREADY_EXISTS;
			break;

		case Protocol::COM_DELETE_NG:
			result += Protocol::ANS_DELETE_NG + " ";
			int parameter1 = parse_number();
			result += ld.delete_ng(parameter1) ? Protocol::ANS_ACK : Protocol::ANS_NAK + " " + Protocol::ERR_NG_DOES_NOT_EXIST;
			break;

		case Protocol::COM_LIST_ART: 
			result += Protocol::ANS_LIST_ART + " ";
			int parameter1 = parse_number();
			Newsgroup ng = ld.list_a(parameter1);
			if(ng == NULL){
				result += Protocol::ANS_NAK + " " + Protocol::ERR_NG_DOES_NOT_EXIST;
			} else {
				result += ng.articles.size() + " ";
				for(Article a : ng.articles){
					result += a.articleNbr + " " + a.title + " ";
				}
			}
			break;

		case Protocol::COM_CREATE_ART:
			result += Protocol::ANS_CREATE_ART + " ";
			int parameter1 = parse_number();
			string parameter2 = parse_string();
			string parameter3 = parse_string();
			string parameter4 = parse_string();
			result += ld.create_a(parameter1, parameter2, parameter3, parameter4) ? Protocol::ANS_ACK : Protocol::ANS_NAK + " " + Protocol::ERR_NG_DOES_NOT_EXIST;
			break;

		case Protocol::COM_DELETE_ART: 
			result += Protocol::ANS_DELETE_ART + " ";
			int parameter1 = parse_number();
			int parameter2 = parse_number();
			switch(ld.delete_a(parameter1, parameter2)){
				case 0: result += Protocol::ANS_ACK; break;
				case -1: result += Protocol::ANS_NAK + " " + Protocol::ERR_ART_DOES_NOT_EXIST; break;
				case -2: result += Protocol::ANS_NAK + " " + Protocol::ERR_NG_DOES_NOT_EXIST; break;
			}
			break;

		case Protocol::COM_GET_ART: 
			result += Protocol::ANS_GET_ART + " ";
			int parameter1 = parse_number();
			int parameter2 = parse_number();
			
		default: return "nigger";
	}
	result += " " + Protocol::ANS_END;
	return result;
}