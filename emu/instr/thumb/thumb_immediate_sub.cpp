#include "thumb_immediate.h"
void thumb_immediate_sub::run(gba_context * gba_)
{
}

instruction_string thumb_immediate_sub::print()
{
	auto return_vec = instruction_string("SUB");
	return_vec.add(expression(this->dest_reg));
	return_vec.add(expression(this->unsigned_imm));

	return return_vec;
}