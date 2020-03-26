#include "instruction_return.h"


const bool instruction_return::get_sign()
{
	return sign;
}

const bool instruction_return::get_zero()
{
	return zero;
}

const bool instruction_return::get_carry()
{
	return carry;
}

const bool instruction_return::get_overflow()
{
	return overflow;
}

const unsigned int instruction_return::get_value()
{
	unsigned int return_value = value;

	if (sign)
	{
		//return signer value 
		return_value = return_value;
	}

	if (carry || overflow)
	{
		return_value = return_value & 0xFFFF;
	}

	return return_value;
}

instruction_return::instruction_return(unsigned int _value)
{
	//look how signed values work in thumb
	sign = static_cast<int>(_value) < 0;
	zero = _value == 0;
	carry = (_value & 0x10000) != 0;
	overflow = _value > 0x10000;
	value = _value;
}

instruction_return::~instruction_return()
{
}
