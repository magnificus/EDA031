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

void ClientInterpreter::delete_ng(int s){

}
void ClientInterpreter::list_a(int n){

}
void ClientInterpreter::create_a(int n, string s1, string s2, string s3){

}
	void ClientInterpreter::delete_a(int n1, int n2){

	}
	void ClientInterpreter::get_a(int n1, int n2){
		
	}

