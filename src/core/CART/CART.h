#include <array>
#include <cstdint>
#include <cstdio>

using namespace std;

class CART {

public:
  // Gets the header of a NES rom
  static bool GetHeader(array<uint8_t, 4> bytes);
};
