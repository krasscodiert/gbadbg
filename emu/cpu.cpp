#include "cpu.h"
#include "arm_globals.h"

unsigned int cpu::get_pc(bool relative)
{
	return this->reg<int>(pc) - (relative ? arm_globals::code_start : 0);
}

void cpu::set_pc(unsigned int value, bool relative)
{
	this->reg(pc, value + (relative ? arm_globals::code_start : 0));
}

unsigned int cpu::get_sp(bool relative)
{
	return this->reg<int>(sp) - (relative ? arm_globals::user_stack_start : 0);
}

void cpu::set_sp(unsigned int value, bool relative)
{
	this->reg(sp, value + (relative ? arm_globals::user_stack_start : 0));
}

void cpu::move_sp(const bool push, const bool descending_stack)
{
	auto old_sp = this->reg<unsigned int>(sp);
	int value = 4;
	if (!push)
		value *= -1;
	if (descending_stack)
		value *= -1;

	this->reg(sp, old_sp + value);
}

std::string cpu::dump_registers() const
{
	std::string result;
	result += "==RegisterDump==\n";
	for (int i = 0; i < spsr + 1; ++i)
	{
		char* buf = new char[512];
		sprintf_s(buf, 512, "R%0*u: [0x%0*x]\n", 2, i, 8, registers_[i]);
		result += buf;
		delete[] buf;
	}
	result += "=======end======\n";
	return result;
}

