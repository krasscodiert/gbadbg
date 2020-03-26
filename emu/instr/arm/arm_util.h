#pragma once
#include <string>
#include <vector>
#include "arm_globals.h"
#include "cpu.h"

namespace arm_util 
{
	int arm_shift(int op1, int op2, arm_globals::arm_shift_type type);
	std::string cpu_register_to_string(const cpu::cpu_register_id register_id, const bool try_use_name = true);
	std::vector<bool> parse_register_list(int list, unsigned int from, unsigned int to);
}
