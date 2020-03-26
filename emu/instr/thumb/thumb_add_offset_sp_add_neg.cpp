#include "thumb_add_offset_sp.h"

void thumb_add_offset_sp_add_neg::run(gba_context * gba_)
{
}

instruction_string thumb_add_offset_sp_add_neg::print()
{
	auto return_vec = instruction_string("ADD");
	return_vec.add(expression(cpu::sp));
	return_vec.add(expression(this->offset * -1));

	return return_vec;
}