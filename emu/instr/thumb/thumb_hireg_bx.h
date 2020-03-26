#pragma once
#include "thumb_instruction.h"
#include "instruction_string.h"

enum class thumb_hireg_bx_opcode_type
{
	t_add = 0,
	t_cmp = 1,
	t_mov = 2,
	t_bx = 3,
};

class thumb_hireg_bx_instruction : public thumb_instruction
{
public:
	bool msbd{};
	bool msbs{};
	cpu::cpu_register_id src_reg{};
	cpu::cpu_register_id dest_reg{};
private:
public:
	thumb_hireg_bx_instruction(const bool msbd_, const bool msbs_, const cpu::cpu_register_id src_reg_, const cpu::cpu_register_id dest_reg_) {
		this->msbd = msbd_;
		this->msbs = msbs_;
		this->src_reg = src_reg_;
		this->dest_reg = dest_reg_;
	}

	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_hireg_bx_add : public thumb_hireg_bx_instruction
{
public:
	thumb_hireg_bx_add(thumb_hireg_bx_instruction* base_) : thumb_hireg_bx_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_hireg_bx_cmp : public thumb_hireg_bx_instruction
{
public:
	thumb_hireg_bx_cmp(thumb_hireg_bx_instruction* base_) : thumb_hireg_bx_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_hireg_bx_mov : public thumb_hireg_bx_instruction
{
public:
	thumb_hireg_bx_mov(thumb_hireg_bx_instruction* base_) : thumb_hireg_bx_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_hireg_bx_bx : public thumb_hireg_bx_instruction
{
public:
	thumb_hireg_bx_bx(thumb_hireg_bx_instruction* base_) : thumb_hireg_bx_instruction(*base_) {};

private:
	unsigned int address{};
public:
	void run(gba_context* gba) override;
	instruction_string print() override;
	int calculate_target_address() const;
private:
};