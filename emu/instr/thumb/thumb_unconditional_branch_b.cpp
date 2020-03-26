#include "thumb_unconditional_branch.h"

int thumb_unconditional_branch_b::calculate_target_address() const
{
	return this->offset * 2 + 4;
}

void thumb_unconditional_branch_b::run(gba_context * gba_)
{
	gba_->cpu.set_pc(gba_->get_next_instruction_offset_(gba_->cpu.get_pc() + this->calculate_target_address()));
}

instruction_string thumb_unconditional_branch_b::print()
{
	auto return_vec = instruction_string("B");
	return_vec.add(expression(this->offset));

	return return_vec;
}
