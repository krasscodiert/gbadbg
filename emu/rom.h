#pragma once
#include "parser.h"

class rom
{
public:
	unsigned int entry_point;
	char bitmap[156];
	char title[12];
	unsigned int game_code;
	unsigned short maker_code;
	int rom_size;
private:
	unsigned char * raw_data_;
public:
	rom(char* data, int rom_size);
	~rom();
	void parse_internal_information();
	void parse_code();
private:
};
