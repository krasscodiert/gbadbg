#pragma once

namespace arm_globals
{
	enum arm_shift_type
	{
		lsl = 0,
		lsr = 1,
		asr = 2,
		ror = 3
	};

	enum memory_sections
	{
		null,
		user_stack_start = 0x03007F00,
		code_start = 0x08000000,
		code_end = 0x08FFFFFF,
	};
}