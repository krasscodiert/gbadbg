#pragma once
#include "thumb_instruction.h"
#include "instruction_string.h"

enum class thumb_ldr_str_opcode_type
{
	t_str = 0,
	t_strb = 1,
	t_ldr = 2,
	t_ldrb = 3
};

class thumb_ldr_str_instruction : public thumb_instruction
{
public:
	cpu::cpu_register_id off_reg{};
	cpu::cpu_register_id base_reg{};
	cpu::cpu_register_id src_dest_reg{};
private:
public:
	thumb_ldr_str_instruction(const cpu::cpu_register_id off_reg_, const cpu::cpu_register_id base_reg_, const cpu::cpu_register_id src_dest_reg_) {
		this->off_reg = off_reg_;
		this->base_reg = base_reg_;
		this->src_dest_reg = src_dest_reg_;
	}

	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_ldr_str_str : public thumb_ldr_str_instruction
{
public:
private:
public:
	thumb_ldr_str_str(thumb_ldr_str_instruction* base_) : thumb_ldr_str_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_ldr_str_strb : public thumb_ldr_str_instruction
{
public:
private:
public:
	thumb_ldr_str_strb(thumb_ldr_str_instruction* base_) : thumb_ldr_str_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_ldr_str_ldr : public thumb_ldr_str_instruction
{
public:
private:
public:
	thumb_ldr_str_ldr(thumb_ldr_str_instruction* base_) : thumb_ldr_str_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_ldr_str_ldrb : public thumb_ldr_str_instruction
{
public:
private:
public:
	thumb_ldr_str_ldrb(thumb_ldr_str_instruction* base_) : thumb_ldr_str_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};