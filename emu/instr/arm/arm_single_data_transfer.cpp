#include "arm_single_data_transfer.h"

void arm_single_data_transfer_instruction::run(gba_context * gba)
{
	//TODO: non-privileged access ? 
	if (this->address_into_base || !this->is_pre_indexing) 
	{
		gba->cpu.reg(this->reg_base, this->calculated_offset);
	}
	else
	{
		
	}
}

instruction_string arm_single_data_transfer_instruction::print()
{
	return std::string();
}