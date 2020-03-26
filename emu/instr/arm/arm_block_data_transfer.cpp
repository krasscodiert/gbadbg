#include "arm_block_data_transfer.h"


void arm_block_data_transfer_instruction::parse_register_list(int list)
{
	for (int i = 0; i < 16; ++i)
	{
		this->registers[i] = util::is_bit_set(i, list);
	}
}

void arm_block_data_transfer_instruction::run(gba_context * gba)
{
}

instruction_string arm_block_data_transfer_instruction::print()
{
	return std::string();
}
