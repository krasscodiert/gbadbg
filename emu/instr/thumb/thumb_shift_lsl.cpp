#include "thumb_shift.h"
void thumb_shift_lsl::run(gba_context * gba_)
{
}

instruction_string thumb_shift_lsl::print()
{
	auto return_vec = instruction_string("LSL");
	return_vec.add(expression(this->dest_reg));
	return_vec.add(expression(this->src_reg));
	return_vec.add(expression(this->offset));

	return return_vec;
}