#pragma once
#include "arm_instruction.h"

class arm_coprocessor_register_transfer_instruction : public arm_instruction
{
public:
	int operation_code;
	cpu::cpu_register_id cp_source_reg;
	cpu::cpu_register_id arm_source_reg;
	int coprocessor_number;
	int coprocessor_info;
	cpu::cpu_register_id cp_operand_reg;
private:
public:
	arm_coprocessor_register_transfer_instruction(int operation_code_, cpu::cpu_register_id cp_source_reg_, cpu::cpu_register_id arm_source_reg_, int coprocessor_number_, int coprocessor_info_, cpu::cpu_register_id cp_operand_reg_, condition_flag flag_)
	{
		this->cond_flag = flag_;
		this->operation_code = operation_code_;
		this->cp_source_reg = cp_source_reg_;
		this->arm_source_reg = arm_source_reg_;
		this->coprocessor_number = coprocessor_number_;
		this->coprocessor_info = coprocessor_info_;
		this->cp_operand_reg = cp_operand_reg_;
	}

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_mcr : public arm_coprocessor_register_transfer_instruction
{
public:
private:
public:
	arm_mcr(arm_coprocessor_register_transfer_instruction *base) : arm_coprocessor_register_transfer_instruction(*base) {};

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_mrc : public arm_coprocessor_register_transfer_instruction
{
public:
private:
public:
	arm_mrc(arm_coprocessor_register_transfer_instruction *base) : arm_coprocessor_register_transfer_instruction(*base) {};

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_coprocessor_data_transfer_instruction : public arm_instruction
{
public:
	bool pre_indexing;
	bool add_to_base;
	bool transfer_length;
	bool address_into_base;
	cpu::cpu_register_id arm_base_reg;
	cpu::cpu_register_id cp_source_reg;
	int coprocessor_number;
	unsigned int immediate;
private:
public:
	arm_coprocessor_data_transfer_instruction(bool pre_indexing_ , bool add_to_base_, bool transfer_length_, bool address_into_base_, cpu::cpu_register_id arm_base_reg_, cpu::cpu_register_id cp_source_reg_, int coprocessor_number_, unsigned int immediate_, condition_flag flag_)
	{
		this->cond_flag = flag_;
		this->pre_indexing = pre_indexing_;
		this->add_to_base = add_to_base_;
		this->transfer_length = transfer_length_;
		this->address_into_base = address_into_base_;
		this->arm_base_reg = arm_base_reg_;
		this->cp_source_reg = cp_source_reg_;
		this->coprocessor_number = coprocessor_number_;
		this->immediate = immediate_;
	}

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_stc : public arm_coprocessor_data_transfer_instruction
{
public:
private:
public:
	arm_stc(arm_coprocessor_data_transfer_instruction *base) : arm_coprocessor_data_transfer_instruction(*base) {};

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_ldc : public arm_coprocessor_data_transfer_instruction
{
public:
private:
public:
	arm_ldc(arm_coprocessor_data_transfer_instruction *base) : arm_coprocessor_data_transfer_instruction(*base) {};

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};

class arm_cdp : public arm_instruction
{
public:
	int cp_opcode;
	cpu::cpu_register_id first_cp_operand_reg;
	cpu::cpu_register_id cp_dest_reg;
	int coprocessor_number;
	int coprocessor_info;
	cpu::cpu_register_id second_cp_operand_reg;
private:
public:
	arm_cdp(int cp_opcode_, cpu::cpu_register_id first_cp_operand_reg_, cpu::cpu_register_id cp_dest_reg_, int coprocessor_number_, int coprocessor_info_, cpu::cpu_register_id second_cp_operand_reg_, condition_flag flag_)
	{
		this->cond_flag = flag_;
		this->cp_opcode = cp_opcode_;
		this->first_cp_operand_reg = first_cp_operand_reg_;
		this->cp_dest_reg = cp_dest_reg_;
		this->coprocessor_number = coprocessor_number_;
		this->coprocessor_info = coprocessor_info_;
		this->second_cp_operand_reg = second_cp_operand_reg_;
	}

	void run(gba_context* gba) override;
	instruction_string print() override;
private:
};