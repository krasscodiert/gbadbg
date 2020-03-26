#include "thumb_alu.h"
void thumb_alu_ror::run(gba_context * gba_)
{
}

instruction_string thumb_alu_ror::print()
{
	auto return_vec = instruction_string("ROR");
	return_vec.add(expression(this->dest_reg));
	return_vec.add(expression(this->src_reg));

	return return_vec;
}