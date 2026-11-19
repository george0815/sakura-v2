#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <sys/types.h>
#include <vector>

using namespace std;

class CART {

public:
  //==========================
  //  CHR/PRG ROM, TRAINER DATA
  //==========================

  // Roms sizes, for iNES 1.0, these values will be multiplied by 16KB and 8KB
  // respectively to get the actual size. For NES 2.0, the least significant
  // bits read from bytes 4-5 of the header are combined with the most
  // significant bits from byte to get the total size. If the last 4 bits are
  // 0xF, the exponent-multiplier notation is used
  size_t PRG_ROM_SIZE;
  size_t CHR_ROM_SIZE;

  // PRG ROM is the part of the rom chip that holds the games program (hence
  // "PRG") data. This is where the PC reads instructions from. At a minimum
  // there is always at least one PRG ROM
  vector<uint8_t> PRG_ROM;
  // CHR ROM contains the sprites and the visual assets of the game. This is
  // available to the PPU "from the moment it turns on".
  vector<uint8_t> CHR_ROM;

  // TRAINER
  array<uint8_t, 512> TRAINER;
  bool TRAINER_PRESENT;

  //==========================
  //  RAM
  //==========================

  bool USES_CHR_RAM; // CHR RAM contains visual assets that the CPU has loaded
                     // from PRG ROM.
  bool PRG_RAM_PRESENT;   // Battery-backed RAM, mapped to address space
                          // $6000-$7FFF, used for persistent saving
  bool EEPROM_PRESENT;    // Used in homebrew roms to store save data without a
                          // battery, rarely used by offiial NES games
  bool CHR_NVRAM_PRESENT; // Battery backed CHR RAM

  // Sizes for the above RAM types
  size_t PRG_RAM_SIZE;
  size_t EEPROM_SIZE;
  size_t CHR_RAM_SIZE;
  size_t CHR_NVRAM_SIZE;

  // Vectors for ram NOTE: only CHR RAM and PRG RAM are impelmented for now
  vector<uint8_t> PRG_RAM;
  vector<uint8_t> CHR_RAM;

  //==========================
  //  MAPPER DATA/NAMETABLE MIRRORING
  //==========================

  uint16_t MAPPER_NUMBER; // Mappers extend the capabilities of the NES. For
                          // example it can utilize bank switching to allow a
                          // cartridge to have more data than the address space
                          // would otherwise allow. Nametable mirroring is
                          // another fucntion of a mapper. (There will be a more
                          // detailed explanation in the comments in the files
                          // for the mapper files) Potential values:
                          //   Archaic iNES: 0-15 (4 bits)
                          //   iNES 1.0    : 0-255 (8 bits)
                          //   NES 2.0     : 0-4095 (12 bits)

  uint8_t SUBMAPPER_NUMBER; // According to nesdev wiki, used for "designating
                            // functionally distinct variants of iNES mappers
                            // that cannot be distinguished from the memory size
                            // fields alone."

  // PPU nametables are basically areas of memory (1024 - 1KB size) used by the
  // PPU to layout backgrounds.
  // - Each byte of the nametable controls an 8x8 pixel cell/tile.
  // - 30 rows of 32 tiles, 960 totol tiles. 30 x 8 = 240, 32 * 8 = 256 for a
  // width of 240px and a height of 256px
  //
  // As for mirroring, the NES has 4 logical nametables but only enough ram
  // for 2. Mirroring controls which areas of memory contain which nametables
  enum NAMETABLE_MIRRORING {

    HORIZONTAL = 0, // $2000 and $2400, contain the first, with $2800 and $2C00
                    // containing the second
    VERTICAL = 1    // $2000 and $2800, contain the first, with $2400 and $2C00
                    // containing the second

  };
  int NAMETABLE_MIRRORING;
  bool ALTERNATE_NAMETABLE_LAYOUT; // Some mappers can use alternate schemes

  //==========================
  //  HEADER DATA AND METADATA
  //==========================

  // Holds first 16 bytes of the ROM file
  array<uint8_t, 16> HEADER_BUFFER;

  // flag bytes, 11-15 are only used in the NES 2.0 format
  uint8_t FLAGS_6;  // Mapper, mirroring, battery, trainer
  uint8_t FLAGS_7;  // Mapper, console type, NES 2.0 flag
  uint8_t FLAGS_8;  // iNES 1.0: PRG RAM size, NES 2.0: Mapper/submapper
  uint8_t FLAGS_9;  // iNES 1.0: TV system, NES 2.0: PRG/CHR ROM size
  uint8_t FLAGS_10; // iNES 1.0: TV system, PRG RAM presence, NES 2.0:
                    // PRG-RAM/EEPROM size

  uint8_t FLAGS_11; // CHR-RAM size
  uint8_t FLAGS_12; // CPU/PPU timing
  uint8_t FLAGS_13; // Console type
  uint8_t FLAGS_14; // Misc roms
  uint8_t FLAGS_15; // Default expansion device

  // Most modern roms use NES 2.0 rather than iNES 1.0, but NES 2.0 is backwards
  // compatible
  enum CART_VERSION {

    ARCH_NES = 0,
    INES_1 = 1,
    NES_2 = 2,

  };

  int CART_VERSION;

  //==========================
  //  CONSOLE TYPES/TV SYSTEM
  //==========================

  uint8_t VS_HARDWARE_TYPE; // If the rom is for the VS system, denotes whether
                            // its for the Vs. Unisystem or Dual System
  uint8_t VS_PPU_TYPE;      // PPU type of the Vs. System
  uint8_t EXT_SYS_TYPE; // If the rom is for one of the extended console types,
                        // denotes which one

  // The NES had 2 arcade variants - The VS. System and the Playchoice-10, in
  // addition to various other versions such as the Famiclone
  enum CONSOLE_TYPE {

    STANDARD_NES = 0,
    VS_SYSTEM = 1,
    PC10 = 2,
    EXTENDED_CONSOLE_TYPE = 3

  };
  int CONSOLE_TYPE;

  // Different TV system
  // NTSC: NA/Japan, 60hz, ~17 faster, PAL: AUS/EUR, 50hz, slower
  enum TV_SYSTEM { NTSC = 0, PAL = 1 };
  int TV_SYSTEM;

  //==========================
  //  BUS CONFLICTS, TIMING, MISC ROMS, DEFAULT EXPANSION DEVICE
  //==========================

  // A bus confllict occurs "when two logic devices output different values on
  // the same bus line"
  bool BUS_CONFLICTS;

  // Denotes which PPU/CPU combo's timing that should be used when emulating the
  // game
  enum CPU_PPU_TIMING {

    RP2C02 = 0, // NTSC
    RP2C07 = 1, // PAL
    MULTIPLE = 2,
    UA6538 = 3, // Dendy (NOTE: I have no clue what Dendy means)

  };
  int CPU_PPU_TIMING;

  // Denotes the number of miscellaneous roms. Some NES
  // console types (like the PC10) can have extra chips. The memory for it
  // occupies the remaining space after the CHR_ROM.
  uint8_t MISC_ROMS;

  // Denotes the expansion device (such as the power
  // pad, zapper, etc) the rom expects at CPU $4016/$4017. For example if byte
  // 15 == $08, then the rom expects a Zapper. $00 is unspecified and $01 is for
  // standard NES controllers
  uint8_t DEFAULT_EXPANSION_DEVICE;

  //==========================
  //  HELPER FUNCTIONS
  //==========================

  // Reads the CHR ROM and PRG ROM size values from bytes 4 and 5 of the header
  int READ_ROM_SIZE_INES_1();

  // Combines the flag helper functions to read the entire ROM header
  int READ_HEADER();

  // Reads the mapper, mirroring, battery, and trainer data from byte 6,
  // the VS/Playchoice data, and the iNES 2.0 from byte 7,
  // the PRG RAM size from byte 8 (rarely used),
  // the TV system data from byte 9 (also rarely used),
  // and the TV system data, and PRG RAM presence from byte 10 (also rarely
  // used, in addition to being unofficial)
  int READ_FLAGS_INES_1();

  // Reads the data from the byte flags of the header for NES 2.0 roms
  int READ_HEADER_NES_2();

  // PC10 data, might implement this far into the future if im bored
  int READ_PLAYCHOICE_INST_ROM_INES_1(); // NOTE: NOT CURRENTLY IMPLEMENTED
  int READ_PLAYCHOICE_PROM_INES_1();     // NOTE: NOT CURRENTLY IMPLEMENTED

  // Attempts to load rom using provided file name
  int READ_ROM(string file_name);

  // Verifies if the ROM is a valid ROM by checking the first 4 bytes of the
  // header
  int CHECK_HEADER(array<uint8_t, 4> bytes);
};
