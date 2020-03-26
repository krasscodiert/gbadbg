#pragma once
#include "arm_instruction.h"

class arm_swp : public arm_instruction
{
public:
	bool swap_byte;
	cpu::cpu_register_id base_reg;
	cpu::cpu_register_id dest_reg;
	cpu::cpu_register_id source_reg;
private:
public:
	arm_swp(bool swap_byte_, cpu::cpu_register_id base_reg_, cpu::cpu_register_id dest_reg_, cpu::cpu_register_id source_reg, condition_flag flag_)
	{
		this->cond_flag = flag_;
		this->swap_byte = swap_byte_;
		this->base_reg = base_reg_;
		this->dest_reg = dest_reg_;
		this->source_reg = source_reg;
	}

	void run(gba_context* gba) override;
	instruction_string print() override;
public:
};
