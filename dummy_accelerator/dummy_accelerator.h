#include "encoding.h"
#include "accelerator.h"
#include "mmu.h"
#include <cstring>
#include <iostream>

// Vector Register is 32 registers of 32 words each
#define VECTOR_REGISTERS 32
#define VECTOR_REGISTER_WORDS 32


