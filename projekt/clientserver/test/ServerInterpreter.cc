#include "ServerInterpreter.h"
#include <iostream>

using namespace std;

string ServerInterpreter::parse(){
	LocalData ld;
	string result, parameter1, parameter2, parameter3, parameter4;
	int intParam1, intParam2;
	unsigned char in = c->read();
	switch(in){
		case Protocol::COM_LIST_NG: {
			result += Protocol::ANS_LIST_NG + " ";
			vector<Newsgroup> list = ld.list_ng();
			result += list.size() + " ";
			for(Newsgroup n : list){
				result += n.newsGroupsNbr + " " + n.title + " ";
			}
		}
		break;


		case Protocol::COM_CREATE_NG: {
			result += Protocol::ANS_CREATE_NG + " ";
			parameter1 = parse_string();
			result += ld.create_ng(parameter1) ? to_string(Protocol::ANS_ACK) : Protocol::ANS_NAK + " " + Protocol::ERR_NG_ALREADY_EXISTS;
		}
		break;

		case Protocol::COM_DELETE_NG: {
			result += Protocol::ANS_DELETE_NG + " ";
			intParam1 = parse_number();
			result += ld.delete_ng(intParam1) ? to_string(Protocol::ANS_ACK) : Protocol::ANS_NAK + " " + Protocol::ERR_NG_DOES_NOT_EXIST;
		}	
		break;

		case Protocol::COM_LIST_ART: {
			result += Protocol::ANS_LIST_ART + " ";
			intParam1 = parse_number();
			Newsgroup ng = ld.list_a(intParam1);
			try {
				result += ng.articles.size() + " ";
				for(Article a : ng.articles){
					result += a.articleNbr + " " + a.title + " ";
				}
			} catch (invalid_argument& e){
				result += Protocol::ANS_NAK + " " + Protocol::ERR_NG_DOES_NOT_EXIST;
			}
		}	
		break;

		case Protocol::COM_CREATE_ART: {
			result += Protocol::ANS_CREATE_ART + " ";
			intParam1 = parse_number();
			parameter2 = parse_string();
			parameter3 = parse_string();
			parameter4 = parse_string();
			result += ld.create_a(intParam1, parameter2, parameter3, parameter4) ? to_string(Protocol::ANS_ACK) : Protocol::ANS_NAK + " " + Protocol::ERR_NG_DOES_NOT_EXIST;
		}	
		break;

		case Protocol::COM_DELETE_ART: {
			result += Protocol::ANS_DELETE_ART + " ";
			intParam1 = parse_number();
			intParam2 = parse_number();
			switch(ld.delete_a(intParam1, intParam2)){
				case 0: result += Protocol::ANS_ACK; break;
				case -1: result += Protocol::ANS_NAK + " " + Protocol::ERR_ART_DOES_NOT_EXIST; break;
				case -2: result += Protocol::ANS_NAK + " " + Protocol::ERR_NG_DOES_NOT_EXIST; break;
			}
		}	
		break;

		case Protocol::COM_GET_ART: {
			result += Protocol::ANS_GET_ART + " ";
			intParam1 = parse_number();
			intParam2 = parse_number();
			try {
				Article a = ld.get_a(intParam1, intParam2);
				result += a.title + " " + a.author + " " + a.text;
			} catch(invalid_argument& e){
				result += Protocol::ANS_NAK + " " + Protocol::ERR_ART_DOES_NOT_EXIST;
			} catch(domain_error& a){
				result += Protocol::ANS_NAK + " " + Protocol::ERR_NG_DOES_NOT_EXIST;
			}
		}	
		break;

		default: return "nigger";
	}
	result += " " + Protocol::ANS_END;
	return result;
}