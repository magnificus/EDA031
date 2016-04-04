#include "ServerInterpreter.h"
#include "localdata.h"
#include <iostream>

using namespace std;

string ServerInterpreter::parse(){
	unsigned char in = c->read();
	switch(in){
		case Protocol::COM_LIST_NG: return "list newsgroup";
		case Protocol::COM_CREATE_NG: return "create newsgroup";
		case Protocol::COM_DELETE_NG: return "delete newsgroup";
		case Protocol::COM_LIST_ART: return "list articles";
		case Protocol::COM_CREATE_ART: return "create article";
		case Protocol::COM_DELETE_ART: return "delete article";
		case Protocol::COM_GET_ART: return "get article";
		default: return "nigger";
	}
}