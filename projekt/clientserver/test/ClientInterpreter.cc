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

void ClientInterpreter::delete_ng(int n){
	c->write(Protocol::COM_DELETE_NG);
	write_number(n);
	c->write(Protocol::COM_END);

}
void ClientInterpreter::list_a(int n){
	c->write(Protocol::COM_LIST_ART);
	write_number(n);
	c->write(Protocol::COM_END);

}
void ClientInterpreter::create_a(int n, string s1, string s2, string s3){
	c->write(Protocol::COM_CREATE_ART);
	write_number(n);
	write_string(s1);
	write_string(s2);
	write_string(s3);
	c->write(Protocol::COM_END);

}
void ClientInterpreter::delete_a(int n1, int n2){
	c->write(Protocol::COM_DELETE_ART);
	write_number(n1);
	write_number(n2);
	c->write(Protocol::COM_END);

}
void ClientInterpreter::get_a(int n1, int n2){
	c->write(Protocol::COM_GET_ART);
	write_number(n1);
	write_number(n2);
	c->write(Protocol::COM_END);

}

