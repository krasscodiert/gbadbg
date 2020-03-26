#pragma once
#include "arm_memory_transfer.h"

enum class arm_half_double_signed_transfer_store_opcode_type
{
	a_str_h = 1,
	a_ldr_d,
	a_str_d
};

enum class arm_half_double_signed_transfer_load_opcode_type
{
	a_ldr_h = 1,
	a_ldr_sb,
	a_ldr_sh
};

class arm_half_double_signed_transfer_instruction : public arm_memory_transfer_instruction
{
public:
	int immediate{};
	cpu::cpu_register_id reg_offset{};
private:
	enum instruction_type
	{
		register_offset,
		immediate_offset
	}type_;
public:
	arm_half_double_signed_transfer_instruction(bool is_pre_indexing_, bool add_to_base_, bool param_, bool load_from_memory_, cpu::cpu_register_id reg_base_, cpu::cpu_register_id reg_dest_, int immediate_, condition_flag flag_) : arm_memory_transfer_instruction(is_pre_indexing_, add_to_base_, param_, reg_base_, reg_dest_, flag_)
	{
		this->immediate = immediate_;
		this->type_ = immediate_offset;
	}

	arm_half_double_signed_transfer_instruction(bool is_pre_indexing_, bool add_to_base_, bool param_, bool load_from_memory_, cpu::cpu_register_id reg_base_, cpu::cpu_register_id reg_dest_, cpu::cpu_register_id reg_offset_, condition_flag flag_) : arm_memory_transfer_instruction(is_pre_indexing_, add_to_base_, param_, reg_base_, reg_dest_, flag_)
	{
		this->reg_offset = reg_offset_;
		this->type_ = register_offset;
	}

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_str_h : public arm_half_double_signed_transfer_instruction
{
public:
private:
public:
	arm_str_h(arm_half_double_signed_transfer_instruction *base) : arm_half_double_signed_transfer_instruction(*base) {};

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_ldr_d : public arm_half_double_signed_transfer_instruction
{
public:
private:
public:
	arm_ldr_d(arm_half_double_signed_transfer_instruction *base) : arm_half_double_signed_transfer_instruction(*base) {};

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_str_d : public arm_half_double_signed_transfer_instruction
{
public:
private:
public:
	arm_str_d(arm_half_double_signed_transfer_instruction *base) : arm_half_double_signed_transfer_instruction(*base) {};

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_ldr_h : public arm_half_double_signed_transfer_instruction
{
public:
private:
public:
	arm_ldr_h(arm_half_double_signed_transfer_instruction *base) : arm_half_double_signed_transfer_instruction(*base) {};

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_ldr_sb : public arm_half_double_signed_transfer_instruction
{
public:
private:
public:
	arm_ldr_sb(arm_half_double_signed_transfer_instruction *base) : arm_half_double_signed_transfer_instruction(*base) {};

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_ldr_sh : public arm_half_double_signed_transfer_instruction
{
public:
private:
public:
	arm_ldr_sh(arm_half_double_signed_transfer_instruction *base) : arm_half_double_signed_transfer_instruction(*base) {};

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};