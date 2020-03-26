#pragma once
#include "thumb_instruction.h"
#include "instruction_string.h"

class thumb_software_interrupt : public thumb_instruction
{
public:
	unsigned int comment{};
private:
public:
	thumb_software_interrupt(unsigned int comment_) {
		this->comment = comment_;
	}

	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};
