#include "dummy_accelerator.h"

class dummy_accelerator_t : public accelerator_t
{
 public:
   const char* name() { return "dummy_accelerator"; }

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

  
/*   
   reg_t custom0(accelerator_insn_t insn, reg_t xs1, reg_t xs2)
  {
    std::cout << "dummy accelerator custom0 called\n";
    reg_t prev_acc = acc[insn.rs2];

    if (insn.rs2 >= num_acc)
      illegal_instruction();

    switch (insn.funct)
    {
      case 0: // acc <- xs1
        acc[insn.rs2] = xs1;
        break;
      case 1: // xd <- acc (the only real work is the return statement below)
        break;
      case 2: // acc[rs2] <- Mem[xs1]
        acc[insn.rs2] = p->get_mmu()->load_uint64(xs1);
        break;
      case 3: // acc[rs2] <- accX + xs1
        acc[insn.rs2] += xs1;
        break;
      default:
        illegal_instruction();
    }

    return prev_acc; // in all cases, xd <- previous value of acc[rs2]
  }
  */

  dummy_accelerator_t()
  {
    std::cout << "INFO: Dummy Accelerator Instantiated\n";
    memset(vector_register, 0, sizeof(vector_register));
  }
  
  
  std::vector<insn_desc_t> get_instructions()
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

 private:
  reg_t vector_register[VECTOR_REGISTERS][VECTOR_REGISTER_WORDS];
};

REGISTER_EXTENSION(dummy_accelerator, []() { return new dummy_accelerator_t; })
