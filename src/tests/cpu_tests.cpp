#include "../core/CPU/CPU.h"
#include <cassert>

int main() {

  CPU *test_cpu = new CPU();

  test_cpu->SET_FLAG(CPU::STATUS_FLAG::INT_DISABLE);
  assert(test_cpu->GET_FLAG(CPU::STATUS_FLAG::INT_DISABLE));
}
