#include "encoding.h"
#include "accelerator.h"
#include "mmu.h"
#include <cstring>
#include <iostream>

// Vector Register is 32 registers of 32 words each
#define VECTOR_REGISTERS 32
#define VECTOR_REGISTER_WORDS 32

class dummy_accelerator_t : public accelerator_t
{
 public:
  const char* name() { return "dummy_accelerator"; }
  dummy_accelerator_t()
  {
    std::cout << "INFO: Dummy Accelerator Instantiated\n";
    memset(vector_register, 0, sizeof(vector_register));
  }
  std::vector<insn_desc_t> get_instructions();
  reg_t vector_register[VECTOR_REGISTERS][VECTOR_REGISTER_WORDS];

 private:
};
