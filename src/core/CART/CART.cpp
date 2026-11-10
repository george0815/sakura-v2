#include <array>
#include <cstdint>
#include <string>

using namespace std;

//==========================
//
// This namespace represents a NES cart. Currently I'm planning to start with
// support for iNES 1.0 and Archaic iNES, since iNES 2.0 ROMs are backward
// compatible, then eventually add support for iNES 2.0 This implemtation
// includes many functions, there's about a helper function for parsing each
// byte in the header. There are also functions for parsing each section of the
// ROM (one for the header, one for PRG ROM, one for CHR ROM, etc). Finally
// there's one fucntion that puts it all together that loads all the data and
// flags into the object.
//
//
// As some flags are not commonly supported by emulators, not everything will be
// implemented at first, only the necessary fucntions.
//
// Current members: TODO: Update this
//
//==========================

class CART {

  //==========================
  //  HELPER FUNCTIONS
  //==========================

  // Attempts to load rom using provided file name
  int READ_ROM(string file_name) { return 0; }

  // Verifies if the ROM is valid by check the first 4 bytes of the header, the
  // first 4 bytes should be equal to "NES<EOF>"
  int CHECK_HEADER(array<uint8_t, 4> bytes) {

    uint32_t tmp = 0;

    tmp = (tmp | bytes[0]) << 8;
    tmp = (tmp | bytes[1]) << 8;
    tmp = (tmp | bytes[2]) << 8;
    tmp = (tmp | bytes[3]) << 8;

    if (tmp == 0x4E45531A) {
      return 0;
    }
    return -1;
  }
};
