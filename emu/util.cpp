#include "util.h"
#include <vector>
#include <fstream>
#include <bitset>
#include <sstream>

char* util::load_file(std::string filename, int* len)
{
	std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open())
	{
		const int size = static_cast<int>(file.tellg());
		char * memblock = new char[size];
		file.seekg(0, std::ios::beg);
		file.read(memblock, size);
		file.close();

		*len = size;
		return memblock;
	}
	printf("unable to load file %s\n", filename.c_str());
	return nullptr;
}

std::string util::value_to_string(const int value, const bool thumb_mode_, const number_type number_type)
{
	switch (number_type)
	{
	case binary:
	{
		if (thumb_mode_)
		{
			return (std::bitset<16>(value).to_string()) + "b"; 
		}
		else
		{
			return (std::bitset<32>(value).to_string()) + "b"; 
		}
	}
	case octal:
	{
		std::stringstream stream;
		stream << std::oct << value;
		std::string result = stream.str();
		if (thumb_mode_)
		{
			while (result.length() < 6)
			{
				result = "0" + result;
			}
		}
		else
		{
			while (result.length() < 11)
			{
				result = "0" + result;
			}
		}
		return std::string(result + "o");
	}
	case decimal:
		return std::string(value + "d");
	case hexadecimal:
	{
		std::stringstream stream;
		stream << std::hex << value;
		std::string result = stream.str();
		if (thumb_mode_)
		{
			while (result.length() < 4)
			{
				result = "0" + result;
			}
		}
		else
		{
			while (result.length() < 8)
			{
				result = "0" + result;
			}
		}
		return std::string(result + "h");
	}
	default:
		break;
	}
	return std::string();
}

long int util::get_timestamp_millis()
{
	return static_cast<long>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

long int util::get_timestamp_nanos()
{
	return static_cast<long>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

int util::sign_extend(int number, int size)
{
	const bool is_negative = ((number >> size) & 0b1) == 1;
	if(is_negative)
	{
		const int one = 1 << (size - 1);
		return (number ^ one) - one;
	}
	return number;
}

bool util::is_bit_set(int bit, unsigned int bitmask)
{
	return ((bitmask >> bit) & 1) == 1;
}

bool util::are_bits_equal(int n, int m)
{
	return (n ^ m) == 0;
}

std::string util::get_working_directory(){
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}

std::string util::get_rom_directory() {
	auto workingDir = get_working_directory();
	auto str = workingDir + "\\RomFiles";
	return str;
}

int util::rotate_right(unsigned int number, unsigned int rotate_by)
{
	return (number >> rotate_by) | (number << ((sizeof(number) * 8) - rotate_by));
}