#pragma once
#include "thumb_instruction.h"
#include "instruction_string.h"

enum class thumb_add_offset_sp_opcode_type
{
	t_add_pos = 0,
	t_add_neg = 1
};

class thumb_add_offset_sp_instruction : public thumb_instruction
{
public:
	unsigned int offset{};
private:
public:
	thumb_add_offset_sp_instruction(const unsigned int offset_) {
		this->offset = offset_;
	}

	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_add_offset_sp_add_pos : public thumb_add_offset_sp_instruction
{
public:
	thumb_add_offset_sp_add_pos(thumb_add_offset_sp_instruction* base_) : thumb_add_offset_sp_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_add_offset_sp_add_neg : public thumb_add_offset_sp_instruction
{
public:
	thumb_add_offset_sp_add_neg(thumb_add_offset_sp_instruction* base_) : thumb_add_offset_sp_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};
