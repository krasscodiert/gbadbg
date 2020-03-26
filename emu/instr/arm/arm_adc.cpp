#include "arm_alu.h"
void arm_adc::run(gba_context * gba)
{
}

instruction_string arm_adc::print()
{
	auto return_vec = instruction_string("ADC");
	return_vec.add(expression(reg_dest));
	return_vec.add(expression(reg_src));
	const auto op2 = arm_alu_instruction::print();
	return_vec.insert(op2, 2);
	return return_vec;
}