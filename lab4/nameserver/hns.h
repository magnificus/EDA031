#ifndef HNS_H
#define HNS_H

#include <iostream>
#include <vector>
#include <map>
#include "nameserverinterface.h"

using namespace std;

class HNS : public NameServerInterface{
public:
//  string search(string address);
  HNS(size_t newSize) : size(newSize), data(vector<vector<myPair>> (newSize)) {};

  void insert(const HostName&, const IPAddress&);
  bool remove(const HostName&);
  IPAddress lookup(const HostName&) const;

private:
  size_t size;
  vector<vector<myPair>> data;
};

#endif
