#pragma once
#include "util.h"
#include "memory.h"
#include <vector>
#include <exception>

class emulation_memory : public memory
{
public:
	std::vector<byte> mem_;
private:
	emulation_memory(const emulation_memory& base) : memory(base)
	{
		this->rom_data = base.rom_data;
		this->mem_ = base.mem_;
	}
public:
	emulation_memory(unsigned char * rom_data_, unsigned int len_)
	{
		this->mem_ = std::vector<byte>(arm_globals::code_start, 0);
		this->set_rom_data(rom_data_, len_);
	}

	~emulation_memory() = default;

	emulation_memory * clone() const override;

	void write_word(int val, unsigned int address) override;
	void write_halfword(short val, unsigned int address) override;
	void write_byte(byte val, unsigned int address) override;

	int read_word(unsigned int address) override;
	short read_halfword(unsigned int address) override;
	byte read_byte(unsigned int address) override;
};