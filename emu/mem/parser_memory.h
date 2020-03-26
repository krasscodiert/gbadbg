#pragma once
#include "util.h"
#include "memory.h"

class parser_memory : public memory
{
public:
	std::map<unsigned int, byte> entries;
private:
	parser_memory(const parser_memory& base) : memory(base)
	{
		this->entries = base.entries;
		this->rom_data = base.rom_data;
	}
public:
	parser_memory(unsigned char * rom_data_, unsigned int len_)
	{
		this->entries = std::map<unsigned int, byte>();
		this->set_rom_data(rom_data_, len_);
	}

	~parser_memory() override = default;

	parser_memory * clone() const override;

	void write_word(int val, unsigned int address) override;
	void write_halfword(short val, unsigned int address) override;
	void write_byte(byte val, unsigned int address) override;

	int read_word(unsigned int address) override;
	short read_halfword(unsigned int address) override;
	byte read_byte(unsigned int address) override;
};