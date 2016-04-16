#include "ServerInterpreter.h"
#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

void ServerInterpreter::parse(){
	static LocalData ld;
	//vector<DataInterface::Article> DataInterface::Newsgroup::articles;
	string result, parameter1, parameter2, parameter3, parameter4;
	int intParam1, intParam2;
	unsigned char in = c->read();
	switch(in){
		case Protocol::COM_LIST_NG: {

			if(c->read() == Protocol::COM_END){
				c->write(Protocol::ANS_LIST_NG);
				vector<DataInterface::Newsgroup> list = ld.list_ng();
				write_number(list.size());
				cout << list.size() << endl;
				for(DataInterface::Newsgroup n : list){
					write_number(n.newsGroupsNbr);
					write_string(n.title);
				}
			}
		}
		//ANS_LIST_NG PAR_NUM size PAR_NUM n1 PAR_STR s1 PAR_NUM n2 PAR_STR s2
		break;

//COM_CREATE_NG PAR_STRING string COM_END
		case Protocol::COM_CREATE_NG: {
			parameter1 = parse_string();
			if(c->read() == Protocol::COM_END){
				c->write(Protocol::ANS_CREATE_NG);
				if(ld.create_ng(parameter1)){
					c->write(Protocol::ANS_ACK);
				} else {
					c->write(Protocol::ANS_NAK);
					c->write(Protocol::ERR_NG_ALREADY_EXISTS);
				}
			}
		}
		break;

		case Protocol::COM_DELETE_NG: {
			intParam1 = parse_number();
			if(c->read() == Protocol::COM_END){
				c->write(Protocol::ANS_DELETE_NG);
				if(ld.delete_ng(intParam1)){
					c->write(Protocol::ANS_ACK);
				} else {
					c->write(Protocol::ANS_NAK);
					c->write(Protocol::ERR_NG_DOES_NOT_EXIST);
				}
			}			
		}	
		break;

		case Protocol::COM_LIST_ART: {
			intParam1 = parse_number();
			if(c->read() == Protocol::COM_END){
				c->write(Protocol::ANS_LIST_ART);
				try {
					DataInterface::Newsgroup ng = ld.list_a(intParam1);
					c->write(Protocol::ANS_ACK);
					write_number(ng.articles.size());
					for(DataInterface::Article a : ng.articles){
						write_number(a.articleNbr);
						write_string(a.title);
					}
				} catch (char e){
					c->write(Protocol::ANS_NAK);
					c->write(e);
				}
			}
		}	
		break;
		//ANS_LIST_ART ANS_ACK PAR_NUM size PAR_NUM a1 PAR_STR s1 ANS_END

		case Protocol::COM_CREATE_ART: {
			intParam1 = parse_number();
			parameter2 = parse_string();
			parameter3 = parse_string();
			parameter4 = parse_string();
			if(c->read() == Protocol::COM_END){
				c->write(Protocol::ANS_CREATE_ART);
				if(ld.create_a(intParam1, parameter2, parameter3, parameter4)){
					c->write(Protocol::ANS_ACK);
				} else {
					c->write(Protocol::ANS_NAK);
					c->write(Protocol::ERR_NG_DOES_NOT_EXIST);
				}
			}
		}	
		break;

		case Protocol::COM_DELETE_ART: {
			intParam1 = parse_number();
			intParam2 = parse_number();
			if(c->read() == Protocol::COM_END){
				c->write(Protocol::ANS_DELETE_ART);
				switch(ld.delete_a(intParam1, intParam2)){
					case 0: c->write(Protocol::ANS_ACK); break;
					case -1: c->write(Protocol::ANS_NAK); c->write(Protocol::ERR_ART_DOES_NOT_EXIST); break;
					case -2: c->write(Protocol::ANS_NAK); c->write(Protocol::ERR_NG_DOES_NOT_EXIST); break;
				}
			}
		}	
		break;

		case Protocol::COM_GET_ART: {
			intParam1 = parse_number();
			intParam2 = parse_number();
			if(c->read() == Protocol::COM_END){
				c->write(Protocol::ANS_GET_ART);
				try {
					DataInterface::Article a = ld.get_a(intParam1, intParam2);
					c->write(Protocol::ANS_ACK);
					write_string(a.title);
					write_string(a.author);
					write_string(a.text);
				} catch(char e){
					c->write(Protocol::ANS_NAK);
					c->write(e);
				}
			}
		}	
		break;

		case Protocol::COM_END: {		
			cout << "Ans end" << endl;
		}
		default: cout << "error" << endl;
	}
	c->write(Protocol::ANS_END);

}