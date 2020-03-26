#pragma once
#include "thumb_instruction.h"
#include "instruction_string.h"

enum class thumb_multiple_ld_st_opcode_type
{
	t_stmia = 0,
	t_ldmia = 1
};

class thumb_multiple_ld_st_instruction : public thumb_instruction
{
public:
	std::vector<bool> r_list{};
	cpu::cpu_register_id offset_reg{};
private:
public:
	thumb_multiple_ld_st_instruction(const cpu::cpu_register_id src_dest_reg_, std::vector<bool> r_list_) {
		this->offset_reg = src_dest_reg_;
		this->r_list = r_list_;
	}

	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_multiple_ld_st_stmia : public thumb_multiple_ld_st_instruction
{
public:
	thumb_multiple_ld_st_stmia(thumb_multiple_ld_st_instruction* base_) : thumb_multiple_ld_st_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_multiple_ld_st_ldmia : public thumb_multiple_ld_st_instruction
{
public:
	thumb_multiple_ld_st_ldmia(thumb_multiple_ld_st_instruction* base_) : thumb_multiple_ld_st_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};
