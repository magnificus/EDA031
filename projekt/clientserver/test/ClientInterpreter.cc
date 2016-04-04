#include "ClientInterpreter.h"

using namespace std;
using namespace protocol;

void ClientInterpreter::list_ng(){
	c.write(COM_LIST_NG);
	c.write(COM_END);
}

void ClientInterpreter::create_ng(){
	c.write()
}

