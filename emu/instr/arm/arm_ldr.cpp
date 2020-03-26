#include "arm_single_data_transfer.h"
#include "arm_util.h"

void arm_ldr::run(gba_context * gba)
{
	bool r15_as_base = (this->reg_base == cpu::r15);

	unsigned int base = gba->cpu.reg<int>(this->reg_base) + (r15_as_base ? 8 : 0);

	if (!this->is_pre_indexing) 
	{
		gba->cpu.reg(this->reg_dest, transfer_byte ? gba->memory->read_byte(base) : gba->memory->read_word(base));
	}

	switch (this->type)
	{
	case register_offset:
		gba->cpu.reg(this->reg_offset, arm_util::arm_shift(gba->cpu.reg<int>(this->reg_offset), this->shift_amount, this->shift_type));
		this->calculated_offset = base + (gba->cpu.reg<int>(this->reg_offset) * (this->add_to_base ? 1 : -1));
		break;
	case immediate_offset:
		this->calculated_offset = base + (this->immediate * (this->add_to_base ? 1 : -1));
		break;
	default:;
	}

	if (this->is_pre_indexing) 
	{
		gba->cpu.reg(this->reg_dest, transfer_byte ? gba->memory->read_byte(this->calculated_offset) : gba->memory->read_word(this->calculated_offset));
	}

	arm_single_data_transfer_instruction::run(gba);
}

instruction_string arm_ldr::print()
{
	return std::string();
}