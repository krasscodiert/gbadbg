#pragma once
#include <string>
#include <vector>
#include "cpu.h"
#include "arm_globals.h"

class expression
{
public:

private:
	enum expression_type
	{
		value,
		reg,
		r_list,
		inline_shift,
		memory_accessor
	} type_;

	int value_ = -1;
	cpu::cpu_register_id s1_{};
	cpu::cpu_register_id s2_{};
	std::vector<bool> rList_{};
	arm_globals::arm_shift_type shift_type_{};

public:
	expression(int value)
	{
		this->type_ = expression_type::value;
		value_ = value;
	}

	expression(cpu::cpu_register_id reg)
	{
		this->type_ = expression_type::reg;
		s1_ = reg;
	}

	expression(std::vector<bool> rList)
	{
		this->type_ = r_list;
		rList_ = rList;
	}

	expression(cpu::cpu_register_id s1, cpu::cpu_register_id s2)
	{
		this->type_ = memory_accessor;
		s1_ = s1; 
		s2_ = s2;
	}

	expression(cpu::cpu_register_id s1, int value)
	{
		this->type_ = memory_accessor;
		s1_ = s1;
		value_ = value;
	}

	expression(arm_globals::arm_shift_type shift_type, int value)
	{
		this->type_ = inline_shift;
		shift_type_ = shift_type;
		value_ = value;
	}

	expression(arm_globals::arm_shift_type shift_type, cpu::cpu_register_id reg)
	{
		this->type_ = inline_shift;
		shift_type_ = shift_type;
		s1_ = reg;
	}

	std::string to_string();
	bool is_valide();
private:
};

class instruction_string
{
private:
	std::string instruction_type_;
	std::vector<expression> expressions_;
public:
private:
public:
	instruction_string(std::string instruction_type) {
		this->instruction_type_ = instruction_type;
	}

	instruction_string(std::string instruction_type, std::vector<expression> expressions_) {
		this->instruction_type_ = instruction_type;
		this->expressions_ = expressions_;
	}

	std::string to_string();
	void add(expression ex);
	void insert(instruction_string s, int index);
};
