#include "thumb_add_offset_relative.h"

void thumb_add_offset_relative_add_sp::run(gba_context * gba_)
{
}

instruction_string thumb_add_offset_relative_add_sp::print()
{
	auto return_vec = instruction_string("ADD");
	return_vec.add(expression(this->dest_reg));
	return_vec.add(expression(cpu::sp));
	return_vec.add(expression(this->offset));

	return return_vec;
}