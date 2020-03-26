#include "rom.h"

rom::rom(char* data, int rom_size)
{
	this->rom_size = rom_size;
	this->raw_data_ = static_cast<unsigned char*>(malloc(rom_size));
	memcpy(this->raw_data_, data, rom_size);
}

rom::~rom()
{
	free(this->raw_data_);
}

void rom::parse_internal_information()
{
	memcpy(&this->entry_point, &(this->raw_data_[0x00]), 4);
	memcpy(&this->bitmap, &(this->raw_data_[0x04]), 156);
	memcpy(&this->title, &(this->raw_data_[0xA0]), 12);
	memcpy(&this->game_code, &(this->raw_data_[0xAC]), 4);
	memcpy(&this->maker_code, &(this->raw_data_[0xB0]), 2);
}

void rom::parse_code()
{
	parser p = parser(this->raw_data_, this->rom_size);
	p.parse();
}
