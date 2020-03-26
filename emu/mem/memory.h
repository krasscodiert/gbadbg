#pragma once
#include <mutex>
#include <map>
#include <vector>
#include "arm_globals.h"
#include "util.h"

class memory
{
public:
	std::vector<char> * rom_data{};
private:
public:
	memory() = default;
	virtual ~memory() = default;

	virtual memory * clone()  const = 0;

	void set_rom_data(unsigned char * file, int len);

	virtual void write_word(int val, unsigned int address) = 0;
	virtual void write_halfword(short val, unsigned int address) = 0;
	virtual void write_byte(byte val, unsigned int address) = 0;

	virtual int read_word(unsigned int address) = 0;
	virtual short read_halfword(unsigned int address) = 0;
	virtual byte read_byte(unsigned int address) = 0;
private:
};
