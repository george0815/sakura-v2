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
    return -1;
  }

  // Get size of CHR ROM, PRG ROM, and determine whether CHR RAM is used
  if (READ_ROM_SIZE_INES_1() != 0) {
    AddLogEntry(I18nObject.tr("FAILED_READING_ROM_SIZE:_"));
    return -1;
  }

  // Load flags
  if (READ_FLAGS_INES_1() != 0) {
    AddLogEntry(I18nObject.tr("FAILED_READING_FLAGS:_"));
    return -1;
  }

  return 0;
}

// Read flag bytes and set values
int CART::READ_FLAGS_INES_1() {

  // Set flag bytes
  uint8_t flags_6 = HEADER_BUFFER[6];
  uint8_t flags_7 = HEADER_BUFFER[7];
  uint8_t flags_8 = HEADER_BUFFER[8];
  uint8_t flags_9 = HEADER_BUFFER[9];
  uint8_t flags_10 = HEADER_BUFFER[10];

  // FLAGS 6

  // Parse nametable arrangement, horizontal arrangement means vertical
  // mirroring and vice-versa
  NAMETABLE_MIRRORING = (flags_6 & 0x1);
  if (NAMETABLE_MIRRORING == NAMETABLE_MIRRORING::HORIZONTAL) {
    AddLogEntry(I18nObject.tr("NAMETABLE MIRRORING: HORIZONTAL"));
  } else if (NAMETABLE_MIRRORING == NAMETABLE_MIRRORING::VERTICAL) {
    AddLogEntry(I18nObject.tr("NAMETABLE MIRRORING: VERTICAL"));
  }

  // Determine if persistent saving is used (ex. battery-backed SRAM) (if 2nd
  // bit is set)
  SRAM_PRESENT = (flags_6 & 0x2);

  // Determine if trainer is present (if 3rd bit is set)
  TRAINER_PRESENT = (flags_6 & 0x4);

  // Determine if an alternative nametable layout is used (if 4th bit is set)
  ALTERNATE_NAMETABLE_LAYOUT = (flags_6 & 0x8);

  // Get lower 4 bits of mapper number (mask last for bits then left shift 4)
  MAPPER_NUMBER_LOWER_4_BITS = (flags_6 & 0xF0) >> 4;

  // Parse flags 8 byte

  // Parse flags 9 byte

  // Parse flags 10 byte

  return 0;
}

// Load ROM sizes from bytes 4 and 5
int CART::READ_ROM_SIZE_INES_1() {

  // Get PRG ROM size value (byte 4) and multiply it by 16kb (0x4000)
  PRG_ROM_SIZE = HEADER_BUFFER[4] * 0x4000;

  // Get CHR ROM size value (byte 5) and multiply it by 8kb (0x2000)
  // If value of byte 5 is 0, then the rom uses CHR RAM instead
  if (HEADER_BUFFER[5] != 0) {
    CHR_ROM_SIZE = HEADER_BUFFER[5] * 0x2000;
  } else {
    CHR_ROM_SIZE = HEADER_BUFFER[5];
    USES_CHR_RAM = true;
  }

  // Actual value are stored as amount of bytes, but for readability divide by
  // 1KB (0x400)
  AddLogEntry("PRG ROM: " + to_string(PRG_ROM_SIZE / 0x400) + "KB");
  AddLogEntry("CHR ROM: " + to_string(CHR_ROM_SIZE / 0x400) + "KB");

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

  // reinterpret_cast allows any pointer to be converted into any other
  // pointer type, ifstream .read takes in char* and streamsize, so
  // header_buffer is casted to char*
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
