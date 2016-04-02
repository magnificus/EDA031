#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;
// sp
string getAppSymb(const string& s){
  if (s == "&lt;") return "<";
  else if (s == "&gt;") return ">";
  else if (s == "&nbsp;") return " ";
  else if (s == "&amp;") return "&";
  else return "no match";

}

int main(){
  ifstream file("test.html");

  string str((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());
  smatch m;
  regex tags ("<[^>]*>");
  while (std::regex_search (str,m,tags)) {
  for (auto x:m){
    string::size_type i = str.find(x);
    str.erase(i, x.length());
  }
  }
  regex spec ("&[^;]*;");
  //smatch m;
  while (std::regex_search(str, m, spec)) {
    for (auto x:m){
      //cout << getAppSymb(x);
      string::size_type i = str.find(x);
      str.replace(i, x.length(), getAppSymb(x));
    }

  }
  cout << str;
  file.close();

  return 0;


}
