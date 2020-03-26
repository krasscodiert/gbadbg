#pragma once
#include "thumb_instruction.h"
#include "instruction_string.h"

enum class thumb_shift_opcode_type
{
	t_lsl = 0,
	t_lsr = 1,
	t_asr = 2
};

class thumb_shift_instruction: public thumb_instruction
{
public:
	unsigned int offset{};
	cpu::cpu_register_id src_reg{};
	cpu::cpu_register_id dest_reg{};
private:
public:
	thumb_shift_instruction(const int offset_, const cpu::cpu_register_id src_reg_, const cpu::cpu_register_id dest_reg_)
	{
		this->offset = offset_;
		this->src_reg = src_reg_;
		this->dest_reg = dest_reg_;
	}

	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};


class thumb_shift_lsl : public thumb_shift_instruction
{
public:
	thumb_shift_lsl(thumb_shift_instruction* base_) : thumb_shift_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_shift_lsr : public thumb_shift_instruction
{
public:
	thumb_shift_lsr(thumb_shift_instruction* base_) : thumb_shift_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_shift_asr : public thumb_shift_instruction
{
public:
	thumb_shift_asr(thumb_shift_instruction* base_) : thumb_shift_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};