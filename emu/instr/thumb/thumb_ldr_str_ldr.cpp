#include "thumb_ldr_str.h"

void thumb_ldr_str_ldr::run(gba_context * gba_)
{
}

instruction_string thumb_ldr_str_ldr::print()
{
	auto return_vec = instruction_string("LDR");
	return_vec.add(expression(this->src_dest_reg));
	return_vec.add(expression(this->base_reg, this->off_reg));

	return return_vec;
}