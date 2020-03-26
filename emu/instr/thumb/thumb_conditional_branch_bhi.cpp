#include "thumb_conditional_branch.h"

void thumb_conditional_branch_bhi::run(gba_context * gba_)
{
	this->is_condition_true = !gba_->cpu.reg_status[status_flag::z] &&
							   gba_->cpu.reg_status[status_flag::c];
	thumb_conditional_branch_instruction::run(gba_);
}

instruction_string thumb_conditional_branch_bhi::print()
{
	auto return_vec = instruction_string("BHI");
	return_vec.add(expression(this->offset));

	return return_vec;
}