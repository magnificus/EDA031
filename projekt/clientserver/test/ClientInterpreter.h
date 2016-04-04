#include "GeneralInterpreter.h"

using namespace std;

class ClientInterpreter : public GeneralInterpreter{
public:
	//ClientInterpreter(Connection& conn) { super(conn); }

	void list_ng();
	void create_ng(string s);
	void delete_ng(string s);


};