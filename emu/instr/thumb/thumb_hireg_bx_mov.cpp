#include "thumb_hireg_bx.h"

void thumb_hireg_bx_mov::run(gba_context * gba_)
{
}

instruction_string thumb_hireg_bx_mov::print()
{
	if (this->dest_reg == this->src_reg)
	{
		auto return_vec = instruction_string("NOP");

		return return_vec;
	}

	auto return_vec = instruction_string("MOV");
	return_vec.add(expression(this->dest_reg));
	return_vec.add(expression(this->src_reg));

	return return_vec;
}