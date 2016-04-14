#include "GeneralInterpreter.h"
#include "diskdata.h"
#include "localdata.h"
#include <vector>

using namespace std;

class ServerInterpreter : GeneralInterpreter{
public:
	ServerInterpreter(shared_ptr<Connection> conn) : GeneralInterpreter(conn) {};

	void parse();
};


