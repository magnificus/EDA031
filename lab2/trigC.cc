#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
using namespace std;


int main(){
  ofstream mySaveFile;
  ifstream file("/usr/share/dict/words");
  //ifstream file("simplewords");
  mySaveFile.open("words.txt");

  string str = "";
  string formatted;
  vector<string> words;
  while (std::getline(file, str))
    {
      words = {};
      formatted = str;
      if (str.length() < 4){
          formatted.append(" " + to_string(0));

      } else{
        formatted.append(" " + to_string(str.length()-2));
        for (size_t i = 3; i <= str.length(); i++){
          words.push_back(str.substr(i-3,3));
        }
        sort(words.begin(), words.end());
        for(size_t i = 0; i < words.size(); i++){
          formatted.append(" ");
          formatted.append(words[i]);
        }
      }
      transform(formatted.begin(), formatted.end(), formatted.begin(), ::tolower);
      formatted.append("\n");
      mySaveFile << formatted;
    }
    file.close();
    mySaveFile.close();

    return 0;
}
