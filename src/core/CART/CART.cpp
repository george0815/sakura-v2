#include "CART.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

#include "../../ui/state.h"
#include "../../ui/views/main_screen/bottom_row/submenus/log/log_component.h"

using namespace std;
using namespace UIState;      // I18nObject
using namespace LogComponent; // AddLogEntry

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
// Current members: READ_HEADER,
//
//==========================

//==========================
//  HELPER FUNCTIONS
//==========================

// Combinmes read flag and read rom helper functions, parses and loads ROM
// metadata.
int CART::READ_HEADER() {

  // Verify that tht first 4 bytes equal "NES<EOF>"
  array<uint8_t, 4> nes_confirm;
  copy(HEADER_BUFFER.begin(), HEADER_BUFFER.begin() + 4, nes_confirm.begin());
  if (CHECK_HEADER(nes_confirm) != 0) {
    AddLogEntry(I18nObject.tr("FAILED_HEADER_CHECK:_"));
  }

  // Load ROM sizes

  // Load flags

  return 0;
}

// Attempts to load rom using provided file name
int CART::READ_ROM(string file_name) {

  // Load file and check if file is over 16 bytes
  ifstream rom_file(file_name, ios::binary);
  if (!rom_file) {
    AddLogEntry(I18nObject.tr("Unable_to_read_rom."));
    return -1;
  }

  // reinterpret_cast allows any pointer to be converted into any other pointer
  // type, ifstream .read takes in char* and streamsize, so header_buffer is
  // casted to char*
  if (!rom_file.read(reinterpret_cast<char *>(HEADER_BUFFER.data()),
                     HEADER_BUFFER.size())) {
    AddLogEntry(I18nObject.tr("Unable_to_read_rom."));
    return -1;
  }

  // Read all values from header
  if (READ_HEADER() != 0) {
    AddLogEntry(I18nObject.tr("Unable_to_read_rom."));
    return -1;
  }

  // Load trainer data if available

  // Load PRG and CHR ROM

  // TODO: Implement playchoice (if im bored or have the time)

  return 0;
}

// Verifies if the ROM is valid by check the first 4 bytes of the header, the
// first 4 bytes should be equal to "NES<EOF>"
int CART::CHECK_HEADER(array<uint8_t, 4> bytes) {

  // NES<EOF>
  array<uint8_t, 4> good_header = {0x4E, 0x45, 0x53, 0x1A};

  // If the first for bytes equal the canonical NES header above
  if (good_header == bytes) {

    // Convert first 4 bytes to string
    stringstream byte_stringstream;
    for (streamsize i = 0; i < 4; ++i) {
      byte_stringstream << format("{:02x} ", bytes[i]);
    }
    string byte_string = byte_stringstream.str();

    AddLogEntry(I18nObject.tr("ROM_CONFIRMED:_") + byte_string);
    return 0;
  } else {
    return -1;
  }
}
