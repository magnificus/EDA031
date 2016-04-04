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

void ClientInterpreter::handleAnswer(){
	unsigned char recieved = c->read();
	switch(recieved){
		case Protocol::ANS_LIST_NG: cout << "recieved ANS_LIST_NG" << endl; ANS_LIST_NG(); break;
		case Protocol::ANS_CREATE_NG: cout << "recieved ANS_CREATE_NG" << endl; ANS_CREATE_NG(); break;
		case Protocol::ANS_DELETE_NG: cout << "recieved ANS_DELETE_NG" << endl; ANS_DELETE_NG(); break;
		case Protocol::ANS_LIST_ART: cout << "recieved ANS_LIST_ART" << endl; ANS_LIST_ART(); break;
		case Protocol::ANS_CREATE_ART: cout << "recieved ANS_CREATE_ART" << endl; ANS_CREATE_ART(); break;
		case Protocol::ANS_DELETE_ART: cout << "recieved ANS_DELETE_ART" << endl; ANS_DELETE_ART(); break;
		case Protocol::ANS_GET_ART: cout << "recieved ANS_GET_ART" << endl; ANS_GET_ART(); break;
		case Protocol::ANS_END: cout << "recieved ANS_END" << endl; break;
		case Protocol::ANS_ACK: cout << "recieved ANS_ACK" << endl; break;
		case Protocol::ANS_NAK: cout << "recieved ANS_NAK" << endl; break;
		default: cout << "could not interpret";
	};
}

void ClientInterpreter::ANS_LIST_NG(){
	cout << "Listing Newsgroups: " << endl;
	if (c->read() != Protocol::PAR_NUM){
		return;
	}
	unsigned char nbr = c->read();
	cout << "There are: " << nbr;
	
	for (unsigned char i = 0; i < nbr; i++){
		cout << "Id: " << parse_number() << " Name: " << parse_string() << endl;
	}

	c->read();

}

void ClientInterpreter::ANS_CREATE_NG(){
	unsigned char recieved = c->read();
	switch(recieved){
		case Protocol::ANS_ACK: cout << "Created newsgroup" << endl; break;
		case Protocol::ANS_NAK: cout << "Unable to create newsgroup, blame lukas tbh" << endl; c->read(); break;
	}

	c->read();

}

void ClientInterpreter::ANS_DELETE_NG(){
	unsigned char recieved = c->read();
	switch(recieved){
		case Protocol::ANS_ACK: cout << "Deleted newsgroup" << endl; break;
		case Protocol::ANS_NAK: cout << "Unable to delete newsgroup, blame lukas tbh" << endl; c->read(); break;
	}

	c->read();
}

void ClientInterpreter::ANS_LIST_ART(){
	cout << "Listing articles in newsgroup: " << endl;
	unsigned char recieved = c->read();
	switch(recieved){
		case Protocol::ANS_ACK: {
			unsigned char nbr = c->read();
			for (unsigned char i = 0; i < nbr; i++){
				cout << "Id: " << parse_number() << " Name: " << parse_string() << endl; 
			} break;

		}
	}

	c->read();

}

void ClientInterpreter::ANS_CREATE_ART(){

}

void ClientInterpreter::ANS_DELETE_ART(){

}

void ClientInterpreter::ANS_GET_ART(){

}