#include "thumb_ldr_str_immediate.h"

void thumb_ldr_str_immediate_ldrb::run(gba_context * gba_)
{
}

instruction_string thumb_ldr_str_immediate_ldrb::print()
{
	auto return_vec = instruction_string("LDRB");
	return_vec.add(expression(this->src_dest_reg));
	return_vec.add(expression(this->base_reg, this->offset));

	return return_vec;
}