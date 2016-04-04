/* myclient.cc: sample client program */
#include "ClientInterpreter.h"

#include "connection.h"
#include "connectionclosedexception.h"
#include "protocol.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <algorithm>
#include <sstream>

using namespace std;


inline bool isInteger(const string& s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}
/*
 * Send an integer to the server as four bytes.
 */
void writeNumber(const Connection& conn, int value) {
	conn.write((value >> 24) & 0xFF);
	conn.write((value >> 16) & 0xFF);
	conn.write((value >> 8)	 & 0xFF);
	conn.write(value & 0xFF);
}

/*
 * Read a string from the server.
 */
string readString(const Connection& conn) {
	string s;
	char ch;
	while ((ch = conn.read()) != '$') {
		s += ch;
	}
	return s;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: myclient host-name port-number" << endl;
		exit(1);
	}
	
	int port = -1;
	try {
		port = stoi(argv[2]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
	
	Connection *conn = new Connection(argv[1], port);
	if (!conn->isConnected()) {
		cerr << "Connection attempt failed" << endl;
		exit(1);
	}
	ClientInterpreter CI(conn);
	string input;
	while (getline(cin, input)) {
		try {
			string command;
			istringstream ss(input);
			ss >> command;
			transform(command.begin(), command.end(), command.begin(), ::tolower);
			if(command == "list"){
				int nbr;
				ss >> nbr;
				if(nbr){
					CI.list_a(nbr);
				} else {
					CI.list_ng();
				}
			} else if(command == "create"){
				string parameter;
				ss >> parameter;
				if(isInteger(parameter)){
					string title, author, text;
					ss >> title >> author >> text;
					int p = stoi(parameter);
					CI.create_a(p, title, author, text);
				} else {
					CI.create_ng(parameter);
				}
			} else if(command == "delete"){
				int groupNbr, articleNbr;
				ss >> groupNbr >> articleNbr;
				if(articleNbr){
					CI.delete_a(groupNbr, articleNbr);
				} else {
					CI.delete_ng(groupNbr);
				}
			} else if(command == "read"){
				int groupNbr, articleNbr;
				ss >> groupNbr >> articleNbr;
				CI.get_a(groupNbr, articleNbr);
			} else {
				cout << "No such command";
			}

		} catch (ConnectionClosedException&) {
			cout << " no reply from server. Exiting." << endl;
			exit(1);
		}
	}
}



