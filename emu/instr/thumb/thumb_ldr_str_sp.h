#pragma once
#include "thumb_instruction.h"
#include "instruction_string.h"

enum class thumb_ldr_str_sp_opcode_type
{
	t_str = 0,
	t_ldr = 1
};

class thumb_ldr_str_sp_instruction : public thumb_instruction
{
public:
	cpu::cpu_register_id src_dest_reg{};
	unsigned int offset{};
private:
public:
	thumb_ldr_str_sp_instruction(const cpu::cpu_register_id src_dest_reg_, const unsigned int offset_) {
		this->src_dest_reg = src_dest_reg_;
		this->offset = offset_;
	}

	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_ldr_str_sp_str : public thumb_ldr_str_sp_instruction
{
public:
	thumb_ldr_str_sp_str(thumb_ldr_str_sp_instruction* base_) : thumb_ldr_str_sp_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_ldr_str_sp_ldr : public thumb_ldr_str_sp_instruction
{
public:
	thumb_ldr_str_sp_ldr(thumb_ldr_str_sp_instruction* base_) : thumb_ldr_str_sp_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};
