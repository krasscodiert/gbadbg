#pragma once
#include "arm_instruction.h"

enum class arm_alu_opcode_type
{
	a_and = 0,
	a_eor = 1,
	a_sub = 2,
	a_rsb = 3,
	a_add = 4,
	a_adc = 5,
	a_sbc = 6,
	a_rsc = 7,
	a_tst = 8,
	a_teq = 9,
	a_cmp = 10,
	a_cmn = 11,
	a_orr = 12,
	a_mov = 13,
	a_bic = 14,
	a_mvn = 15
};

class arm_alu_instruction : public arm_instruction
{

public:
	cpu::cpu_register_id reg_dest;
	cpu::cpu_register_id reg_src;
	cpu::cpu_register_id reg_shift{};
	cpu::cpu_register_id second_op{};
	unsigned int shift_amount{};
	unsigned int shift_by_immediate{};
	unsigned int shift_immediate{};
	arm_globals::arm_shift_type shift_type;
	bool set_condition_flags;

	enum instruction_type
	{
		immediate,
		register_reg_amount,
		register_imm_amount
	}type;
private:

public:
	arm_alu_instruction(cpu::cpu_register_id reg_dest_, cpu::cpu_register_id reg_src_, int shift_by_immediate_, int shift_immediate_, bool set_condition_flags_, condition_flag flag_)
	{
		this->cond_flag = flag_;
		this->reg_dest = reg_dest_;
		this->reg_src = reg_src_;
		this->shift_by_immediate = shift_by_immediate_;
		this->shift_immediate = shift_immediate_;
		this->shift_type = arm_globals::arm_shift_type::ror;
		this->set_condition_flags = set_condition_flags_;
		this->type = immediate;
	}

	arm_alu_instruction(cpu::cpu_register_id reg_dest_, cpu::cpu_register_id reg_src_, arm_globals::arm_shift_type shift_type_, cpu::cpu_register_id reg_shift_, cpu::cpu_register_id second_op_,bool set_condition_flags_, condition_flag flag_)
	{
		this->cond_flag = flag_;
		this->reg_dest = reg_dest_;
		this->reg_src = reg_src_;
		this->shift_type = shift_type_;
		this->reg_shift = reg_shift_;
		this->second_op = second_op_;
		this->set_condition_flags = set_condition_flags_;
		this->type = register_reg_amount;
	}

	arm_alu_instruction(cpu::cpu_register_id reg_dest_, cpu::cpu_register_id reg_src_, int shift_amount_, arm_globals::arm_shift_type shift_type_, cpu::cpu_register_id second_op_, bool set_condition_flags_, condition_flag flag_)
	{
		this->cond_flag = flag_;
		this->reg_dest = reg_dest_;
		this->reg_src = reg_src_;
		this->shift_amount = shift_amount_;
		this->shift_type = shift_type_;
		this->second_op = second_op_;
		this->set_condition_flags = set_condition_flags_;
		this->type = register_imm_amount;
	}

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_and : public arm_alu_instruction
{
public:
	arm_and(arm_alu_instruction* base) : arm_alu_instruction(*base) {};
private:
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_eor : public arm_alu_instruction
{
public:
	arm_eor(arm_alu_instruction* base) : arm_alu_instruction(*base) {};
private:
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_sub : public arm_alu_instruction
{
public:
	arm_sub(arm_alu_instruction* base) : arm_alu_instruction(*base) {};
private:
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_rsb : public arm_alu_instruction
{
public:
	arm_rsb(arm_alu_instruction* base) : arm_alu_instruction(*base) {};
private:
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_add : public arm_alu_instruction
{
public:
	arm_add(arm_alu_instruction* base) : arm_alu_instruction(*base) {};
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_adc : public arm_alu_instruction
{
public:
	arm_adc(arm_alu_instruction* base) : arm_alu_instruction(*base) {};
private:
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_sbc : public arm_alu_instruction
{
public:
	arm_sbc(arm_alu_instruction* base) : arm_alu_instruction(*base) {};
private:
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_rsc : public arm_alu_instruction
{
public:
	arm_rsc(arm_alu_instruction* base) : arm_alu_instruction(*base) {};
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_tst : public arm_alu_instruction
{
public:
	arm_tst(arm_alu_instruction* base) : arm_alu_instruction(*base) {};
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_teq : public arm_alu_instruction
{
public:
	arm_teq(arm_alu_instruction* base) : arm_alu_instruction(*base) {};
private:
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_cmp : public arm_alu_instruction
{
public:
	arm_cmp(arm_alu_instruction* base) : arm_alu_instruction(*base) {};
private:
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_cmn : public arm_alu_instruction
{
public:
	arm_cmn(arm_alu_instruction* base) : arm_alu_instruction(*base) {};
private:
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_orr : public arm_alu_instruction
{
public:
	arm_orr(arm_alu_instruction* base) : arm_alu_instruction(*base) {};
private:
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_mov : public arm_alu_instruction
{
public:
	arm_mov(arm_alu_instruction* base) : arm_alu_instruction(*base) {};
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_bic : public arm_alu_instruction
{
public:
	arm_bic(arm_alu_instruction* base) : arm_alu_instruction(*base) {};
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_mvn : public arm_alu_instruction
{
public:
	arm_mvn(arm_alu_instruction* base) : arm_alu_instruction(*base) {};
private:
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};