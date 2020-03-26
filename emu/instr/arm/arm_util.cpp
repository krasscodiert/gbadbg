#include "arm_util.h"
#include "util.h"

int arm_util::arm_shift(int op1, int op2, arm_globals::arm_shift_type type) {

	switch (type)
	{
	case arm_globals::arm_shift_type::lsl:
		return static_cast<int>(static_cast<unsigned int>(op1) << op2);
		break;
	case arm_globals::arm_shift_type::lsr:
		if (op2 == 0)
			return 0;
		return static_cast<int>(static_cast<unsigned int>(op1) >> op2);
	case arm_globals::arm_shift_type::asr:
		return  op1 >> op2;
	case arm_globals::arm_shift_type::ror:
		return util::rotate_right(op1, op2);
	default:
		throw std::exception("invalid shift type");
	}
}
std::string arm_util::cpu_register_to_string(const cpu::cpu_register_id register_id, const bool try_use_name)
{
	switch (register_id)
	{
	case cpu::r0:
	case cpu::r1:
	case cpu::r2:
	case cpu::r3:
	case cpu::r4:
	case cpu::r5:
	case cpu::r6:
	case cpu::r7:
	case cpu::r8:
	case cpu::r9:
	case cpu::r10:
	case cpu::r11:
	case cpu::r12:
	{
		auto str = std::string("r" + std::to_string(register_id));
		return str;
	}
	case cpu::r13:
	{
		if (try_use_name)
		{
			return std::string("SP");
		}
		return std::string("r" + std::to_string(register_id));
	}
	case cpu::r14:
	{
		if (try_use_name)
		{
			return std::string("LR");
		}
		return std::string("r" + std::to_string(register_id));
	}
	case cpu::r15:
	{
		if (try_use_name)
		{
			return std::string("PC");
		}
		return std::string("r" + std::to_string(register_id));
	}
	default:
		return std::string("not supported register");;
	}
}


std::vector<bool> arm_util::parse_register_list(int list, unsigned int from, unsigned int to)
{
	if (to < from)
	{
		const auto swap = to;
		to = from;
		from = swap;
	}
	size_t size = (to - from) + 1;

	std::vector<bool> r_list = std::vector<bool>(size, false);
	for (size_t i = from; i < to + 1; i++)
	{
		r_list[i] = util::is_bit_set(i, list);
	}
	return r_list;
}
