#include "ipv4.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(IPv4Test, ParseFromString) {
  IPv4 ip("192.168.0.1");
  EXPECT_EQ(ip[0], 192);
  EXPECT_EQ(ip[1], 168);
  EXPECT_EQ(ip[2], 0);
  EXPECT_EQ(ip[3], 1);
}

TEST(IPv4Test, LessOperator) {
  IPv4 ip1("1.2.3.4");
  IPv4 ip2("2.2.3.4");
  EXPECT_TRUE(ip1 < ip2);
  EXPECT_FALSE(ip2 < ip1);
}

TEST(IPv4Test, GreaterOperator) {
  IPv4 ip1("10.0.0.1");
  IPv4 ip2("2.255.255.255");
  EXPECT_TRUE(ip1 > ip2);
  EXPECT_FALSE(ip2 > ip1);
}

TEST(IPv4Test, EqualityOperator) {
  IPv4 ip1("8.8.8.8");
  IPv4 ip2("8.8.8.8");
  IPv4 ip3("8.8.4.4");
  EXPECT_TRUE(ip1 == ip2);
  EXPECT_FALSE(ip1 == ip3);
}

TEST(IPv4Test, Iterators) {
  IPv4 ip("1.2.3.4");
  std::array<uint8_t, 4> expected = {1, 2, 3, 4};
  size_t i = 0;
  for (auto b : ip) {
    EXPECT_EQ(b, expected[i]);
    ++i;
  }
}

TEST(IPv4Test, OutputOperator) {
  IPv4 ip("127.0.0.1");
  std::ostringstream os;
  os << ip;
  EXPECT_EQ(os.str(), "127.0.0.1");
}

TEST(IPv4Test, PrintMethod) {
  IPv4 ip("1.2.3.4");
  std::ostringstream os;
  ip.print(os);
  EXPECT_EQ(os.str(), "1.2.3.4\n");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}