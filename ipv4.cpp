#include "ipv4.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

IPv4::IPv4(const std::string &s) : ipv4(parser_ipv4(s)) {}

std::array<uint8_t, 4> IPv4::parser_ipv4(const std::string &s) {
  std::array<uint8_t, 4> ip{};
  std::istringstream ss(s);
  std::string num;
  for (int i = 0; i < 4 && std::getline(ss, num, '.'); ++i) {
    ip[i] = std::stoi(num);
  }
  return ip;
}

void IPv4::print(std::ostream &out) const {
  out << static_cast<int>(ipv4[0]) << '.' << static_cast<int>(ipv4[1]) << '.'
      << static_cast<int>(ipv4[2]) << '.' << static_cast<int>(ipv4[3]) << "\n";
}

std::ostream &operator<<(std::ostream &os, const IPv4 &obj) {
  os << static_cast<int>(obj.ipv4[0]) << '.' << static_cast<int>(obj.ipv4[1])
     << '.' << static_cast<int>(obj.ipv4[2]) << '.'
     << static_cast<int>(obj.ipv4[3]);
  return os;
}

std::array<uint8_t, 4>::iterator IPv4::begin() { return ipv4.begin(); };

std::array<uint8_t, 4>::const_iterator IPv4::begin() const {
  return ipv4.begin();
};

std::array<uint8_t, 4>::iterator IPv4::end() { return ipv4.end(); };

std::array<uint8_t, 4>::const_iterator IPv4::end() const { return ipv4.end(); };

bool IPv4::operator<(const IPv4 &other) const { return ipv4 < other.ipv4; }

bool IPv4::operator>(const IPv4 &other) const { return ipv4 > other.ipv4; }

bool IPv4::operator==(const IPv4 &other) const { return ipv4 == other.ipv4; }

const uint8_t &IPv4::operator[](size_t idx) const { return ipv4[idx]; }