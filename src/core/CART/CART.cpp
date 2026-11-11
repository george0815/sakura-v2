#include "CART.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

#include "../../ui/views/main_screen/bottom_row/submenus/log/log_component.h"

using namespace std;
using namespace LogComponent;

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

//==========================
//  HELPER FUNCTIONS
//==========================

// Combinmes read flag and read rom helper functions, parses and loads ROM
// metadata.
int CART::READ_HEADER(array<uint8_t, 16> bytes) {

  stringstream test;

  for (streamsize i = 0; i < 16; ++i) {
    test << format("{:02x} ", bytes[i]);
  }

  string test_result = test.str();

  AddLogEntry("CHECK :" + test_result);

  // Verify that tht first 4 bytes equal "NES<EOF>"
  array<uint8_t, 4> nes_confirm;
  copy(bytes.begin(), bytes.begin() + 4, nes_confirm.begin());
  CHECK_HEADER(nes_confirm);

  // Load ROM sizes

  // Load flags

  return 0;
}

// Attempts to load rom using provided file name
int CART::READ_ROM(string file_name) {

  // Load file and check if file is over 16 bytes
  ifstream rom_file(file_name, ios::binary);
  if (!rom_file) {
    // TODO: error handling
  }
  AddLogEntry("ROM OPENED");

  // Load header_buffer and parse header
  array<uint8_t, 16> header_buffer;
  // array<uint8_t, 16> test_buffer;
  /*
    rom_file.read(reinterpret_cast<char *>(test_buffer.data()),
                  test_buffer.size());
    streamsize buffer_size = rom_file.gcount();

    stringstream test;

    for (streamsize i = 0; i < buffer_size; ++i) {
      test << format("{:02x} ", test_buffer[i]);
    }

    string test_result = test.str();

    AddLogEntry(test_result);

    rom_file.close(); */

  // reinterpret_cast allows any pointer to be converted into any other pointer
  // type, ifstream read takes in char* and streamsize, so header_buffer is
  // casted to char*
  rom_file.read(reinterpret_cast<char *>(header_buffer.data()),
                header_buffer.size());

  streamsize buffer_size2 = rom_file.gcount();
  AddLogEntry("HEADER LOADED");

  stringstream test2;
  for (streamsize i = 0; i < buffer_size2; ++i) {
    test2 << format("{:02x} ", header_buffer[i]);
  }

  string test_result = test2.str();

  AddLogEntry("TEST" + test_result);

  READ_HEADER(header_buffer);

  // Load trainer data if available

  // Load PRG and CHR ROM

  // TODO: Implement playchoice (if im bored or have the time)

  return 0;
}

// Verifies if the ROM is valid by check the first 4 bytes of the header, the
// first 4 bytes should be equal to "NES<EOF>"
int CART::CHECK_HEADER(array<uint8_t, 4> bytes) {

  stringstream test;

  array<uint8_t, 4> good_header = {0x4E, 0x45, 0x53, 0x1A};

  if (good_header == bytes) {
    AddLogEntry("NES");
  }

  for (streamsize i = 0; i < 4; ++i) {
    test << format("{:02x} ", bytes[i]);
  }

  string test_result = test.str();

  uint32_t tmp = 0;

  tmp = (tmp | bytes[0]) << 8;
  tmp = (tmp | bytes[1]) << 8;
  tmp = (tmp | bytes[2]) << 8;
  tmp = (tmp | bytes[3]) << 8;

  stringstream tmp_string;

  tmp_string << hex << tmp;

  string res(tmp_string.str());

  AddLogEntry(test_result);

  AddLogEntry(to_string(tmp));
  if (test_result == to_string(0x4E45531A)) {
    AddLogEntry(to_string(tmp));
    return 0;
  }
  return -1;
}
