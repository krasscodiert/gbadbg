#pragma once
#include "arm_instruction.h"

enum class arm_mul_opcode_type
{
	mul,
	mla,
	umull = 0b0100,
	umlal,
	smull,
	smlal,
	smla,
	smlaw,
	smulw = smlaw,
	smlal_xy,
	smul
};

class arm_multiply_instruction : public arm_instruction
{
public:
	cpu::cpu_register_id reg_dest{};
	cpu::cpu_register_id reg_acc{};	
	cpu::cpu_register_id reg_op_s{};
	cpu::cpu_register_id reg_op_m{};
	bool set_condition_flags{};
	bool use_reg_s_upper{};
	bool use_reg_m_upper{};
private:
	enum instruction_type
	{
		word,
		halfword,
	}type_;
public:
	arm_multiply_instruction(cpu::cpu_register_id reg_dest_, cpu::cpu_register_id reg_acc_, cpu::cpu_register_id reg_op_s_, cpu::cpu_register_id reg_op_m_, bool set_condition_flags_, condition_flag flag_)
	{
		this->cond_flag = flag_;
		this->reg_dest = reg_dest_;
		this->reg_acc = reg_acc_;
		this->reg_op_s = reg_op_s_;
		this->reg_op_m = reg_op_m_;
		this->set_condition_flags = set_condition_flags_;
		this->type_ = word;
	}

	arm_multiply_instruction(cpu::cpu_register_id reg_dest_, cpu::cpu_register_id reg_acc_, cpu::cpu_register_id reg_op_s_, cpu::cpu_register_id reg_op_m_, bool use_reg_s_upper_, bool use_reg_m_upper_, bool set_condition_flags_, condition_flag flag_)
	{
		this->cond_flag = flag_;
		this->reg_dest = reg_dest_;
		this->reg_acc = reg_acc_;
		this->reg_op_s = reg_op_s_;
		this->reg_op_m = reg_op_m_;
		this->use_reg_s_upper = use_reg_s_upper_;
		this->use_reg_m_upper = use_reg_m_upper_;
		this->set_condition_flags = set_condition_flags_;
		this->type_ = halfword;
	}

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_mul : public arm_multiply_instruction
{
public:
private:
public:
	arm_mul(arm_multiply_instruction * base) : arm_multiply_instruction(*base) {};
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_mla : public arm_multiply_instruction
{
public:
private:
public:
	arm_mla(arm_multiply_instruction * base) : arm_multiply_instruction(*base) {};
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_umull : public arm_multiply_instruction
{
public:
private:
public:
	arm_umull(arm_multiply_instruction * base) : arm_multiply_instruction(*base) {};
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_umlal : public arm_multiply_instruction
{
public:
private:
public:
	arm_umlal(arm_multiply_instruction * base) : arm_multiply_instruction(*base) {};
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_smull : public arm_multiply_instruction
{
public:
private:
public:
	arm_smull(arm_multiply_instruction * base) : arm_multiply_instruction(*base) {};
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_smlal : public arm_multiply_instruction
{
public:
private:
public:
	arm_smlal(arm_multiply_instruction * base) : arm_multiply_instruction(*base) {};
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_smla : public arm_multiply_instruction
{
public:
private:
public:
	arm_smla(arm_multiply_instruction * base) : arm_multiply_instruction(*base) {};
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_smlaw : public arm_multiply_instruction
{
public:
private:
public:
	arm_smlaw(arm_multiply_instruction * base) : arm_multiply_instruction(*base) {};
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_smulw : public arm_multiply_instruction
{
public:
private:
public:
	arm_smulw(arm_multiply_instruction * base) : arm_multiply_instruction(*base) {};
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_smlal_xy : public arm_multiply_instruction
{
public:
private:
public:
	arm_smlal_xy(arm_multiply_instruction * base) : arm_multiply_instruction(*base) {};
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_smul : public arm_multiply_instruction
{
public:
private:
public:
	arm_smul(arm_multiply_instruction * base) : arm_multiply_instruction(*base) {};
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};