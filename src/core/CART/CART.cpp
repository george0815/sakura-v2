#include "CART.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>

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
// NOTE: In this project when I say "5th bit" or "2nd bit", I am NOT starting
// from index 0. For example, with 0000 0100 I would say the "3rd" bit is set
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

  // iNES 1.0
  if (CART_VERSION == CART_VERSION::INES_1) {

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
  // iNES 2.0
  else if (CART_VERSION == CART_VERSION::INES_2) {

    // Get size of CHR ROM, PRG ROM, and determine whether CHR RAM is used
    if (READ_ROM_SIZE_NES_2() != 0) {
      AddLogEntry(I18nObject.tr("FAILED_READING_ROM_SIZE:_"));
      return -1;
    }

    // Load flags
    if (READ_FLAGS_NES_2() != 0) {
      AddLogEntry(I18nObject.tr("FAILED_READING_FLAGS:_"));
      return -1;
    }

    return 0;
  }

  return 0;
}

// iNES 2.0
int CART::READ_FLAGS_NES_2() { return 0; }

// Read flag bytes and set values for iNES 1.0
int CART::READ_FLAGS_INES_1() {

  // FLAGS 6

  // Parse nametable arrangement, horizontal arrangement means vertical
  // mirroring and vice-versa
  NAMETABLE_MIRRORING = (FLAGS_6 & 0x1);
  if (NAMETABLE_MIRRORING == NAMETABLE_MIRRORING::HORIZONTAL) {
    AddLogEntry(I18nObject.tr("NAMETABLE MIRRORING: HORIZONTAL"));
  } else if (NAMETABLE_MIRRORING == NAMETABLE_MIRRORING::VERTICAL) {
    AddLogEntry(I18nObject.tr("NAMETABLE MIRRORING: VERTICAL"));
  }

  // Determine if persistent saving is used (ex. battery-backed SRAM) (if 2nd
  // bit is set)
  SRAM_PRESENT = (FLAGS_6 & 0x2);

  // Determine if trainer is present (if 3rd bit is set)
  TRAINER_PRESENT = (FLAGS_6 & 0x4);

  // Determine if an alternative nametable layout is used (if 4th bit is set)
  ALTERNATE_NAMETABLE_LAYOUT = (FLAGS_6 & 0x8);

  // Get lower 4 bits of mapper number (mask last for bits then left shift 4)
  uint8_t mapper_lower_4_bits = (FLAGS_6 & 0xF0) >> 4;

  // FLAGS 7

  if (CART_VERSION !=
      CART_VERSION::ARCH_NES) { // bytes 7-15 are unused in archaic iNES

    // Does the rom use the VS unisystem (I dont even know what the hell that
    // is, right now I'm basing my implemtation off iNES format page on nesdev
    // wiki and saw vs system. Maybe I'll implement it down the line if I'm
    // bored and I want to make this emulator more accurate)
    VS_UNISYSTEM = ((FLAGS_7 & 0x01) == 0x01);

    // Same as above, apparently PC10 was some arcade thing I guess?
    PLAYCHOICE = ((FLAGS_7 & 0x02) == 0x02);

    // Get upper 4 bits of mapper number (mask last for bits then left shift 4)
    uint8_t mapper_upper_4_bits = (FLAGS_7 & 0xF0) >> 4;

    // Get final mapper number
    MAPPER_NUMBER = (mapper_upper_4_bits << 4) | mapper_lower_4_bits;

    // FLAGS 8 - flags 8 byte just contains the PRG RAM size, although in
    // iNES 1.0 this is not considered reliable. I'm setting it this way for now
    // and will change is once iNES 2.0 is supported

    if (FLAGS_8 == 0) { // for compatibility purposes, a value of 0 infers 8KB
      PRG_RAM_SIZE = 0x2000;
    } else { // like CHR ROM size, it is in 8KB units, so multiply by 0x2000
      PRG_RAM_SIZE = FLAGS_8 * 0x2000;
    }

    // FLAGS 9 - TV system, although official it is almost never used
    TV_SYSTEM = (FLAGS_9 & 0x01);

    // FLAGS 10
    // NOTE: The first 2 bits of the flag 10 byte actually also denote the TV
    // system, but since the flag 10 byte isn't even official and I already set
    // is using the flag 9 byte (not that that byte is commonly used anyway...),
    // I'm deciding to not parse the TV system value again
    PRG_RAM_PRESENT = (FLAGS_10 & 0x10); // if 5th bit is set
    BUS_CONFLICTS =
        (FLAGS_10 & 0x20); // if 6th bit is set (nesdev wiki barely says
                           // anything about this, but fuck it we ball)

    return 0;
  } else {
    MAPPER_NUMBER = mapper_lower_4_bits;
  }
  return 0;
}

// Load ROM size values LSB from bytes 4 and 5
int CART::READ_ROM_SIZE_NES_2() { return 0; }

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

  // Add bytes 12 - 15 together (this is for determining iNES format
  // version)
  array<uint8_t, 4> byte_confirm;
  uint16_t byte_total = 0;
  copy(HEADER_BUFFER.begin() + 12,
       HEADER_BUFFER.begin() +
           16, // the index pointed to by the second arg of copy() is NOT
               // included in the copy, so this copies the data in indicies 12,
               // 13, 14, and 15, but not 16
       byte_confirm.begin());
  for (uint8_t byte : byte_confirm) {
    byte_total += byte;
  }

  // iNES format version (if 3rd bit not set and 4th bit set (value of 2),
  // then iNES 2.0)
  uint8_t flags_7 = HEADER_BUFFER[7];
  if ((flags_7 & 0x0C) == 0x08) {
    CART_VERSION = CART_VERSION::INES_2;
  }
  // If 3rd bit set bit set and 4th not set (value of 1), the archaic iNES
  else if ((flags_7 & 0x0C) == 0x04) {
    CART_VERSION = CART_VERSION::ARCH_NES;
  }
  // If both 3rd and 4th bits are unset AND bytes 12-15 are 0, then iNES
  else if (((flags_7 & 0x0C) == 0x00) && byte_total == 0) {
    CART_VERSION = CART_VERSION::INES_1;
  }
  // else, archaic iNES
  else {
    CART_VERSION = CART_VERSION::ARCH_NES;
  }

  // Read all values from header
  if (READ_HEADER() != 0) {
    AddLogEntry(I18nObject.tr("Unable_to_read_rom."));
    return -1;
  }

  // Load trainer data if available (next 512 bytes)
  if (TRAINER_PRESENT) {
    // rom_file.seekg(16); // Set read position to the 17th byte (byte at index
    // 16)
    if (!rom_file.read(reinterpret_cast<char *>(TRAINER.data()),
                       TRAINER.size())) {
      AddLogEntry(I18nObject.tr("Unable_to_read_trainer."));
      return -1;
    }
  }

  // Load PRG ROM
  if (!rom_file.read(reinterpret_cast<char *>(PRG_ROM.data()), PRG_ROM_SIZE)) {
    AddLogEntry(I18nObject.tr("Unable_to_read_PRG_ROM."));
    return -1;
  }

  // Load CHR ROM (if present)
  if (!USES_CHR_RAM) {
    // Load CHR ROM
    if (!rom_file.read(reinterpret_cast<char *>(CHR_ROM.data()),
                       CHR_ROM_SIZE)) {
      AddLogEntry(I18nObject.tr("Unable_to_read_CHR_ROM."));
      return -1;
    }
  }

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
