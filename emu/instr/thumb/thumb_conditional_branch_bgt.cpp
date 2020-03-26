#include "thumb_conditional_branch.h"

void thumb_conditional_branch_bgt::run(gba_context * gba_)
{
	auto n = !gba_->cpu.reg_status[status_flag::n];
	auto v = !gba_->cpu.reg_status[status_flag::v];
	auto z = !gba_->cpu.reg_status[status_flag::z];

	this->is_condition_true = (!z) &&
							  (n == v);
	thumb_conditional_branch_instruction::run(gba_);
}

instruction_string thumb_conditional_branch_bgt::print()
{
	auto return_vec = instruction_string("BGT");
	return_vec.add(expression(this->offset));

	return return_vec;
}