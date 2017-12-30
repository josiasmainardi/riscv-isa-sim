#ifndef _RISCV_ROCC_H
#define _RISCV_ROCC_H

#include "extension.h"

struct accelerator_insn_t
{
  unsigned opcode : 7;
  unsigned rd : 5;
  unsigned xs2 : 1;
  unsigned xs1 : 1;
  unsigned xd : 1;
  unsigned rs1 : 5;
  unsigned rs2 : 5;
  unsigned funct : 7;
};

union accelerator_insn_union_t
{
  accelerator_insn_t r;
  insn_t i;
};

class accelerator_t : public extension_t
{
 public:
  virtual reg_t custom0(accelerator_insn_t insn, reg_t xs1, reg_t xs2);
  virtual reg_t custom1(accelerator_insn_t insn, reg_t xs1, reg_t xs2);
  virtual reg_t custom2(accelerator_insn_t insn, reg_t xs1, reg_t xs2);
  virtual reg_t custom3(accelerator_insn_t insn, reg_t xs1, reg_t xs2);
  std::vector<insn_desc_t> get_instructions();
  std::vector<disasm_insn_t*> get_disasms();
};

#endif
