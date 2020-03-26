#pragma once
#include "thumb_instruction.h"
#include "instruction_string.h"

enum class thumb_conditional_branch_opcode_type
{
	t_beq = 0,
	t_bne = 1,
	t_bcs = 2,
	t_bhs = t_bcs,
	t_bcc = 3,
	t_blo = t_bcc,
	t_bmi = 4,
	t_bpl = 5,
	t_bvs = 6,
	t_bvc = 7,
	t_bhi = 8,
	t_bls = 9,
	t_bge = 10,
	t_blt = 11,
	t_bgt = 12,
	t_ble = 13,

	swi = 15 // swi doesn't belong to conditional branch but the address and opcode are the same
};

class thumb_conditional_branch_instruction : public thumb_instruction
{
public:
	bool is_condition_true;
	int offset{};
private:
public:
	thumb_conditional_branch_instruction(const int offset_) {
		this->offset = offset_;
	}

	int calculate_target_address() const;

	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_conditional_branch_beq : public thumb_conditional_branch_instruction
{
public:
	thumb_conditional_branch_beq(thumb_conditional_branch_instruction* base_) : thumb_conditional_branch_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_conditional_branch_bne : public thumb_conditional_branch_instruction
{
public:
	thumb_conditional_branch_bne(thumb_conditional_branch_instruction* base_) : thumb_conditional_branch_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_conditional_branch_bcs : public thumb_conditional_branch_instruction
{
public:
	thumb_conditional_branch_bcs(thumb_conditional_branch_instruction* base_) : thumb_conditional_branch_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_conditional_branch_bcc : public thumb_conditional_branch_instruction
{
public:
	thumb_conditional_branch_bcc(thumb_conditional_branch_instruction* base_) : thumb_conditional_branch_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_conditional_branch_bmi : public thumb_conditional_branch_instruction
{
public:
	thumb_conditional_branch_bmi(thumb_conditional_branch_instruction* base_) : thumb_conditional_branch_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_conditional_branch_bpl : public thumb_conditional_branch_instruction
{
public:
	thumb_conditional_branch_bpl(thumb_conditional_branch_instruction* base_) : thumb_conditional_branch_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_conditional_branch_bvs : public thumb_conditional_branch_instruction
{
public:
	thumb_conditional_branch_bvs(thumb_conditional_branch_instruction* base_) : thumb_conditional_branch_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_conditional_branch_bvc : public thumb_conditional_branch_instruction
{
public:
	thumb_conditional_branch_bvc(thumb_conditional_branch_instruction* base_) : thumb_conditional_branch_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_conditional_branch_bhi : public thumb_conditional_branch_instruction
{
public:
	thumb_conditional_branch_bhi(thumb_conditional_branch_instruction* base_) : thumb_conditional_branch_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_conditional_branch_bls : public thumb_conditional_branch_instruction
{
public:
	thumb_conditional_branch_bls(thumb_conditional_branch_instruction* base_) : thumb_conditional_branch_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_conditional_branch_bge : public thumb_conditional_branch_instruction
{
public:
	thumb_conditional_branch_bge(thumb_conditional_branch_instruction* base_) : thumb_conditional_branch_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_conditional_branch_blt : public thumb_conditional_branch_instruction
{
public:
	thumb_conditional_branch_blt(thumb_conditional_branch_instruction* base_) : thumb_conditional_branch_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_conditional_branch_bgt : public thumb_conditional_branch_instruction
{
public:
	thumb_conditional_branch_bgt(thumb_conditional_branch_instruction* base_) : thumb_conditional_branch_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_conditional_branch_ble : public thumb_conditional_branch_instruction
{
public:
	thumb_conditional_branch_ble(thumb_conditional_branch_instruction* base_) : thumb_conditional_branch_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};
