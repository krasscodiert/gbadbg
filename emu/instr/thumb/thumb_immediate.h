#pragma once
#include "thumb_instruction.h"
#include "instruction_string.h"

enum class thumb_immediate_opcode_type
{
	t_mov = 0,
	t_cmp = 1,
	t_add = 2,
	t_sub = 3
};

class thumb_immediate_instruction : public thumb_instruction
{
public:
	unsigned int unsigned_imm{};
	cpu::cpu_register_id dest_reg{};
private:
public:
	thumb_immediate_instruction(const int unsigned_imm_, const cpu::cpu_register_id dest_reg_)
	{
		this->unsigned_imm = unsigned_imm_;
		this->dest_reg = dest_reg_;
	}

	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_immediate_mov : public thumb_immediate_instruction
{
public:
	thumb_immediate_mov(thumb_immediate_instruction* base_) : thumb_immediate_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_immediate_cmp : public thumb_immediate_instruction
{
public:
	thumb_immediate_cmp(thumb_immediate_instruction* base_) : thumb_immediate_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_immediate_add : public thumb_immediate_instruction
{
public:
	thumb_immediate_add(thumb_immediate_instruction* base_) : thumb_immediate_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_immediate_sub : public thumb_immediate_instruction
{
public:
	thumb_immediate_sub(thumb_immediate_instruction* base_) : thumb_immediate_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};