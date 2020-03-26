#include "arm_alu.h"
#include "arm_util.h"

void arm_alu_instruction::run(gba_context * gba)
{
	switch (this->type)
	{
	case immediate:
		this->shift_immediate = arm_util::arm_shift(this->shift_immediate, this->shift_by_immediate * 2, arm_globals::arm_shift_type::ror);
		break;
	case register_reg_amount:
		gba->cpu.reg(this->second_op, arm_util::arm_shift(gba->cpu.reg<int>(this->second_op), gba->cpu.reg<int>(this->reg_shift), this->shift_type));
		break;
	case register_imm_amount:
		gba->cpu.reg(this->second_op, arm_util::arm_shift(gba->cpu.reg<int>(this->second_op), this->shift_amount, this->shift_type));
		break;
	default: throw std::exception("invalid instruction type");
	}
}

instruction_string arm_alu_instruction::print()
{
	auto return_vec = instruction_string("");
	switch (this->type)
	{
	case immediate:
		return_vec.add(expression(arm_globals::ror, this->shift_immediate));
		break;
	case register_reg_amount:
		return_vec.add(expression(this->shift_type, this->second_op));
		break;
	case register_imm_amount:
		return_vec.add(expression(this->shift_type, this->second_op));
		break;
	default:
		break;
	}
	return return_vec;
}