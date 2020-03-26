#include "thumb_alu.h"
void thumb_alu_lsl::run(gba_context * gba_)
{
}

instruction_string thumb_alu_lsl::print()
{
	auto return_vec = instruction_string("LSL");
	return_vec.add(expression(this->dest_reg));
	return_vec.add(expression(this->src_reg));

	return return_vec;
}