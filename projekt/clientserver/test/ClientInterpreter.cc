#include "ClientInterpreter.h"

using namespace std;



void ClientInterpreter::list_ng(){
	c->write(Protocol::COM_LIST_NG);
	c->write(Protocol::COM_END);
}

void ClientInterpreter::create_ng(string s){
	c->write(Protocol::COM_CREATE_NG);
	write_string(s); //PAR_STRING string s
	c->write(Protocol::COM_END);
	//COM_CREATE_NG PAR_STRING string COM_END
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
		default: cout << recieved;
	};
}
		//ANS_LIST_NG PAR_NUM size PAR_NUM n1 PAR_STR s1 PAR_NUM n2 PAR_STR s2
void ClientInterpreter::ANS_LIST_NG(){
	cout << "Listing Newsgroups: " << endl;
	int nbr = parse_number();
	cout << "There are: " << nbr << endl;
	
	for (int i = 0; i < nbr; i++){
		cout << "Id: " << parse_number() << " Name: ";
		cout << parse_string() << endl;
	}
	handleAnswer();
}

void ClientInterpreter::ANS_CREATE_NG(){
	switch(c->read()){
		case Protocol::ANS_ACK: cout << "Created newsgroup" << endl; break;
		case Protocol::ANS_NAK: cout << "Unable to create newsgroup"; if (c->read() == Protocol::ERR_NG_ALREADY_EXISTS) cout << ", group already exists." << endl; break;
	}
	handleAnswer();
}

void ClientInterpreter::ANS_DELETE_NG(){
	switch(c->read()){
		case Protocol::ANS_ACK: cout << "Deleted newsgroup" << endl; break;
		case Protocol::ANS_NAK: cout << "Unable to delete newsgroup"; if (c->read() == Protocol::ERR_NG_DOES_NOT_EXIST) cout << ", group does not exist." << endl; break;
	}
	handleAnswer();
}

void ClientInterpreter::ANS_LIST_ART(){
	cout << "Listing articles in newsgroup: " << endl;
	switch(c->read()){
		case Protocol::ANS_ACK: {
			int nbr = parse_number();
			for (int i = 0; i < nbr; i++){
				cout << "Id: " << parse_number() << " Name: ";
				cout << parse_string() << endl; 
			} break;

		}
		case Protocol::ANS_NAK: {
			cout << "Unable to list article"; if (c->read() == Protocol::ERR_NG_DOES_NOT_EXIST) cout << ", article does not exist." << endl; break;
		}
//ANS_LIST_ART ANS_ACK PAR_NUM size PAR_NUM a1 PAR_STR s1 ANS_END
	}
	handleAnswer();

}

void ClientInterpreter::ANS_CREATE_ART(){
	switch(c->read()){
		case Protocol::ANS_ACK: cout << "Created article" << endl; break;
		case Protocol::ANS_NAK: cout << "Unable to create article"; if (c->read() == Protocol::ERR_NG_DOES_NOT_EXIST) cout << ", group does not exist." << endl; break;
	}
	handleAnswer();
}

void ClientInterpreter::ANS_DELETE_ART(){
	switch(c->read()){
		case Protocol::ANS_ACK: cout << "Deleted article" << endl; break;
		case Protocol::ANS_NAK: {
			cout << "Unable to delete article";
			switch(c->read()){
				case Protocol::ERR_NG_DOES_NOT_EXIST: cout << ", group does not exist" << endl; break;
				case Protocol::ERR_ART_DOES_NOT_EXIST: cout << ", article does not exist" << endl; break;
			}
		}
	}

	handleAnswer();
}

void ClientInterpreter::ANS_GET_ART(){
	switch(c->read()){
		case Protocol::ANS_ACK: {
			cout << "Title: " << parse_string() << endl;
			cout << "Author: " << parse_string() << endl;
			cout << "Text: " << parse_string() << endl;
		} break;
		case Protocol::ANS_NAK: {
			cout << "Unable to read article";
			switch(c->read()){
				case Protocol::ERR_NG_DOES_NOT_EXIST: cout << ", group does not exist" << endl;
				case Protocol::ERR_ART_DOES_NOT_EXIST: cout << ", article does not exist" << endl;;
			} break;
		}
	}
	handleAnswer();
}