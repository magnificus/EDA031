#include "GeneralInterpreter.h"

using namespace std;

class ClientInterpreter : GeneralInterpreter{
public:
	ClientInterpreter(shared_ptr<Connection> conn) : GeneralInterpreter(conn) {};

	void list_ng();
	void create_ng(string s);
	void delete_ng(int n);
	void list_a(int n);
	void create_a(int n, string s1, string s2, string s3);
	void delete_a(int n1, int n2);
	void get_a(int n1, int n2);
	

	void handleAnswer();

	void ANS_LIST_NG();
	void ANS_CREATE_NG();
	void ANS_DELETE_NG();
	void ANS_LIST_ART();
	void ANS_CREATE_ART();
	void ANS_DELETE_ART();
	void ANS_GET_ART();


};