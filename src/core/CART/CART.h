#include <array>
#include <cstdint>
#include <string>
#include <vector>

using namespace std;

class CART {

public:
  //==========================
  //  FLAGS, METADATA, AND ROM
  //==========================

  // ROM
  vector<uint8_t> PRG_ROM;
  vector<uint8_t> CHR_ROM;

  // FLAG 6 DATA
  enum NAMETABLE_ARRANGEMENT {

    VERTICAL,
    HORIZONTAL

  };

  int NAMETABLE_ARRANGEMENT;
  bool SRAM_PRESENT;

  bool TRAINER_PRESENT;
  bool ALTERNATE_NAMETABLE_LAYOUT;

  uint8_t MAPPER_NUMBER_LOWER_4_BITS;

  // FLAG 6 DATA

  //==========================
  //  HELPER FUNCTIONS
  //==========================

  // HEADER - for iNES 1.0 bytes 11-15 are unused

  // Combines the flag helper functions to read the entire ROM header
  int READ_HEADER();

  // Reads the CHR ROM and PRG ROM size values from bytes 4 and 5 of the header
  int READ_ROM_SIZE_INES_1();

  // Reads the mapper, mirroring, battery, and trainer data from byte 6
  int READ_FLAGS_6_INES_1();

  // Reads the mapper, VS/Playchoice data, and the iNES 2.0 from byte 7
  int READ_FLAGS_7_INES_1();

  // Reads the PRG RAM size from byte 8 (rarely used)
  int READ_FLAGS_8_INES_1();

  // Reads the TV system data from byte 9 (also rarely used)
  int READ_FLAGS_9_INES_1();

  // Reads the TV system data, and PRG RAM presence from byte 10 (also rarely
  // used, in addition to being unofficial)
  int READ_FLAGS_10_INES_1();

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
