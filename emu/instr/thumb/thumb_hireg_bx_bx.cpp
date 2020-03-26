#include "thumb_hireg_bx.h"

int thumb_hireg_bx_bx::calculate_target_address() const
{
	return this->address;
}

void thumb_hireg_bx_bx::run(gba_context * gba_)
{
	this->address = gba_->cpu.reg<unsigned int>(this->src_reg);
	if (this->src_reg == cpu::cpu_register_id::pc)
	{
		gba_->thumb_mode_ = false;
		auto old_pc = gba_->cpu.get_pc();
		auto new_pc = (old_pc + 4) & (~2);

		gba_->cpu.set_pc(new_pc);
	}
	else
	{
		auto new_offset = this->calculate_target_address();
		gba_->cpu.set_pc(gba_->get_next_instruction_offset_(new_offset));
	}
}

instruction_string thumb_hireg_bx_bx::print()
{
	auto return_vec = instruction_string("BX");
	return_vec.add(expression(this->src_reg));

	return return_vec;
}