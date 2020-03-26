#include "arm_single_data_transfer.h"
#include "arm_util.h"

void arm_str::run(gba_context * gba)
{
	bool r15_as_base = (this->reg_base == cpu::r15);

	if (!this->is_pre_indexing)
	{
		gba->memory->write_word(static_cast<int>((this->transfer_byte ? gba->cpu.reg<byte>(this->reg_dest) : gba->cpu.reg<int>(this->reg_dest))), gba->cpu.reg<int>(this->reg_base));
	}

	if (this->type == register_offset)
		switch (this->type)
		{
		case register_offset:
			gba->cpu.reg(this->reg_offset, arm_util::arm_shift(gba->cpu.reg<int>(this->reg_offset), this->shift_amount, this->shift_type));
			this->calculated_offset = gba->cpu.reg<int>(this->reg_base) + (gba->cpu.reg<int>(this->reg_offset) * (this->add_to_base ? 1 : -1));
			break;
		case immediate_offset:
			this->calculated_offset = gba->cpu.reg<int>(this->reg_base) + (this->immediate * (this->add_to_base ? 1 : -1));
			break;
		default:;
		}

	if (this->is_pre_indexing)
	{
		gba->memory->write_word(static_cast<int>((this->transfer_byte ? gba->cpu.reg<byte>(this->reg_dest) : gba->cpu.reg<int>(this->reg_dest))), this->calculated_offset);
	}

	arm_single_data_transfer_instruction::run(gba);
}

instruction_string arm_str::print()
{
	return std::string();
}
