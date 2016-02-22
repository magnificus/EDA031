#ifndef MNS_H
#define MNS_H

#include <iostream>
#include <vector>
#include <map>
#include "nameserverinterface.h"

using namespace std;


class MNS : public NameServerInterface{
public:
//  string search(string address);

  void insert(const HostName&, const IPAddress&);
  bool remove(const HostName&);
  IPAddress lookup(const HostName&) const;

private:
  map<HostName, IPAddress> data;
};

#endif
