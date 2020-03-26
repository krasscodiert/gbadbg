#pragma once
#include "arm_instruction.h"

class arm_mrs : public arm_instruction
{
public:
	bool use_spsr;
	cpu::cpu_register_id reg_dest;
private:
public:
	arm_mrs(bool use_spsr_, cpu::cpu_register_id reg_dest_, condition_flag flag_)
	{
		this->cond_flag = flag_;
		this->use_spsr = use_spsr_;
		this->reg_dest = reg_dest_;
	}

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_msr : public arm_instruction
{
public:
	bool use_spsr;
	bool write_f;
	bool write_s;
	bool write_x;
	bool write_c;
	cpu::cpu_register_id reg_src{};
	int shift_amount{};
	unsigned char immediate{};
private:
	enum instruction_type
	{
		reg,
		imm
	}type_;
public:
	arm_msr(bool use_spsr_, bool write_f_, bool write_s_, bool write_x_, bool write_c_, cpu::cpu_register_id reg_src_, condition_flag flag_)
	{
		this->cond_flag = flag_;
		this->use_spsr = use_spsr_;
		this->write_f = write_f_;
		this->write_s = write_s_;
		this->write_x = write_x_;
		this->write_c = write_c_;
		this->reg_src = reg_src_;
		this->type_ = reg;
	}

	arm_msr(bool use_spsr_, bool write_f_, bool write_s_, bool write_x_, bool write_c_, int shift_amount_,unsigned char immediate_, condition_flag flag_)
	{
		this->cond_flag = flag_;
		this->use_spsr = use_spsr_;
		this->write_f = write_f_;
		this->write_s = write_s_;
		this->write_x = write_x_;
		this->write_c = write_c_;
		this->shift_amount = shift_amount_;
		this->immediate = immediate_;
		this->type_ = imm;
	}

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};