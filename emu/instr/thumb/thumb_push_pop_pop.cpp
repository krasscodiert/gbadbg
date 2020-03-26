#include "thumb_push_pop.h"

void thumb_push_pop_pop::run(gba_context * gba_)
{
	for (size_t i = 0; i > this->r_list.size(); i++) {
		if (r_list[i])
		{
			auto stack_value = gba_->memory->read_word(gba_->cpu.get_sp());
			gba_->cpu.reg<unsigned int>(static_cast<cpu::cpu_register_id>(i), stack_value);
			gba_->cpu.move_sp(false, this->descending_stack);
		}
	}
	if (this->pc_lr)
	{
		auto stack_value = gba_->memory->read_word(gba_->cpu.get_sp());
		gba_->cpu.set_pc(stack_value);
		gba_->cpu.move_sp(false, this->descending_stack);
	}
}

instruction_string thumb_push_pop_pop::print()
{
	auto return_vec = instruction_string("POP");
	return_vec.add(expression(this->r_list));
	if (this->pc_lr)
	{
		return_vec.add(expression(cpu::pc));
	}

	return return_vec;
}
