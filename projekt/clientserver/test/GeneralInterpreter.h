#include "protocol.h"
#include "connection.h"
#include <string>
#include <iostream>
#include <memory>

using namespace std;

class GeneralInterpreter{

public:
	GeneralInterpreter(shared_ptr<Connection> conn);

	void write_number(int num);
	void write_string(string str);

	string parse_string();
	int parse_number();

protected:
	shared_ptr<Connection> c;

};