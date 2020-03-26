#include "thumb_push_pop.h"

void thumb_push_pop_push::run(gba_context * gba_)
{
	if (this->pc_lr)
	{
		gba_->cpu.move_sp(true, this->descending_stack);
		auto reg_entry = gba_->cpu.reg<unsigned int>(static_cast<cpu::cpu_register_id>(cpu::lr));
		gba_->memory->write_word(reg_entry, gba_->cpu.get_sp());
	}
	for (int i = this->r_list.size() - 1; i >= 0; i--) {
		if (r_list[i])
		{
			gba_->cpu.move_sp(true, this->descending_stack);
			auto reg_entry = gba_->cpu.reg<unsigned int>(static_cast<cpu::cpu_register_id>(i));
			gba_->memory->write_word(reg_entry, gba_->cpu.get_sp());
		}
	}
}

instruction_string thumb_push_pop_push::print()
{
	auto return_vec = instruction_string("PUSH");
	return_vec.add(expression(this->r_list));
	if (this->pc_lr)
	{
		return_vec.add(expression(cpu::lr));
	}

	return return_vec;
}
