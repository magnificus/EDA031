#include "mns.h"
#include <vector>


using namespace std;

IPAddress MNS::lookup(const HostName& address) const{
  auto got = data.find(address);
  if(got == data.end()){
    return NON_EXISTING_ADDRESS;
  }
  return got->second;

}

void MNS::insert(const HostName& address, const IPAddress& ipaddress){
  data.emplace(address, ipaddress);
}

 bool MNS::remove(const HostName& address){
   auto pos = data.find(address);
   if (pos != data.end()){
     data.erase(pos);
     return true;
   }
   return false;
 }
