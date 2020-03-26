#pragma once
#include "arm_instruction.h"

class arm_branch_imm_instruction : public arm_instruction
{
public:
	int offset;
private:
public:
	arm_branch_imm_instruction(int offset_, condition_flag flag_)
	{
		this->offset = offset_;
		this->cond_flag = flag_;
	}

	int calculate_target_address() const;

	void run(gba_context* gba) override;
	instruction_string print() override;
};

class arm_branch_reg_instruction : public arm_instruction
{
public:
	cpu::cpu_register_id reg;
private:
public:
	arm_branch_reg_instruction(cpu::cpu_register_id reg_, condition_flag flag_)
	{
		this->reg = reg_;
		this->cond_flag = flag_;
	}

	int calculate_target_address(unsigned int address) const;

	void run(gba_context* gba) override;
	instruction_string print() override;
};

class arm_b : public arm_branch_imm_instruction
{
public:
	arm_b(int offset, condition_flag flag) : arm_branch_imm_instruction(offset, flag) {};
	void run(gba_context* gba) override;
	instruction_string print() override;
};

class arm_bl : public arm_branch_imm_instruction
{
public:
	arm_bl(int offset, condition_flag flag) : arm_branch_imm_instruction(offset, flag) {};
	void run(gba_context* gba) override;
	instruction_string print() override;
};

class arm_bx : public arm_branch_reg_instruction
{
public:
	arm_bx(cpu::cpu_register_id reg_num, condition_flag flag) : arm_branch_reg_instruction(reg_num, flag) {};
	void run(gba_context* gba) override;
	instruction_string print() override;
};

class arm_blx : public arm_branch_reg_instruction

{
public:
	arm_blx(cpu::cpu_register_id reg_num, condition_flag flag) : arm_branch_reg_instruction(reg_num, flag) {};
	void run(gba_context* gba) override;
	instruction_string print() override;
};

class arm_swi : public arm_instruction
{
public:
	unsigned int comment;
private:
public:
	arm_swi(unsigned int comment_, condition_flag flag_)
	{
		this->comment = comment_;
		this->cond_flag = flag_;
	};
	void run(gba_context* gba) override;
	instruction_string print() override;
};