#include "thumb_ldr_str_byte_half.h"
#include "arm_util.h"

void thumb_ldr_str_byte_half_strh::run(gba_context * gba_)
{
}

instruction_string thumb_ldr_str_byte_half_strh::print()
{
	const auto src_dest_reg_str = arm_util::cpu_register_to_string(this->src_dest_reg);
	const auto base_reg_str = arm_util::cpu_register_to_string(this->base_reg);
	const auto off_reg_str = arm_util::cpu_register_to_string(this->off_reg);

	auto return_vec = instruction_string("STRH");
	return_vec.add(expression(this->src_dest_reg));
	return_vec.add(expression(this->base_reg, this->off_reg));

	return return_vec;
}