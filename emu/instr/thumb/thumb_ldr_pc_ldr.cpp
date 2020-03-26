#include "thumb_ldr_pc.h"

void thumb_ldr_pc_ldr::run(gba_context * gba_)
{
}

instruction_string thumb_ldr_pc_ldr::print()
{
	auto return_vec = instruction_string("LDR");
	return_vec.add(expression(this->dest_reg));
	return_vec.add(expression(cpu::pc, this->offset));

	return return_vec;
}