#pragma once
#include "arm_instruction.h"
#include "util.h"

class arm_memory_transfer_instruction : public arm_instruction
{
public:
	bool is_pre_indexing;
	bool add_to_base;
	bool address_into_base;
	bool force_non_privileged_access;
	bool load_from_memory{};
	cpu::cpu_register_id reg_base;
	cpu::cpu_register_id reg_dest;
private:
	enum instruction_type
	{
		post_indexing,
		pre_indexing
	}type_;
public:
	arm_memory_transfer_instruction(bool is_pre_indexing_, bool add_to_base_, bool param_, cpu::cpu_register_id reg_base_, cpu::cpu_register_id reg_dest_, condition_flag flag_)
	{
		this->cond_flag = flag_;
		this->is_pre_indexing = is_pre_indexing_;
		this->add_to_base = add_to_base_;
		this->reg_base = reg_base_;
		this->reg_dest = reg_dest_;

		if (is_pre_indexing_)
		{
			this->type_ = pre_indexing;
			this->address_into_base = param_;
		}	
		else
		{
			this->type_ = post_indexing;
			this->force_non_privileged_access = param_;
		}
	}

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};
