#pragma once
#include "thumb_instruction.h"
#include "instruction_string.h"

enum class thumb_ldr_str_immediate_opcode_type
{
	t_str = 0,
	t_ldr = 1,
	t_strb = 2,
	t_ldrb = 3
};

class thumb_ldr_str_immediate_instruction : public thumb_instruction
{
public:
	unsigned int offset{};
	cpu::cpu_register_id base_reg{};
	cpu::cpu_register_id src_dest_reg{};
private:
public:
	thumb_ldr_str_immediate_instruction(const unsigned int offset_, const cpu::cpu_register_id base_reg_, const cpu::cpu_register_id src_dest_reg_) {
		this->offset = offset_;
		this->base_reg = base_reg_;
		this->src_dest_reg = src_dest_reg_;
	}

	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_ldr_str_immediate_str : public thumb_ldr_str_immediate_instruction
{
public:
	thumb_ldr_str_immediate_str(thumb_ldr_str_immediate_instruction* base_) : thumb_ldr_str_immediate_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_ldr_str_immediate_ldr : public thumb_ldr_str_immediate_instruction
{
public:
	thumb_ldr_str_immediate_ldr(thumb_ldr_str_immediate_instruction* base_) : thumb_ldr_str_immediate_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_ldr_str_immediate_strb : public thumb_ldr_str_immediate_instruction
{
public:
	thumb_ldr_str_immediate_strb(thumb_ldr_str_immediate_instruction* base_) : thumb_ldr_str_immediate_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_ldr_str_immediate_ldrb : public thumb_ldr_str_immediate_instruction
{
public:
	thumb_ldr_str_immediate_ldrb(thumb_ldr_str_immediate_instruction* base_) : thumb_ldr_str_immediate_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};