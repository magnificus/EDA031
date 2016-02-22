#ifndef VNS_H
#define VNS_H

#include <vector>
#include "nameserverinterface.h"

using namespace std;


class VNS : public NameServerInterface {
public:

  void insert(const HostName&, const IPAddress&);
  bool remove(const HostName&);
  IPAddress lookup(const HostName&) const;
private:
  vector<myPair> data;
};

#endif
