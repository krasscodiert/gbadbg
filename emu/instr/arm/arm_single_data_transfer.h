#pragma once
#include "arm_memory_transfer.h"

class arm_single_data_transfer_instruction : public arm_memory_transfer_instruction
{
public:
	int immediate{};
	int shift_amount{};
	arm_globals::arm_shift_type shift_type{};
	cpu::cpu_register_id reg_offset{};
	int calculated_offset{};
	bool transfer_byte{};

	enum instruction_type
	{
		register_offset,
		immediate_offset,
	}type;
private:
public:
	arm_single_data_transfer_instruction(bool is_pre_indexing_, bool add_to_base_, bool transfer_byte_, bool param_, cpu::cpu_register_id reg_base_, cpu::cpu_register_id reg_dest_, int immediate_offset_, condition_flag flag_) : arm_memory_transfer_instruction(is_pre_indexing_, add_to_base_, param_, reg_base_, reg_dest_, flag_)
	{
		this->transfer_byte = transfer_byte_;
		this->immediate = immediate_offset_;
		this->type = immediate_offset;
	}

	arm_single_data_transfer_instruction(bool is_pre_indexing_, bool add_to_base_, bool transfer_byte_, bool param_, cpu::cpu_register_id reg_base_, cpu::cpu_register_id reg_dest_, int shift_amount_, arm_globals::arm_shift_type shift_type_, cpu::cpu_register_id reg_offset_, condition_flag flag_) : arm_memory_transfer_instruction(is_pre_indexing_, add_to_base_, param_, reg_base_, reg_dest_, flag_)
	{
		this->transfer_byte = transfer_byte_;
		this->shift_amount = shift_amount_;
		this->shift_type = shift_type_;
		this->reg_offset = reg_offset_;
		this->type = register_offset;
	}

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_str : public arm_single_data_transfer_instruction
{
public:
private:
public:
	arm_str(arm_single_data_transfer_instruction *base) : arm_single_data_transfer_instruction(*base) {};
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_ldr : public arm_single_data_transfer_instruction
{
public:
private:
public:
	arm_ldr(arm_single_data_transfer_instruction *base) : arm_single_data_transfer_instruction(*base) {};
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};