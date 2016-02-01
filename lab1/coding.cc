#include <iostream>
#include <fstream>
#include "coding.h"
#include <cstdlib>
using namespace std;



const char encode(char c){
  return c + 1;
}

const char decode (char c){
  return c - 1;
}

string encode_str(string s, bool to){
  string newString = "";
  for (int i = 0; i < s.length(); i++){
    if (to){
      newString += encode(s[i]);
    } else {
      newString += decode(s[i]);
    }
  }
  return newString;
}

int main (int argc, char* argv[]){
  bool encode = atoi(argv[2]) == 1;


  ifstream myReadFile;
  ofstream mySaveFile;
  if (encode){
    mySaveFile.open("file.enc");
    myReadFile.open(argv[1]);
  } else{
    mySaveFile.open(argv[1]);
    myReadFile.open("file.enc");
  }

  string output;
  std::getline( myReadFile, output );
    while (myReadFile) {
      myReadFile >> output;
      cout << output;
      mySaveFile<<encode_str(output, encode);
      std::getline( myReadFile, output );
    }


  //toFile(encode_str(output, true));
  myReadFile.close();
  mySaveFile.close();
//  cout << "el segredo messago" << endl;
//  cout << encode_str("el segredo messago", true) << endl;
//  cout << encode_str(encode_str("el segredo messago", true), false)  << endl;
  return 0;
}
