#include <string>

using namespace std;

class EMU {

public:
  // Starts rom, contains main emulation loop
  int START_ROM(string file_name, string &error_message);
};
