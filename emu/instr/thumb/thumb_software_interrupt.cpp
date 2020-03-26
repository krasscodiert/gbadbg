#include "thumb_software_interrupt.h"

void thumb_software_interrupt::run(gba_context * gba_)
{
}

instruction_string thumb_software_interrupt::print()
{
	auto return_vec = instruction_string("SWI");
	return_vec.add(expression(this->comment));

	return return_vec;
}
