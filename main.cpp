#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ipv4.h"

int main() {
  // std::ifstream fin("../ip_filter.tsv");
  // if (!fin) {
  //   std::cout << "File unavailable! \n";
  //   return 1;
  // }

  std::string line;
  std::vector<IPv4> ip_list;
  while (std::getline(std::cin, line)) {
    auto tab_pos = line.find('\t');
    if (tab_pos != std::string::npos) {
      std::string ip = line.substr(0, tab_pos);
      IPv4 ip_n(ip);
      ip_list.push_back(ip_n);
    }
  }
  // revers sorting
  std::sort(ip_list.begin(), ip_list.end(), std::greater<IPv4>());

  for (auto i : ip_list) {
    i.print();
  }

  // looking for address with first 1

  uint8_t req_val1 = 1;
  size_t req_index1 = 0;

  std::for_each(ip_list.begin(), ip_list.end(),
                [req_val1, req_index1](const IPv4 &ip) {
                  if (ip[req_index1] == req_val1)
                    ip.print();
                });

  // looking for address start from 46.70
  req_val1 = 46;
  req_index1 = 0;
  uint8_t req_val2 = 70;
  size_t req_index2 = 1;
  std::for_each(ip_list.begin(), ip_list.end(),
                [req_val1, req_index1, req_val2, req_index2](const IPv4 &ip) {
                  if ((ip[req_index1] == req_val1) &&
                      (ip[req_index2] == req_val2))
                    ip.print();
                });

  auto target = 46;

  std::for_each(ip_list.begin(), ip_list.end(), [target](const IPv4 &ip) {
    if (std::find(ip.begin(), ip.end(), target) != ip.end()) {
      ip.print();
      return true;
    }
    return false;
  });
  return 0;
}