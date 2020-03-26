#pragma once
#include "instruction.h"

namespace arm_parser
{
	instruction * parse_arm_branch(unsigned int current_instruction);
	instruction * parse_arm_exchange(unsigned int current_instruction);
	instruction * parse_arm_software_interrupt(unsigned int current_instruction);
	instruction * parse_arm_alu(unsigned int current_instruction);
	instruction * parse_arm_multiply(unsigned int current_instruction);
	instruction * parse_arm_psr(unsigned int current_instruction);
	instruction * parse_arm_swap(unsigned int current_instruction);
	instruction * parse_arm_single_data_transfer(unsigned int current_instruction);
	instruction * parse_arm_half_double_signed_transfer(unsigned int current_instruction);
	instruction * parse_arm_block_data_transfer(unsigned int current_instruction);
	instruction * parse_arm_coprocessor_register_transfer(unsigned int current_instruction);
	instruction * parse_arm_coprocessor_data_transfer(unsigned int current_instruction);
	instruction * parse_arm_coprocessor_data_operations(unsigned int current_instruction);
}
