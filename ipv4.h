#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#pragma once

class IPv4 {
public:
  explicit IPv4(const std::string &s);

  static std::array<uint8_t, 4> parser_ipv4(const std::string &s);

  friend std::ostream &operator<<(std::ostream &os, const IPv4 &obj);

  void print(std::ostream &out = std::cout) const;

  std::array<uint8_t, 4>::iterator begin();

  std::array<uint8_t, 4>::const_iterator begin() const;

  std::array<uint8_t, 4>::iterator end();

  std::array<uint8_t, 4>::const_iterator end() const;

  bool operator<(const IPv4 &other) const;

  bool operator>(const IPv4 &other) const;

  bool operator==(const IPv4 &other) const;

  const uint8_t &operator[](size_t idx) const;

private:
  std::array<uint8_t, 4> ipv4;
};
