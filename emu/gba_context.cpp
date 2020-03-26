#include "gba_context.h"

unsigned gba_context::get_next_instruction_offset_(unsigned int address) const
{
	auto offset = this->thumb_mode_ ? 0x02 : 0x04;
	return address + offset;
}
