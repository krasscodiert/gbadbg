#include "arm_branch.h"

int arm_branch_imm_instruction::calculate_target_address() const
{
	return this->offset * 4 + 8;
}

void arm_branch_imm_instruction::run(gba_context * gba)
{
}

instruction_string arm_branch_imm_instruction::print()
{
	return std::string();
}

int arm_branch_reg_instruction::calculate_target_address(unsigned int address) const
{
	return address - 1;
}

void arm_branch_reg_instruction::run(gba_context* gba)
{
}

instruction_string arm_branch_reg_instruction::print()
{
	return std::string();
}
