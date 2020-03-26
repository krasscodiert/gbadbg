#pragma once
#include "arm_memory_transfer.h"
#include <memory>

class arm_block_data_transfer_instruction : public arm_memory_transfer_instruction
{
public:
	bool load_psr;
	bool registers[15]{};
private:
	void parse_register_list(int list);
public:
	arm_block_data_transfer_instruction(bool is_pre_indexing_, bool add_to_base_, bool load_psr_, bool param_, cpu::cpu_register_id reg_base_, int list_, condition_flag flag_) : arm_memory_transfer_instruction(is_pre_indexing_, add_to_base_, param_, reg_base_, cpu::cpu_register_id::r0, flag_)
	{
		this->load_psr = load_psr_;
		this->parse_register_list(list_);
	}

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_stm : public arm_block_data_transfer_instruction
{
public:
private:
public:
	arm_stm(arm_block_data_transfer_instruction *base) : arm_block_data_transfer_instruction(*base) {};

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_ldm : public arm_block_data_transfer_instruction
{
public:
private:
public:
	arm_ldm(arm_block_data_transfer_instruction *base) : arm_block_data_transfer_instruction(*base) {};

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};