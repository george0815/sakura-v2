#include <array>
#include <cstdint>
#include <string>
#include <sys/types.h>
#include <vector>

using namespace std;

class CART {

public:
  //==========================
  //  FLAGS, METADATA, AND ROM
  //==========================

  // Roms sizes, these values will be multiplied by 16KB and 8KB respectively to
  // get the actual size
  size_t PRG_ROM_SIZE;
  size_t CHR_ROM_SIZE;

  bool USES_CHR_RAM;

  array<uint8_t, 16> HEADER_BUFFER;

  // FLAGS 6 DATA
  enum NAMETABLE_MIRRORING {

    HORIZONTAL = 0,
    VERTICAL = 1

  };
  int NAMETABLE_MIRRORING;

  bool SRAM_PRESENT;

  bool TRAINER_PRESENT;
  bool ALTERNATE_NAMETABLE_LAYOUT;

  uint8_t MAPPER_NUMBER_LOWER_4_BITS;

  // FLAGS 7 DATA

  bool PLAYCHOICE;

  bool VS_UNISYSTEM;

  enum CART_VERSION {

    ARCH_NES,
    INES_1,
    INES_2,

  };

  int CART_VERSION;

  uint8_t MAPPER_NUMBER_UPPER_4_BITS;

  // FLAGS 8 DATA

  uint8_t PRG_RAM_SIZE;

  // FLAGS 9 DATA

  enum TV_SYSTEM { NTSC, PAL };

  int TV_SYSTEM;

  // FLAGS 10 DATA

  bool PRG_RAM_PRESENT;

  // TRAINER

  // ROM
  vector<uint8_t> PRG_ROM;
  vector<uint8_t> CHR_ROM;

  // PLAYCHOICE INST-ROM
  // PLAYCHOICE PROM

  //==========================
  //  HELPER FUNCTIONS
  //==========================

  // HEADER - for iNES 1.0 bytes 11-15 are unused

  // Combines the flag helper functions to read the entire ROM header
  int READ_HEADER();

  // Reads the CHR ROM and PRG ROM size values from bytes 4 and 5 of the header
  int READ_ROM_SIZE_INES_1();

  // Reads the mapper, mirroring, battery, and trainer data from byte 6,
  // the VS/Playchoice data, and the iNES 2.0 from byte 7,
  // the PRG RAM size from byte 8 (rarely used),
  // the TV system data from byte 9 (also rarely used),
  // and the TV system data, and PRG RAM presence from byte 10 (also rarely
  // used, in addition to being unofficial)
  int READ_FLAGS_INES_1();

  // DATA

  // Reads trainer data if available, trainers are 512 bytes which are loaded
  // before the game starts, enabling cheats
  int READ_TRAINER();

  // Reads PRG ROM into buffer
  int READ_PRG_ROM_INES_1();

  // Reads CHR ROM into buffer
  int READ_CHR_ROM_INES_1();

  // PC10 data, might implement this far into the future if im bored
  int READ_PLAYCHOICE_INST_ROM_INES_1();
  int READ_PLAYCHOICE_PROM_INES_1();

  // GENERAL HELPER FUNCTIONS

  // Attempts to load rom using provided file name
  int READ_ROM(string file_name);

  // Verifies if the ROM is a valid ROM by checking the first 4 bytes of the
  // header
  int CHECK_HEADER(array<uint8_t, 4> bytes);
};
