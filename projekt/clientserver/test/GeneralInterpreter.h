#include "protocol.h"
#include "connection.h"
#include <string>
#include <iostream>

using namespace std;

class GeneralInterpreter{

public:
	GeneralInterpreter(Connection *conn);

	void write_number(int num);
	void write_string(string str);

	string parse_string(unsigned char num);
	int parse_number();

protected:
	Connection* c;

};