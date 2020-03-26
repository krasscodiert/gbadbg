#include "thumb_immediate.h"
void thumb_immediate_mov::run(gba_context * gba_)
{
}

instruction_string thumb_immediate_mov::print()
{
	auto return_vec = instruction_string("MOV");
	return_vec.add(expression(this->dest_reg));
	return_vec.add(expression(this->unsigned_imm));

	return return_vec;
}