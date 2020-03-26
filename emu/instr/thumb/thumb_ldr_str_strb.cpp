#include "thumb_ldr_str.h"

void thumb_ldr_str_strb::run(gba_context * gba_)
{
}

instruction_string thumb_ldr_str_strb::print()
{
	auto return_vec = instruction_string("STRB");
	return_vec.add(expression(this->src_dest_reg));
	return_vec.add(expression(this->base_reg, this->off_reg));

	return return_vec;
}