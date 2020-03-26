#pragma once
#include "instruction.h"

namespace thumb_parser
{
	instruction * parse_thumb_shift(unsigned int current_instruction);
	instruction * parse_thumb_add_sub(unsigned int current_instruction);
	instruction * parse_thumb_immediate(unsigned int current_instruction);
	instruction * parse_thumb_alu(unsigned int current_instruction);
	instruction * parse_thumb_hireg_bx(unsigned int current_instruction);
	instruction * parse_thumb_ldr_pc(unsigned int current_instruction);
	instruction * parse_thumb_ldr_str(unsigned int current_instruction);
	instruction * parse_thumb_ldr_str_byte_half(unsigned int current_instruction);
	instruction * parse_thumb_ldr_str_immediate(unsigned int current_instruction);
	instruction * parse_thumb_ldr_str_half(unsigned int current_instruction);
	instruction * parse_thumb_ldr_str_sp(unsigned int current_instruction);
	instruction * parse_thumb_add_offset_relative(unsigned int current_instruction);
	instruction * parse_thumb_add_offset_sp(unsigned int current_instruction);
	instruction * parse_thumb_push_pop(unsigned int current_instruction);
	instruction * parse_thumb_multiple_ld_st(unsigned int current_instruction);
	instruction * parse_thumb_conditional_branch(unsigned int current_instruction);
	instruction * parse_thumb_software_interrupt(unsigned int current_instruction);
	instruction * parse_thumb_unconditional_branch(unsigned int current_instruction);
	instruction * parse_thumb_long_branch_link(unsigned int current_instruction);
}