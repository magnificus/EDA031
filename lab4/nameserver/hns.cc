#include "hns.h"
#include <vector>


using namespace std;

IPAddress HNS::lookup(const HostName& address) const{
  size_t pos = hash<string>()(address) % size;
  vector<myPair> curr = data[pos];
  for (size_t i = 0; i < curr.size(); i++){
    if (curr[i].first == address){
      return curr[i].second;
    }
  }
  return NON_EXISTING_ADDRESS;
}

void HNS::insert(const HostName& address, const IPAddress& ipaddress){
  size_t pos = hash<string>()(address) % size;
  data[pos].push_back(myPair(address, ipaddress));
}

 bool HNS::remove(const HostName& address){
   size_t pos = hash<string>()(address) % size;
   vector<myPair> *curr = &data[pos];
   for (size_t i = 0; i < curr->size(); i++){
     if ((*curr)[i].first == address){
       curr->erase(curr->begin() + i);
       return true;
     }
   }
   return false;
 }
