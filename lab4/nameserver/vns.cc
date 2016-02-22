#include "vns.h"
#include <vector>
#include <algorithm>    // std::find_if

using namespace std;

using myPair = pair<HostName,IPAddress>;

IPAddress VNS::lookup(const HostName& address) const{
  auto it = find_if(data.begin(), data.end(), [&address](myPair current)-> bool{return address == current.first;});
  if(it == data.end()){
    return NON_EXISTING_ADDRESS;
  }
  return it->second;
}

void VNS::insert(const HostName& address, const IPAddress& ipaddress){
 data.push_back(myPair(address, ipaddress));
}

 bool VNS::remove(const HostName& address){
   auto it = find_if(data.begin(), data.end(), [&address](myPair current)-> bool{return address == current.first;});

   if (it != data.end()){
      data.erase(it);
      return true;
   }
   return false;
 }
