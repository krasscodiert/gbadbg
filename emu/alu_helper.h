#pragma once
#include "instruction_return.h"

static class alu_helper
{
public:
	alu_helper();
	~alu_helper();
	static instruction_return alu_and(unsigned int left, unsigned int right);
	static instruction_return alu_eor(unsigned int left, unsigned int right);
	static instruction_return alu_lsl(unsigned int left, unsigned int right);
	static instruction_return alu_lsr(unsigned int left, unsigned int right);
	static instruction_return alu_asr(unsigned int left, unsigned int right);
	static instruction_return alu_adc(unsigned int left, unsigned int right, bool carry);
	static instruction_return alu_sbc(unsigned int left, unsigned int right, bool carry);
	static instruction_return alu_ror(unsigned int left, unsigned int right);
	static instruction_return alu_neg(unsigned int left);
	static instruction_return alu_cmp(unsigned int left, unsigned int right);
	static instruction_return alu_cmn(unsigned int left, unsigned int right);
	static instruction_return alu_orr(unsigned int left, unsigned int right);
	static instruction_return alu_mul(unsigned int left, unsigned int right);
	static instruction_return alu_bic(unsigned int left, unsigned int right);
	static instruction_return alu_mvn(unsigned int left);
private:

};
