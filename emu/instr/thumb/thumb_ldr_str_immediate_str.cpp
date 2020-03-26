#include "thumb_ldr_str_immediate.h"

void thumb_ldr_str_immediate_str::run(gba_context * gba_)
{
}

instruction_string thumb_ldr_str_immediate_str::print()
{
	auto return_vec = instruction_string("STR");
	return_vec.add(expression(this->src_dest_reg));
	return_vec.add(expression(this->base_reg, this->offset));

	return return_vec;
}