#include "thumb_ldr_str_half.h"

void thumb_ldr_str_half_ldrh::run(gba_context * gba_)
{
}

instruction_string thumb_ldr_str_half_ldrh::print()
{
	auto return_vec = instruction_string("LDRH");
	return_vec.add(expression(this->src_dest_reg));
	return_vec.add(expression(this->base_reg, this->offset));

	return return_vec;
}