#include "thumb_shift.h"
void thumb_shift_lsr::run(gba_context * gba_)
{
}

instruction_string thumb_shift_lsr::print()
{
	auto return_vec = instruction_string("LSR");
	return_vec.add(expression(this->dest_reg));
	return_vec.add(expression(this->src_reg));
	return_vec.add(expression(this->offset));

	return return_vec;
}