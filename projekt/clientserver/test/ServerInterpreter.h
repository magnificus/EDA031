#include "GeneralInterpreter.h"

using namespace std;

class ServerInterpreter : GeneralInterpreter{
public:
	ServerInterpreter(Connection *conn) : GeneralInterpreter(conn) {};

	void parse(unsigned char in);

};