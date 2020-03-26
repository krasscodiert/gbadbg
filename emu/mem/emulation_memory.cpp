#include "emulation_memory.h"

emulation_memory * emulation_memory::clone() const
{
	const auto clone = new emulation_memory(*this);
	return clone;
}

void emulation_memory::write_word(int val, unsigned int address)
{
	this->write_halfword(short(val), address);
	this->write_halfword(short(val >> 16), address + 2);
}

void emulation_memory::write_halfword(short val, unsigned int address)
{
	this->write_byte(byte(val), address);
	this->write_byte(byte(val >> 8), address + 1);
}

void emulation_memory::write_byte(byte val, unsigned int address)
{
	if (address >= arm_globals::code_start)
		throw std::exception("access violation");
	this->mem_[address] = val;
}

int emulation_memory::read_word(unsigned int address)
{
	int result = 0;
	result = this->read_halfword(address);
	result |= (this->read_halfword(address + 2) << 16);
	return result;
}

short emulation_memory::read_halfword(unsigned int address)
{
	short result = 0;
	result = this->read_byte(address);
	result |= (this->read_byte(address + 1) << 8);
	return result;
}

byte emulation_memory::read_byte(unsigned int address)
{
	if (address > this->mem_.size() - 1)
		throw std::exception("access violation");
	return mem_[address];
}