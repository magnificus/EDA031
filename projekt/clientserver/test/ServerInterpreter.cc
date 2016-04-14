#include "ServerInterpreter.h"
#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

void ServerInterpreter::parse(){
	LocalData ld;
	string result, parameter1, parameter2, parameter3, parameter4;
	int intParam1, intParam2;
	unsigned char in = c->read();
	switch(in){
		case Protocol::COM_LIST_NG: {
			c->write(Protocol::ANS_LIST_NG);
			vector<Newsgroup> list = ld.list_ng();
			write_number(list.size());
			for(Newsgroup n : list){
				write_number(n.newsGroupsNbr);
				write_string(n.title);
			}
			parse();
		}
		break;


		case Protocol::COM_CREATE_NG: {
			c->write(Protocol::ANS_CREATE_NG);
			parameter1 = parse_string();
			cout << parameter1 << endl;
			if(ld.create_ng(parameter1)){
				c->write(Protocol::ANS_ACK);
			} else {
				c->write(Protocol::ANS_NAK);
				c->write(Protocol::ERR_NG_ALREADY_EXISTS);
			}
			parse();
		}
		break;

		case Protocol::COM_DELETE_NG: {
			c->write(Protocol::ANS_DELETE_NG);
			intParam1 = parse_number();
			if(ld.delete_ng(intParam1)){
				c->write(Protocol::ANS_ACK);
			} else {
				c->write(Protocol::ANS_NAK);
				c->write(Protocol::ERR_NG_DOES_NOT_EXIST);
			}
			parse();
		}	
		break;

		case Protocol::COM_LIST_ART: {
			c->write(Protocol::ANS_LIST_ART);
			intParam1 = parse_number();
			Newsgroup ng = ld.list_a(intParam1);
			try {
				write_number(ng.articles.size());
				for(Article a : ng.articles){
					write_number(a.articleNbr);
					write_string(a.title);
				}
			} catch (char e){
				c->write(Protocol::ANS_NAK);
				c->write(e);
			}
			parse();
		}	
		break;

		case Protocol::COM_CREATE_ART: {
			c->write(Protocol::ANS_CREATE_ART);
			intParam1 = parse_number();
			parameter2 = parse_string();
			parameter3 = parse_string();
			parameter4 = parse_string();
			if(ld.create_a(intParam1, parameter2, parameter3, parameter4)){
				c->write(Protocol::ANS_ACK);
			} else {
				c->write(Protocol::ANS_NAK);
				c->write(Protocol::ERR_NG_DOES_NOT_EXIST);
			}
			parse();
		}	
		break;

		case Protocol::COM_DELETE_ART: {
			c->write(Protocol::ANS_DELETE_ART);
			intParam1 = parse_number();
			intParam2 = parse_number();
			switch(ld.delete_a(intParam1, intParam2)){
				case 0: c->write(Protocol::ANS_ACK); break;
				case -1: c->write(Protocol::ANS_NAK); c->write(Protocol::ERR_ART_DOES_NOT_EXIST); break;
				case -2: c->write(Protocol::ANS_NAK); c->write(Protocol::ERR_NG_DOES_NOT_EXIST); break;
			}
			parse();
		}	
		break;

		case Protocol::COM_GET_ART: {
			c->write(Protocol::ANS_GET_ART);
			intParam1 = parse_number();
			intParam2 = parse_number();
			try {
				Article a = ld.get_a(intParam1, intParam2);
				write_string(a.title);
				write_string(a.author);
				write_string(a.text);
			} catch(char e){
				c->write(Protocol::ANS_NAK);
				c->write(e);
			}
			parse();
		}	
		break;

		case Protocol::COM_END: {			
			c->write(Protocol::ANS_END);
		}
		default: cout << "penis";
	}

}