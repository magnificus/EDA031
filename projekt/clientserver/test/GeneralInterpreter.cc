#include "GeneralInterpreter.h"
using namespace std;


GeneralInterpreter::GeneralInterpreter(shared_ptr<Connection> conn) {c = conn;}

void GeneralInterpreter::write_string(string s){
	c->write(Protocol::PAR_STRING);
	for (char ch : s) {
		c->write(ch);
	}
	c->write('$');
}

void GeneralInterpreter::write_number(int n){
	c->write(Protocol::PAR_NUM);
	c->write((n >> 24) & 0xFF);
	c->write((n >> 16) & 0xFF);
	c->write((n >> 8)	 & 0xFF);
	c->write(n & 0xFF);
}


int GeneralInterpreter::parse_number() {
	unsigned char byte1 = c->read();
	unsigned char byte2 = c->read();
	unsigned char byte3 = c->read();
	unsigned char byte4 = c->read();
	return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

string GeneralInterpreter::parse_string() {
	string s;
	char ch;
	while ((ch = c->read()) != '$') {
		s += ch;
	}
	return s;
}