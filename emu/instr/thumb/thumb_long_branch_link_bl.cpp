#include "thumb_long_branch_link.h"

int thumb_long_branch_link_bl::calculate_target_address() const
{
	return this->address;
}

void thumb_long_branch_link_bl::set_lower_offset(unsigned int lower_address_)
{
	auto lower = lower_address_ << 1;
	this->address += lower;
}

void thumb_long_branch_link_bl::run(gba_context * gba_)
{
	auto old_pc = gba_->cpu.get_pc();
	auto return_pc = (old_pc + 2);
	gba_->cpu.reg(cpu::cpu_register_id::lr, return_pc);

	auto target_address = this->calculate_target_address() + old_pc;
	gba_->cpu.set_pc(target_address);
}

instruction_string thumb_long_branch_link_bl::print()
{
	auto return_vec = instruction_string("BL");
	return_vec.add(expression(this->address));

	return return_vec;
}
