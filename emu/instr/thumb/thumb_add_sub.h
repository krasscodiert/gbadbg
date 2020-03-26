#pragma once
#include "thumb_instruction.h"
#include "instruction_string.h"

enum class thumb_add_sub_opcode_type
{
	t_add_reg = 0,
	t_sub_reg = 1,
	t_add_imm = 2,
	t_sub_imm = 3
};

class thumb_add_sub_instruction : public thumb_instruction
{
public:
	unsigned int imm_val{}; 
	cpu::cpu_register_id reg_op{};
	cpu::cpu_register_id src_reg{};
	cpu::cpu_register_id dest_reg{};
private:
	enum instruction_type
	{
		register_operant,
		immediate_operant
	} type_;

public:
	thumb_add_sub_instruction(const cpu::cpu_register_id reg_op_, const cpu::cpu_register_id src_reg_, const cpu::cpu_register_id dest_reg_) {
		type_ = register_operant;
		this->reg_op = reg_op_;
		this->src_reg = src_reg_;
		this->dest_reg = dest_reg_;
	}

	thumb_add_sub_instruction(int imm_val_, cpu::cpu_register_id src_reg_, cpu::cpu_register_id dest_reg_) {
		type_ = immediate_operant;
		this->imm_val = imm_val_;
		this->src_reg = src_reg_;
		this->dest_reg = dest_reg_;
	}

	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};


class thumb_add_sub_add_reg : public thumb_add_sub_instruction
{
public:
	thumb_add_sub_add_reg(thumb_add_sub_instruction* base_) : thumb_add_sub_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};


class thumb_add_sub_sub_reg : public thumb_add_sub_instruction
{
public:
	thumb_add_sub_sub_reg(thumb_add_sub_instruction* base_) : thumb_add_sub_instruction(*base_) {};
private:
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};


class thumb_add_sub_add_imm : public thumb_add_sub_instruction
{
public:
	thumb_add_sub_add_imm(thumb_add_sub_instruction* base_) : thumb_add_sub_instruction(*base_) {};
private:
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};


class thumb_add_sub_sub_imm : public thumb_add_sub_instruction
{
public:
	thumb_add_sub_sub_imm(thumb_add_sub_instruction* base_) : thumb_add_sub_instruction(*base_) {};
private:
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

