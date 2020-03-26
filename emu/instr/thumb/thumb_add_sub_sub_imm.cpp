#include "thumb_add_sub.h"
void thumb_add_sub_sub_imm::run(gba_context * gba_)
{
}

instruction_string thumb_add_sub_sub_imm::print()
{
	auto return_vec = instruction_string("SUB");
	return_vec.add(expression(this->dest_reg));
	return_vec.add(expression(this->src_reg));
	return_vec.add(expression(this->imm_val));

	return return_vec;
}