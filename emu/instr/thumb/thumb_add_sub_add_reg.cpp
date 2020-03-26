#include "thumb_add_sub.h"
void thumb_add_sub_add_reg::run(gba_context * gba_)
{
}

instruction_string thumb_add_sub_add_reg::print()
{
	auto return_vec = instruction_string("ADD");
	return_vec.add(expression(this->dest_reg));
	return_vec.add(expression(this->src_reg));
	return_vec.add(expression(this->reg_op));

	return return_vec;
}