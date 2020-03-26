#pragma once
#include "instruction.h"

class arm_instruction : public instruction
{
public:
	enum condition_flag
	{
		eq,
		ne,
		cs,
		cc,
		mi,
		pl,
		vs,
		vc,
		hi,
		ls,
		ge,
		lt,
		gt,
		le,
		al,
		nv
	}cond_flag;
private:
public:
	arm_instruction()
	{
		this->is_arm = true;
		this->cond_flag = al;
	}

	arm_instruction(condition_flag flag)
	{
		this->is_arm = true;
		this->cond_flag = flag;
	}
private:
};