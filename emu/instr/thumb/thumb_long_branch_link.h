#pragma once
#include "thumb_instruction.h"
#include "instruction_string.h"

class thumb_long_branch_link_bl : public thumb_instruction
{
public:
private:
	unsigned int address{};
public:
	thumb_long_branch_link_bl(unsigned int upper_address_) {
		this->address = (upper_address_ << 12) + 4;
	}

	int calculate_target_address() const;
	void set_lower_offset(unsigned int lower_address_);
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};
