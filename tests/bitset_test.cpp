#include "catch.hpp"
#include "../src/bitset.h"

TEST_CASE("getBit") {
  uint8_t arr[] = { 0x02, 0x80 };
  REQUIRE(getBit(arr, 0, 0) == false);
  REQUIRE(getBit(arr, 0, 1) == true);
  REQUIRE(getBit(arr, 1, 7) == true);
}

TEST_CASE("getU8") {
  uint8_t arr[] = { 0xf4, 0xba };
  REQUIRE(getU8(arr, 0) == 0xf4);
  REQUIRE(getU8(arr, 0, 4, 0) == 0x04);
  REQUIRE(getU8(arr, 0, 4, 4) == 0x0f);
  REQUIRE(getU8(arr, 1) == 0xba);
}

TEST_CASE("getU16") {
  uint8_t arr[] = { 0x07, 0xdf, 0x03 };
  REQUIRE(getU16(arr, 0) == 0x07df);
  REQUIRE(getU16(arr, 1) == 0xdf03);
}

TEST_CASE("getU32") {
  uint8_t arr[] = { 0x01, 0x02, 0x03, 0x04 };
  REQUIRE(getU32(arr, 0) == 0x01020304);
}

TEST_CASE("getS8") {
  uint8_t arr[] = { 0x10, 0xff };
  REQUIRE(getS8(arr, 0) == 0x10);
  REQUIRE(getS8(arr, 1) == -1);
}

TEST_CASE("getS16") {
  uint8_t arr[] = { 0x10, 0xff, 0xfe };
  REQUIRE(getS16(arr, 0) == 0x10ff);
  REQUIRE(getS16(arr, 1) == -2);
}

TEST_CASE("getS32") {
  uint8_t arr[] = { 0x10, 0xff, 0xff, 0xff, 0xfe };
  REQUIRE(getS32(arr, 0) == 0x10ffffff);
  REQUIRE(getS32(arr, 1) == -2);
}

TEST_CASE("getFloat") {
  uint8_t arr[] = { 0x42, 0xc8, 0x00, 0x00 };
  REQUIRE(getFloat(arr, 0) == Approx(100.0));
}

TEST_CASE("setBit") {
  uint8_t arr[] = { 0, 0xff };
  setBit(arr, true, 0, 7);
  REQUIRE(arr[0] == 0x80);
  setBit(arr, false, 1, 7);
  REQUIRE(arr[1] == 0x7f);
}

TEST_CASE("setU8") {
  uint8_t arr[] = { 0, 0xff };
  setU8(arr, 0x10, 0);
  REQUIRE(arr[0] == 0x10);
  setU8(arr, 0x4, 1, 4, 0);
  REQUIRE(arr[1] == 0xf4);
  setU8(arr, 0xb, 1, 4, 4);
  REQUIRE(arr[1] == 0xb4);
}

TEST_CASE("setU16") {
  uint8_t arr[] = { 0, 0 };
  setU16(arr, 0xdead, 0);
  REQUIRE(arr[0] == 0xde);
  REQUIRE(arr[1] == 0xad);
}

TEST_CASE("setU32") {
  uint8_t arr[] = { 0, 0, 0, 0 };
  setU32(arr, 0xdeadbeef, 0);
  REQUIRE(arr[0] == 0xde);
  REQUIRE(arr[1] == 0xad);
  REQUIRE(arr[2] == 0xbe);
  REQUIRE(arr[3] == 0xef);
}

TEST_CASE("setFloat") {
  uint8_t arr[] = { 0, 0, 0, 0 };
  setFloat(arr, 42, 0);
  REQUIRE(arr[0] == 0x42);
  REQUIRE(arr[1] == 0x28);
  REQUIRE(arr[2] == 0x00);
  REQUIRE(arr[3] == 0x00);
}

TEST_CASE("setBit getBit") {
  uint8_t arr[] = { 0, 0 };
  setBit(arr, true, 0, 6);
  REQUIRE(getBit(arr, 0, 6) == true);
}

TEST_CASE("setU8 getU8") {
  uint8_t arr[] = { 0, 0 };
  setU8(arr, 0xf, 1, 4);
  REQUIRE(getU8(arr, 1, 4) == 0xf);
}

TEST_CASE("setU16 getU16") {
  uint8_t arr[] = { 0xbe, 0xef };
  setU16(arr, 0xdead, 0);
  REQUIRE(getU16(arr, 0) == 0xdead);
}

TEST_CASE("setU32 getU32") {
  uint8_t arr[] = { 0xc0, 0xff, 0xee, 0 };
  setU32(arr, 0xdeadbeef, 0);
  REQUIRE(getU32(arr, 0) == 0xdeadbeef);
}

TEST_CASE("setFloat getFloat") {
  uint8_t arr[] = { 0, 0, 0, 0 };
  const float pi = 3.14159265359;
  setFloat(arr, pi, 0);
  REQUIRE(getFloat(arr, 0) == Approx(pi));
}
