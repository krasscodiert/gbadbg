#include "thumb_ldr_str_byte_half.h"

void thumb_ldr_str_byte_half_ldsh::run(gba_context * gba_)
{
}

instruction_string thumb_ldr_str_byte_half_ldsh::print()
{
	auto return_vec = instruction_string("LDSH");
	return_vec.add(expression(this->src_dest_reg));
	return_vec.add(expression(this->base_reg, this->off_reg));

	return return_vec;
}