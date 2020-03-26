#pragma once
#include "memory.h"

void memory::set_rom_data(unsigned char * file, int len)
{
	this->rom_data = new std::vector<char>(file, file + len); 
}
