#pragma once
#include "thumb_instruction.h"
#include "instruction_string.h"

enum class thumb_alu_opcode_type {
	t_and = 0,
	t_eor = 1,
	t_lsl = 2,
	t_lsr = 3,
	t_asr = 4,
	t_adc = 5,
	t_sbc = 6,
	t_ror = 7,
	t_tst = 8,
	t_neg = 9,
	t_cmp = 10,
	t_cmn = 11,
	t_orr = 12,
	t_mul = 13,
	t_bic = 14,
	t_mvn = 15,
};

class thumb_alu_instruction : public thumb_instruction
{
public:
	cpu::cpu_register_id src_reg{};
	cpu::cpu_register_id dest_reg{};
private:
public:
	thumb_alu_instruction(const cpu::cpu_register_id src_reg_, const cpu::cpu_register_id dest_reg_) {
		this->src_reg = src_reg_;
		this->dest_reg = dest_reg_;
	}

	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_alu_and : public thumb_alu_instruction
{
public:
	thumb_alu_and(thumb_alu_instruction* base_) : thumb_alu_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_alu_eor : public thumb_alu_instruction
{
public:
	thumb_alu_eor(thumb_alu_instruction* base_) : thumb_alu_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_alu_lsl : public thumb_alu_instruction
{
public:
	thumb_alu_lsl(thumb_alu_instruction* base_) : thumb_alu_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_alu_lsr : public thumb_alu_instruction
{
public:
	thumb_alu_lsr(thumb_alu_instruction* base_) : thumb_alu_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_alu_asr : public thumb_alu_instruction
{
public:
	thumb_alu_asr(thumb_alu_instruction* base_) : thumb_alu_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_alu_adc : public thumb_alu_instruction
{
public:
	thumb_alu_adc(thumb_alu_instruction* base_) : thumb_alu_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_alu_sbc : public thumb_alu_instruction
{
public:
	thumb_alu_sbc(thumb_alu_instruction* base_) : thumb_alu_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_alu_ror : public thumb_alu_instruction
{
public:
	thumb_alu_ror(thumb_alu_instruction* base_) : thumb_alu_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_alu_tst : public thumb_alu_instruction
{
public:
	thumb_alu_tst(thumb_alu_instruction* base_) : thumb_alu_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_alu_neg : public thumb_alu_instruction
{
public:
	thumb_alu_neg(thumb_alu_instruction* base_) : thumb_alu_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_alu_cmp : public thumb_alu_instruction
{
public:
	thumb_alu_cmp(thumb_alu_instruction* base_) : thumb_alu_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_alu_cmn : public thumb_alu_instruction
{
public:
	thumb_alu_cmn(thumb_alu_instruction* base_) : thumb_alu_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_alu_orr : public thumb_alu_instruction
{
public:
	thumb_alu_orr(thumb_alu_instruction* base_) : thumb_alu_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_alu_mul : public thumb_alu_instruction
{
public:
	thumb_alu_mul(thumb_alu_instruction* base_) : thumb_alu_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_alu_bic : public thumb_alu_instruction
{
public:
	thumb_alu_bic(thumb_alu_instruction* base_) : thumb_alu_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_alu_mvn : public thumb_alu_instruction
{
public:
	thumb_alu_mvn(thumb_alu_instruction* base_) : thumb_alu_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};