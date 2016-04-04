#include "ServerInterpreter.h"
#include <iostream>

using namespace std;

void ServerInterpreter::parse(unsigned char in){
	switch(in){
		case Protocol::COM_LIST_NG: cout << "list newsgroup"; break;
		case Protocol::COM_CREATE_NG: cout << "create newsgroup"; break;
		case Protocol::COM_DELETE_NG: cout << "delete newsgroup"; break;
		case Protocol::COM_LIST_ART: cout << "list articles"; break;
		case Protocol::COM_CREATE_ART: cout << "create article"; break;
		case Protocol::COM_DELETE_ART: cout << "delete article"; break;
		case Protocol::COM_GET_ART: cout << "get article"; break;
		default: cout << "nigger";
	}
}