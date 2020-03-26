#include "parser_memory.h"

parser_memory * parser_memory::clone() const
{
	const auto clone = new parser_memory(*this);
	return clone;
}

void parser_memory::write_word(int val, unsigned int address)
{
	this->write_halfword(short(val), address);
	this->write_halfword(short(val >> 16), address + 2);
}

void parser_memory::write_halfword(short val, unsigned int address)
{
	this->write_byte(byte(val), address);
	this->write_byte(byte(val >> 8), address + 1);
}

void parser_memory::write_byte(byte val, unsigned int address)
{
	if (entries.find(address) == entries.end()) {
		entries.insert(std::pair<unsigned, byte>(address, val));
	}
	else
	{
		entries[address] = val;
	}
}

int parser_memory::read_word(unsigned int address)
{
	int result = 0;
	result = this->read_halfword(address);
	result |= (this->read_halfword(address + 2) << 16);
	return result;
}

short parser_memory::read_halfword(unsigned int address)
{
	short result = 0;
	result = this->read_byte(address);
	result |= (this->read_byte(address + 1) << 8);
	return result;
}

byte parser_memory::read_byte(unsigned int address)
{
	byte result = 0;
	if (address >= arm_globals::code_start)
	{
		std::memcpy(&result, this->rom_data->data() + (address - arm_globals::code_start), sizeof(byte));
	}

	const auto found = this->entries.find(address);
	if (found != this->entries.end()) {
		result = found->second;
	}
	return result;
}