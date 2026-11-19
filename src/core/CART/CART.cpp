#include "CART.h"
#include <algorithm>
#include <array>
#include <cmath>
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
    AddLogEntry(I18nObject.tr("FAILED_HEADER_CHECK"));
    return -1;
  }

  // Set flag bytes
  FLAGS_6 = HEADER_BUFFER[6];
  FLAGS_7 = HEADER_BUFFER[7];
  FLAGS_8 = HEADER_BUFFER[8];
  FLAGS_9 = HEADER_BUFFER[9];
  FLAGS_10 = HEADER_BUFFER[10];

  FLAGS_11 = HEADER_BUFFER[11];
  FLAGS_12 = HEADER_BUFFER[12];
  FLAGS_13 = HEADER_BUFFER[13];
  FLAGS_14 = HEADER_BUFFER[14];
  FLAGS_15 = HEADER_BUFFER[15];
  // iNES 1.0
  if (CART_VERSION == CART_VERSION::INES_1) {

    // Get size of CHR ROM, PRG ROM, and determine whether CHR RAM is used
    if (READ_ROM_SIZE_INES_1() != 0) {
      AddLogEntry(I18nObject.tr("FAILED_READING_ROM_SIZE"));
      return -1;
    }

    // Load flags
    if (READ_FLAGS_INES_1() != 0) {
      AddLogEntry(I18nObject.tr("FAILED_READING_FLAGS"));
      return -1;
    }

    return 0;
  }
  // iNES 2.0
  else if (CART_VERSION == CART_VERSION::NES_2) {

    // Read entire NES 2.0 header. Since bytes 4 and 5 only store the LSB (Least
    // Significant Bits) of the CHR and PRG rom sizes, I think its better not to
    // make a separate function to read the rom size.
    if (READ_HEADER_NES_2() != 0) {
      AddLogEntry(I18nObject.tr("FAILED_READING_HEADER"));
      return -1;
    }

    return 0;
  }

  return 0;
}

// iNES 2.0
int CART::READ_HEADER_NES_2() {

  // Read PRG and CHR rom size LSB from bytes 4 and 5
  uint8_t prg_rom_size_lsb = HEADER_BUFFER[4];
  uint8_t chr_rom_size_lsb = HEADER_BUFFER[5];

  // FLAGS 6

  // Parse nametable arrangement, horizontal arrangement means vertical
  // mirroring and vice-versa
  NAMETABLE_MIRRORING = (FLAGS_6 & 0x1);
  if (NAMETABLE_MIRRORING == NAMETABLE_MIRRORING::HORIZONTAL) {
    AddLogEntry(I18nObject.tr("NAMETABLE_MIRRORING:_HORIZONTAL"));
  } else if (NAMETABLE_MIRRORING == NAMETABLE_MIRRORING::VERTICAL) {
    AddLogEntry(I18nObject.tr("NAMETABLE_MIRRORING:_VERTICAL"));
  }

  // Determine if persistent saving is used (ex. battery-backed RAM) (if 2nd
  // bit is set)
  PRG_RAM_PRESENT = (FLAGS_6 & 0x2);
  AddLogEntry(I18nObject.tr("PRG_RAM_PRESENT:_") + to_string(PRG_RAM_PRESENT));

  // Determine if trainer is present (if 3rd bit is set)
  TRAINER_PRESENT = (FLAGS_6 & 0x4);
  AddLogEntry(I18nObject.tr("TRAINER_PRESENT:_") + to_string(TRAINER_PRESENT));

  // Determine if an alternative nametable layout is used (if 4th bit is set)
  ALTERNATE_NAMETABLE_LAYOUT = (FLAGS_6 & 0x8);
  AddLogEntry(I18nObject.tr("ALTERNATE_NAMETABLE_LAYOUT:_") +
              to_string(ALTERNATE_NAMETABLE_LAYOUT));

  // Get lower 4 bits of mapper number (mask last for bits then left shift 4)
  uint8_t mapper_lower_4_bits = (FLAGS_6 & 0xF0) >> 4;

  // FLAGS 7

  // Decides console type
  if ((FLAGS_7 & 0x03) == 0x00) {
    CONSOLE_TYPE = CONSOLE_TYPE::STANDARD_NES;
  } else if ((FLAGS_7 & 0x01) == 0x01) {
    CONSOLE_TYPE = CONSOLE_TYPE::VS_SYSTEM;
  } else if ((FLAGS_7 & 0x02) == 0x02) {
    CONSOLE_TYPE = CONSOLE_TYPE::PC10;
  } else if ((FLAGS_7 & 0x03) == 0x03) {
    CONSOLE_TYPE = CONSOLE_TYPE::EXTENDED_CONSOLE_TYPE;
  }

  AddLogEntry(I18nObject.tr("CONSOLE_TYPE:_") + to_string(CONSOLE_TYPE));

  // Get middle 4 bits of mapper number (mask last for bits then left shift 4),
  // in iNES 1.0 this would be the upper 4 bits of the mapper number, but mapper
  // numbers in NES 2.0 are 12 bits, there is also a 4 bit submapper number
  uint8_t mapper_middle_4_bits = (FLAGS_7 & 0xF0) >> 4;

  // FLAGS 8

  // Get most sig bits of mapper number
  uint8_t mapper_upper_4_bits = (FLAGS_8 & 0x0F);

  // Get final mapper
  MAPPER_NUMBER = ((mapper_upper_4_bits << 8) | (mapper_middle_4_bits << 4)) |
                  mapper_lower_4_bits;
  // Get submapper number, see comment in cart.h on what a submapper is
  SUBMAPPER_NUMBER = (FLAGS_8 & 0xF0) >> 4;

  AddLogEntry(I18nObject.tr("MAPPER_NUMBER:_") + to_string(MAPPER_NUMBER));
  AddLogEntry(I18nObject.tr("SUBMAPPER_NUMBER:_") +
              to_string(SUBMAPPER_NUMBER));

  // FLAGS 9, if the size msb is 0xF (1111), the exponent multiplier notation is
  // used to calculate the size.

  uint8_t prg_rom_size_msb = (FLAGS_9 & 0x0F);
  uint8_t chr_rom_size_msb = (FLAGS_9 & 0xF0) >> 4;

  // Get final PRG ROM size
  if (prg_rom_size_msb == 0x0F) { // exponent multiplier notation

    uint8_t exponent = (prg_rom_size_lsb & 0xFC) >>
                       2; // FC masks the most sig 6 bits (1111 11xx)
    uint8_t multiplier = (prg_rom_size_lsb & 0x03); // Get first 2 bits

    // Formula is 2^exponent * (multiplier * 2 + 1)
    PRG_ROM_SIZE =
        static_cast<uint8_t>((pow(2, exponent))) * ((multiplier * 2) + 1);

  } else { // if not 0xF, calculate normally

    PRG_ROM_SIZE = (prg_rom_size_msb << 8) | (prg_rom_size_lsb);
  }

  // Get final CHR ROM size
  if (chr_rom_size_msb == 0x0F) { // exponent multiplier notation

    uint8_t exponent = (chr_rom_size_lsb & 0xFC) >>
                       2; // FC masks the most sig 6 bits (1111 11xx)
    uint8_t multiplier = (chr_rom_size_lsb & 0x03); // Get first 2 bits

    // Formula is 2^exponent * (multiplier * 2 + 1)
    CHR_ROM_SIZE =
        static_cast<uint8_t>((pow(2, exponent))) * ((multiplier * 2) + 1);

  } else { // if not 0xF, calculate normally

    CHR_ROM_SIZE = (chr_rom_size_msb << 8) | (chr_rom_size_lsb);
  }

  // Actual value are stored as amount of bytes, but for readability divide by
  // 1KB (0x400)
  AddLogEntry("PRG ROM: " + to_string(PRG_ROM_SIZE / 0x400) + "KB");
  AddLogEntry("CHR ROM: " + to_string(CHR_ROM_SIZE / 0x400) + "KB");

  // FLAGS 10

  uint8_t prg_ram_size_shift_count = (FLAGS_10 & 0x0F);
  uint8_t eeprom_size_shift_count = ((FLAGS_10 & 0xF0) >> 4);

  if (prg_ram_size_shift_count == 0x00) {
    PRG_RAM_PRESENT = false;
  } else { // if shift count is not 0, 64 << shift value
    PRG_RAM_SIZE = 0x40 << prg_ram_size_shift_count;
    AddLogEntry(I18nObject.tr("PRG_RAM_SIZE:_") + to_string(PRG_RAM_SIZE));
  }
  if (eeprom_size_shift_count == 0x00) {
    EEPROM_PRESENT = false;
  } else {
    EEPROM_SIZE = 0x40 << eeprom_size_shift_count;
    AddLogEntry(I18nObject.tr("EEPROM_SIZE:_") + to_string(EEPROM_SIZE));
  }

  // FLAGS 11

  uint8_t chr_ram_size_shift_count = (FLAGS_10 & 0x0F);
  uint8_t chr_nvram_size_shift_count = ((FLAGS_10 & 0xF0) >> 4);

  if (chr_ram_size_shift_count == 0x00) {
    USES_CHR_RAM = false;
  } else { // if shift count is not 0, 64 << shift value
    CHR_RAM_SIZE = 0x40 << chr_ram_size_shift_count;
    AddLogEntry(I18nObject.tr("CHR_RAM_SIZE:_") + to_string(CHR_RAM_SIZE));
  }
  if (chr_nvram_size_shift_count == 0x00) {
    CHR_NVRAM_PRESENT = false;
  } else {
    CHR_NVRAM_SIZE = 0x40 << chr_nvram_size_shift_count;
    AddLogEntry(I18nObject.tr("CHR_NVRAM_SIZE:_") + to_string(CHR_NVRAM_SIZE));
  }

  // FLAGS 12

  CPU_PPU_TIMING = (FLAGS_12 & 0x3);

  // FLAGS 13
  if (CONSOLE_TYPE == CONSOLE_TYPE::VS_SYSTEM) {
    VS_PPU_TYPE = (FLAGS_13 & 0x0F);
    VS_HARDWARE_TYPE = (FLAGS_13 & 0xF0) >> 4;
  } else if (CONSOLE_TYPE == CONSOLE_TYPE::EXTENDED_CONSOLE_TYPE) {
    EXT_SYS_TYPE = (FLAGS_13 & 0x0F);
  }

  // FLAGS 14
  MISC_ROMS = FLAGS_15;

  // FLAGS 15
  DEFAULT_EXPANSION_DEVICE = FLAGS_15;

  return 0;
}

// Read flag bytes and set values for iNES 1.0
int CART::READ_FLAGS_INES_1() {

  // FLAGS 6

  // Parse nametable arrangement, horizontal arrangement means vertical
  // mirroring and vice-versa
  NAMETABLE_MIRRORING = (FLAGS_6 & 0x1);
  if (NAMETABLE_MIRRORING == NAMETABLE_MIRRORING::HORIZONTAL) {
    AddLogEntry(I18nObject.tr("NAMETABLE_MIRRORING:_HORIZONTAL"));
  } else if (NAMETABLE_MIRRORING == NAMETABLE_MIRRORING::VERTICAL) {
    AddLogEntry(I18nObject.tr("NAMETABLE_MIRRORING:_VERTICAL"));
  }

  // Determine if persistent saving is used (ex. battery-backed SRAM) (if 2nd
  // bit is set)
  PRG_RAM_PRESENT = (FLAGS_6 & 0x2);
  AddLogEntry(I18nObject.tr("PRG_RAM_PRESENT:_") + to_string(PRG_RAM_PRESENT));

  // Determine if trainer is present (if 3rd bit is set)
  TRAINER_PRESENT = (FLAGS_6 & 0x4);
  AddLogEntry(I18nObject.tr("TRAINER_PRESENT:_") + to_string(TRAINER_PRESENT));

  // Determine if an alternative nametable layout is used (if 4th bit is set)
  ALTERNATE_NAMETABLE_LAYOUT = (FLAGS_6 & 0x8);
  AddLogEntry(I18nObject.tr("ALTERNATE_NAMETABLE_LAYOUT:_") +
              to_string(ALTERNATE_NAMETABLE_LAYOUT));

  // Get lower 4 bits of mapper number (mask last for bits then left shift 4)
  uint8_t mapper_lower_4_bits = (FLAGS_6 & 0xF0) >> 4;

  // FLAGS 7

  if (CART_VERSION !=
      CART_VERSION::ARCH_NES) { // bytes 7-15 are unused in archaic iNES

    // Does the rom use the VS unisystem (I dont even know what the hell that
    // is, right now I'm basing my implemtation off iNES format page on nesdev
    // wiki and saw vs system. Maybe I'll implement it down the line if I'm
    // bored and I want to make this emulator more accurate)
    if ((FLAGS_7 & 0x01) == 0x01) {
      CONSOLE_TYPE = CONSOLE_TYPE::VS_SYSTEM;
    }
    // Same as above, apparently PC10 was some arcade thing I guess?
    else if ((FLAGS_7 & 0x02) == 0x02) {
      CONSOLE_TYPE = CONSOLE_TYPE::PC10;
    } else if ((FLAGS_7 & 0x03) == 0x00) {
      CONSOLE_TYPE = CONSOLE_TYPE::STANDARD_NES;
    }

    // Get upper 4 bits of mapper number (mask last for bits then left shift 4)
    uint8_t mapper_upper_4_bits = (FLAGS_7 & 0xF0) >> 4;

    // Get final mapper number
    MAPPER_NUMBER = (mapper_upper_4_bits << 4) | mapper_lower_4_bits;
    AddLogEntry(I18nObject.tr("MAPPER_NUMBER:_") + to_string(MAPPER_NUMBER));

    // FLAGS 8 - flags 8 byte just contains the PRG RAM size, although in
    // iNES 1.0 this is not considered reliable. I'm setting it this way for now
    // and will change is once iNES 2.0 is supported

    if (FLAGS_8 == 0) { // for compatibility purposes, a value of 0 infers 8KB
      PRG_RAM_SIZE = 0x2000;
    } else { // like CHR ROM size, it is in 8KB units, so multiply by 0x2000
      PRG_RAM_SIZE = FLAGS_8 * 0x2000;
    }
    AddLogEntry(I18nObject.tr("PRG_RAM_SIZE:_") + to_string(PRG_RAM_SIZE));

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
    AddLogEntry(I18nObject.tr("MAPPER_NUMBER:_") + to_string(MAPPER_NUMBER));
  }
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
    AddLogEntry(I18nObject.tr("UNABLE_TO_READ_ROM"));
    return -1;
  }

  // reinterpret_cast allows any pointer to be converted into any other
  // pointer type, ifstream .read takes in char* and streamsize, so
  // header_buffer is casted to char*
  if (!rom_file.read(reinterpret_cast<char *>(HEADER_BUFFER.data()),
                     HEADER_BUFFER.size())) {
    AddLogEntry(I18nObject.tr("UNABLE_TO_READ_ROM"));
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
    CART_VERSION = CART_VERSION::NES_2;
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

  AddLogEntry(to_string(CART_VERSION));

  // Read all values from header
  if (READ_HEADER() != 0) {
    AddLogEntry(I18nObject.tr("UNABLE_TO_READ_HEADER"));
    return -1;
  }

  // Load trainer data if available (next 512 bytes)
  if (TRAINER_PRESENT) {
    if (!rom_file.read(reinterpret_cast<char *>(TRAINER.data()),
                       TRAINER.size())) {
      AddLogEntry(I18nObject.tr("UNABLE_TO_READ_TRAINER"));
      return -1;
    }
  }

  // Load PRG ROM
  if (!rom_file.read(reinterpret_cast<char *>(PRG_ROM.data()), PRG_ROM_SIZE)) {
    AddLogEntry(I18nObject.tr("UNABLE_TO_READ_PRG_ROM"));
    return -1;
  }

  // Load CHR ROM (if present)
  if (!USES_CHR_RAM) {
    // Load CHR ROM
    if (!rom_file.read(reinterpret_cast<char *>(CHR_ROM.data()),
                       CHR_ROM_SIZE)) {
      AddLogEntry(I18nObject.tr("UNABLE_TO_READ_CHR_ROM"));
      return -1;
    }
  }

  // TODO: Implement playchoice (If I'm bored or have the time)

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
