#include "thumb_immediate.h"
void thumb_immediate_cmp::run(gba_context * gba_)
{
}

instruction_string thumb_immediate_cmp::print()
{
	auto return_vec = instruction_string("CMP");
	return_vec.add(expression(this->dest_reg));
	return_vec.add(expression(this->unsigned_imm));

	return return_vec;
}