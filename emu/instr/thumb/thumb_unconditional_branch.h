#pragma once
#include "thumb_instruction.h"
#include "instruction_string.h"

class thumb_unconditional_branch_b : public thumb_instruction
{
public:
	unsigned int offset{};
private:
public:
	thumb_unconditional_branch_b(unsigned int offset_) {
		this->offset = offset_;
	}

	int calculate_target_address() const;
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};