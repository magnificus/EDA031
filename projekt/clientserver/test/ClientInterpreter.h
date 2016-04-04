#include "protocol.h"
#include "connection.h"

using namespace std;
class ClientInterpreter{
public:
	ClientInterpreter(Connection &conn) c(conn) {} ;

	void list_ng();
	void create_ng();
	void delete_ng();


private:
	Connection c;
}