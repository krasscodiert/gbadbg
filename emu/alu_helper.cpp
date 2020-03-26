#include "alu_helper.h"

instruction_return alu_helper::alu_and(unsigned int left, unsigned int right)
{
	auto result = left & right;
	return instruction_return(result);
}

instruction_return alu_helper::alu_eor(unsigned int left, unsigned int right)
{
	auto result = left ^ right;
	return instruction_return(result);
}

instruction_return alu_helper::alu_lsl(unsigned int left, unsigned int right)
{
	return 0;
}

instruction_return alu_helper::alu_lsr(unsigned int left, unsigned int right)
{
	return 0;
}

instruction_return alu_helper::alu_asr(unsigned int left, unsigned int right)
{
	return 0;
}

instruction_return alu_helper::alu_adc(unsigned int left, unsigned int right, bool carry)
{
	auto add_carry = 0;
	if (carry)
	{
		add_carry = 0x1000;
	}

	auto result = left + right + add_carry;
	return instruction_return(result);
}

instruction_return alu_helper::alu_sbc(unsigned int left, unsigned int right, bool carry)
{
	auto add_carry = 0;
	if (carry)
	{
		add_carry = ~0x1000;
	}
	auto result = left - right - add_carry;
	return instruction_return(result);
}

instruction_return alu_helper::alu_ror(unsigned int left, unsigned int right)
{
	return 0;
}

instruction_return alu_helper::alu_neg(unsigned int left)
{
	return instruction_return(0-left);
}

instruction_return alu_helper::alu_cmp(unsigned int left, unsigned int right)
{
	auto result = left - right;
	return instruction_return(result);
}

instruction_return alu_helper::alu_cmn(unsigned int left, unsigned int right)
{
	auto result = left - right;
	return instruction_return(result);
}

instruction_return alu_helper::alu_orr(unsigned int left, unsigned int right)
{
	auto result = left | right;
	return instruction_return(result);
}

instruction_return alu_helper::alu_mul(unsigned int left, unsigned int right)
{
	auto result = left * right;
	return instruction_return(result);
}

instruction_return alu_helper::alu_bic(unsigned int left, unsigned int right)
{
	auto result = left & ~right;
	return instruction_return(result);
}

instruction_return alu_helper::alu_mvn(unsigned int left)
{
	auto result = ~left - 0xFFFF0000;
	return instruction_return(result);
}
