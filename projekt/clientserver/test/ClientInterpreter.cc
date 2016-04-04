#include "ClientInterpreter.h"

using namespace std;

void ClientInterpreter::list_ng(){
	c->write(Protocol::COM_LIST_NG);
	c->write(Protocol::COM_END);
}

void ClientInterpreter::create_ng(string s){
	c->write(Protocol::COM_CREATE_NG);
	write_string(s);
	c->write(Protocol::COM_END);
}

void ClientInterpreter::delete_ng(string s){
	
}

int main(){

}

