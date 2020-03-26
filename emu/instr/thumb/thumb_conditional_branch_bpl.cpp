#include "thumb_conditional_branch.h"

void thumb_conditional_branch_bpl::run(gba_context * gba_)
{
	this->is_condition_true = !gba_->cpu.reg_status[status_flag::n];
	thumb_conditional_branch_instruction::run(gba_);
}

instruction_string thumb_conditional_branch_bpl::print()
{
	auto return_vec = instruction_string("BPL");
	return_vec.add(expression(this->offset));

	return return_vec;
}