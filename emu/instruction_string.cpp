#include "instruction_string.h"
#include "arm_util.h"
#include "util.h"

std::string expression::to_string()
{
	switch (type_)
	{
	case value:
		return util::value_to_string(value_, true);
	case reg:
		return arm_util::cpu_register_to_string(s1_);
	case r_list:
	{
		std::string str = "";
		bool is_first = true;
		int hit_in_a_row = 0;
		auto size = rList_.size();
		for (size_t i = 0; i < size; i++)
		{
			if (rList_[i])
			{
				hit_in_a_row++;
				if (is_first)
				{
					auto st = arm_util::cpu_register_to_string(static_cast<cpu::cpu_register_id>(i), false);
					str += st;
					hit_in_a_row++;
					is_first = false;
					continue;
				}
				if (hit_in_a_row > 1)
				{
					if (i == size - 1)
					{
						str += "-" + arm_util::cpu_register_to_string(static_cast<cpu::cpu_register_id>(i));
					}
					continue;
				}
				else
				{
					str += ", " + arm_util::cpu_register_to_string(static_cast<cpu::cpu_register_id>(i));
				}
			}
			else {
				hit_in_a_row = hit_in_a_row;
			}
		}
		return "{" + str + "}";
	}
	case inline_shift:
	{
		std::string shift_str;
		switch (shift_type_)
		{
		case arm_globals::arm_shift_type::lsl:
			shift_str = "LSL";
			break;
		case arm_globals::arm_shift_type::lsr:
			shift_str = "LSR";
			break;
		case arm_globals::arm_shift_type::asr:
			shift_str = "ASR";
			break;
		case arm_globals::arm_shift_type::ror:
			shift_str = "ROR";
			break;
		default:
			return "not initialized";
		}

		if (value_ == -1)
		{
			return "(" + shift_str + " " + arm_util::cpu_register_to_string(s1_) + ")";
		}
		else
		{
			return "(" + shift_str + " " + util::value_to_string(value_, true) + ")";
		}
	}
	case memory_accessor:
	{
		if (value_ == -1)
		{
			return "[" + arm_util::cpu_register_to_string(s1_) + ", " + arm_util::cpu_register_to_string(s2_) + "]";
		}
		else
		{
			if (value_ == 0)
			{
				return "[" + arm_util::cpu_register_to_string(s1_) + "]";
			}
			return "[" + arm_util::cpu_register_to_string(s1_) + ", " + util::value_to_string(value_, true) + "]";
		}
	}
	default:
		return "not initialized";
	}
}

std::string instruction_string::to_string() {
	std::string ret = instruction_type_;
	while (ret.length() < 4)
	{
		ret += " ";
	}

	bool is_first = true;

	for (auto expression : expressions_)
	{
		if (is_first)
		{
			ret = ret + " " + expression.to_string();
			is_first = false;
			continue;
		}
		ret = ret + ", " + expression.to_string();
	}
	return ret;
}

void instruction_string::add(expression ex) {
	expressions_.push_back(ex);
}

void instruction_string::insert(instruction_string s, int index)
{
	auto i = this->expressions_.begin() + index;
	for (const auto& e : s.expressions_)
	{
		this->expressions_.insert(i++, e);
	}
}
