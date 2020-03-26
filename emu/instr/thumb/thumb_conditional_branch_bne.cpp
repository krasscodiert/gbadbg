#include "thumb_conditional_branch.h"

void thumb_conditional_branch_bne::run(gba_context * gba_)
{
	this->is_condition_true = !gba_->cpu.reg_status[status_flag::z];
	thumb_conditional_branch_instruction::run(gba_);
}

instruction_string thumb_conditional_branch_bne::print()
{
	auto return_vec = instruction_string("BNE");
	return_vec.add(expression(this->offset));

	return return_vec;
}