#include "thumb_ldr_str_half.h"

void thumb_ldr_str_half_strh::run(gba_context * gba_)
{
}

instruction_string thumb_ldr_str_half_strh::print()
{
	auto return_vec = instruction_string("STRH");
	return_vec.add(expression(this->src_dest_reg));
	return_vec.add(expression(this->base_reg, this->offset));

	return return_vec;
}