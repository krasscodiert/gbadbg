#pragma once
#include "thumb_instruction.h"
#include "instruction_string.h"

enum class thumb_add_offset_relative_opcode_type
{
	t_add_pc = 0,
	t_add_sp = 1
};

class thumb_add_offset_relative_instruction : public thumb_instruction
{
public:
	cpu::cpu_register_id dest_reg{};
	unsigned int offset{};
private:
public:
	thumb_add_offset_relative_instruction(const cpu::cpu_register_id dest_reg_, const unsigned int offset_) {
		this->dest_reg = dest_reg_;
		this->offset = offset_;
	}

	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_add_offset_relative_add_pc : public thumb_add_offset_relative_instruction
{
public:
	thumb_add_offset_relative_add_pc(thumb_add_offset_relative_instruction* base_) : thumb_add_offset_relative_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_add_offset_relative_add_sp : public thumb_add_offset_relative_instruction
{
public:
	thumb_add_offset_relative_add_sp(thumb_add_offset_relative_instruction* base_) : thumb_add_offset_relative_instruction(*base_) {};
private:
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};
