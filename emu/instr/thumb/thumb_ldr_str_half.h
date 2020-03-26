#pragma once
#include "thumb_instruction.h"
#include "instruction_string.h"

enum class thumb_ldr_str_half_opcode_type
{
	t_strh = 0,
	t_ldrh = 1
};

class thumb_ldr_str_half_instruction : public thumb_instruction
{
public:
	unsigned int offset{};
	cpu::cpu_register_id base_reg{};
	cpu::cpu_register_id src_dest_reg{};
private:
public:
	thumb_ldr_str_half_instruction(const unsigned int offset_, const cpu::cpu_register_id base_reg_, const cpu::cpu_register_id src_dest_reg_) {
		this->offset = offset_;
		this->base_reg = base_reg_;
		this->src_dest_reg = src_dest_reg_;
	}

	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_ldr_str_half_strh : public thumb_ldr_str_half_instruction
{
public:
	thumb_ldr_str_half_strh(thumb_ldr_str_half_instruction* base_) : thumb_ldr_str_half_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_ldr_str_half_ldrh : public thumb_ldr_str_half_instruction
{
public:
	thumb_ldr_str_half_ldrh(thumb_ldr_str_half_instruction* base_) : thumb_ldr_str_half_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};
