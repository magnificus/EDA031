#include "umns.h"
#include <vector>


using namespace std;

IPAddress UMNS::lookup(const HostName& address) const{
  std::unordered_map<HostName,IPAddress>::const_iterator got = data.find(address);
  if(got == data.end()){
    return NON_EXISTING_ADDRESS;
  }
  return got->second;

}

void UMNS::insert(const HostName& address, const IPAddress& ipaddress){
  data.emplace(address, ipaddress);
}

 bool UMNS::remove(const HostName& address){
   auto pos = data.find(address);
   if (pos != data.end()){
     data.erase(pos);
     return true;
   }
   return false;
 }
