#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;
int size = 100000;

int main(){
    string s = "CC";
    //string whole(size, 'P');
    for (int i = 2; i < size; i++){
      s.append("P");
    }

    int currentPrime = 0;
    while (currentPrime < 1000){
      currentPrime = s.find("P", currentPrime+1);
      for (int index = currentPrime+1; index < size; index+= currentPrime){
          s.replace(index, 1, "C");
      }
    }

    cout << s;
    for(int index = 0; index < 200; index++){
      if(s[index] == 'P') cout << index << endl;
    }
    cout << "The largest prime is: " << s.find_last_of("P");
}
