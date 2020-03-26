#include "arm_branch.h"

arm_blx_imm::arm_blx_imm(int offset) : arm_b(offset) {}

void arm_blx_imm::run(gba_context * gba)
{
}

std::string arm_blx_imm::print()
{
	return std::string();
}
