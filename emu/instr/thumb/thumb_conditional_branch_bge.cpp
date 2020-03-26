#include "thumb_conditional_branch.h"

void thumb_conditional_branch_bge::run(gba_context * gba_)
{
	auto n = gba_->cpu.reg_status[status_flag::n];
	auto v = gba_->cpu.reg_status[status_flag::v];

	this->is_condition_true = (n == v);
	thumb_conditional_branch_instruction::run(gba_);
}

instruction_string thumb_conditional_branch_bge::print()
{
	auto return_vec = instruction_string("BGE");
	return_vec.add(expression(this->offset));

	return return_vec;
}