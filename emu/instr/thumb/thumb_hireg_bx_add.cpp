#include "thumb_hireg_bx.h"

void thumb_hireg_bx_add::run(gba_context * gba_)
{
}

instruction_string thumb_hireg_bx_add::print()
{
	auto return_vec = instruction_string("ADD");
	return_vec.add(expression(this->dest_reg));
	return_vec.add(expression(this->src_reg));

	return return_vec;
}