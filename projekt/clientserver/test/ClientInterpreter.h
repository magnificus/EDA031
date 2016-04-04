#include "GeneralInterpreter.h"

using namespace std;

class ClientInterpreter : public GeneralInterpreter{
public:
	//ClientInterpreter(Connection& conn) { super(conn); }

	void list_ng();
	void create_ng(string s);
	void delete_ng(int n);
	void list_a(int n);
	void create_a(int n, string s1, string s2, string s3);
	void delete_a(int n1, int n2);
	void get_a(int n1, int n2);


};