#include "dummy_accelerator.h"

   static reg_t accelltovec(processor_t* p, insn_t insn, reg_t pc) {
      dummy_accelerator_t* accelerator = static_cast<dummy_accelerator_t*>(p->get_extension());
      reg_t vrd = READ_REG(insn.rd());
      reg_t value = READ_REG(insn.rs1());
      reg_t position = READ_REG(insn.rs2());
      std::cout << "accel to vec instruction\n";
      std::cout << "vrd  = " << vrd << "\n";
      std::cout << "value = " << value << "\n";
      std::cout << "position = " << position << "\n";
      accelerator->vector_register[vrd][position] = value;
      WRITE_REG(insn.rs2(),position+1);
	   return pc + 4;
   }
   static reg_t accelltoreg(processor_t* p, insn_t insn, reg_t pc) {
      dummy_accelerator_t* accelerator = static_cast<dummy_accelerator_t*>(p->get_extension());
      std::cout << "accel to reg instruction\n";
      reg_t rd = READ_REG(insn.rd());
      reg_t vsource = READ_REG(insn.rs1());
      reg_t position = READ_REG(insn.rs2());
      reg_t value = accelerator->vector_register[vsource][position];
      std::cout << "accel to vec instruction\n";
      std::cout << "rd  = " << rd << "\n";
      std::cout << "value = " << value << "\n";
      std::cout << "position = " << position << "\n";
      WRITE_RD(value);
	   return pc + 4;
   }
   static reg_t acceladd(processor_t* p, insn_t insn, reg_t pc) {
      std::cout << "accel add instruction\n";
	   return pc + 4;
   }


  
  std::vector<insn_desc_t> dummy_accelerator_t::get_instructions()
  {
  std::vector<insn_desc_t> insns;
  //                              +- match custom0 opcode
  //                              |                +- mask for opcode recognition
  //                              |                |               +- function called by 32bits implementation
  //                              |                |               |          +- function called by 64bits implementation
  //                              |                |               |          |
  insns.push_back((insn_desc_t){MATCH_ACCELTOVEC, MASK_ACCELTOVEC, accelltovec, accelltovec});
  insns.push_back((insn_desc_t){MATCH_ACCELTOREG, MASK_ACCELTOREG, accelltoreg, accelltoreg});
  //insns.push_back((insn_desc_t){MATCH_ACCELADD , MASK_ACCELADD , acceladd, acceladd});
  //insns.push_back((insn_desc_t){0x2b, 0x7f, c1, c1});
  //insns.push_back((insn_desc_t){0x5b, 0x7f, c2, c2});
  //insns.push_back((insn_desc_t){0x7b, 0x7f, c3, c3});
  return insns;
  }

REGISTER_EXTENSION(dummy_accelerator, []() { return new dummy_accelerator_t; })
