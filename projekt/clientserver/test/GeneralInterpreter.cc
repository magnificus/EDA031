#include "GeneralInterpreter.h"
using namespace std;


GeneralInterpreter::GeneralInterpreter(shared_ptr<Connection> conn) {c = conn;}

void GeneralInterpreter::write_string(string s){
	c->write(Protocol::PAR_STRING);
	c->write(s.length());
	for (char ch : s) {
		c->write(ch);
	}
}

void GeneralInterpreter::write_number(int n){
	c->write(Protocol::PAR_NUM);
	c->write((n >> 24) & 0xFF);
	c->write((n >> 16) & 0xFF);
	c->write((n >> 8) & 0xFF);
	c->write(n & 0xFF);
}


int GeneralInterpreter::parse_number() {
	if(c->read() == Protocol::PAR_NUM){
		unsigned char byte1 = c->read();
		unsigned char byte2 = c->read();
		unsigned char byte3 = c->read();
		unsigned char byte4 = c->read();
		return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
	}
}

string GeneralInterpreter::parse_string() {
	if(c->read() == Protocol::PAR_STRING){	
		string s;
		//char ch;
		size_t length = c->read();
		for (size_t i = 0; i < length; i++) {
			s += c->read();
		}
		return s;
	} else {
		cout << "failed PAR_STRING" << endl;
	}
}