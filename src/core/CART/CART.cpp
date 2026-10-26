#include <array>
#include <cstdint>

using namespace std;

class CART {

  bool GetHeader(array<uint8_t, 4> bytes) {

    uint32_t tmp = 0;

    tmp = (tmp | bytes[0]) << 8;
    tmp = (tmp | bytes[1]) << 8;
    tmp = (tmp | bytes[2]) << 8;
    tmp = (tmp | bytes[3]) << 8;

    return (tmp == 0x4E45531A);
  }
};
