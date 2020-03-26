#include "arm_alu.h"
void arm_mov::run(gba_context * gba)
{
	arm_alu_instruction::run(gba);

	int op2 = 0;
	switch (this->type)
	{
	case immediate:
		op2 = this->shift_immediate;
		break;
	case register_reg_amount:
	case register_imm_amount:
		op2 = gba->cpu.reg<int>(this->second_op);
		break;
	default:;
	}
	gba->cpu.reg(this->reg_dest, op2);
}

instruction_string arm_mov::print()
{
	return std::string();
}