#include "thumb_ldr_str_sp.h"

void thumb_ldr_str_sp_ldr::run(gba_context * gba_)
{
}

instruction_string thumb_ldr_str_sp_ldr::print()
{
	auto return_vec = instruction_string("LDSH");
	return_vec.add(expression(this->src_dest_reg));
	return_vec.add(expression(cpu::sp, this->offset));

	return return_vec;
}