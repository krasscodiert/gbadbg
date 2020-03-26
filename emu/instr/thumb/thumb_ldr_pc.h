#pragma once
#include "instruction.h"
#include "util.h"
#include "arm_util.h"
#include "instruction_string.h"

enum class thumb_ldr_pc_opcode_type
{
	t_ldr = 0 // opcode fixed
};

class thumb_ldr_pc_ldr : public instruction
{
public:
	cpu::cpu_register_id dest_reg{};
	unsigned int offset{};
private:
public:
	thumb_ldr_pc_ldr(const cpu::cpu_register_id dest_reg_, const unsigned int offset_) {
		this->offset = offset_;
		this->dest_reg = dest_reg_;
	}

	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};