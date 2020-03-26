#pragma once
#include "instruction.h"

class thumb_instruction : public instruction
{
public:
	thumb_instruction()
	{
		this->is_arm = false;
		this->descending_stack = true;
	}
};
