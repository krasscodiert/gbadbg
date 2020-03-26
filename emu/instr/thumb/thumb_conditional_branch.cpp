#include "thumb_conditional_branch.h"

int thumb_conditional_branch_instruction::calculate_target_address() const
{
	return this->offset * 2 + 4;
}

void thumb_conditional_branch_instruction::run(gba_context * gba_)
{
	if (this->is_condition_true)
	{
		auto new_offset = this->calculate_target_address();
		gba_->cpu.set_pc(gba_->get_next_instruction_offset_(new_offset));
	}
}

instruction_string thumb_conditional_branch_instruction::print()
{
	return instruction_string(nullptr);
}
