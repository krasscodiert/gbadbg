#pragma once
#include <windows.h>
#include <string>
#include <chrono>

#define LEN(a) (sizeof(a) / sizeof(a[0]))

namespace util
{
	enum number_type {
		binary = 2,
		octal = 8,
		decimal = 10,
		hexadecimal = 16
	};

	bool is_bit_set(int bit, unsigned int bitmask);
	bool are_bits_equal(int n, int m);

	long int get_timestamp_millis();
	long int get_timestamp_nanos();

	int sign_extend(int number, int size);
	int rotate_right(unsigned int number, unsigned int rotate_by);

	template <typename T>
	T extract_bits(int value, int from, int to)
	{
		if (to < from)
		{
			const auto swap = to;
			to = from;
			from = swap;
		}

		int clear_mask_right = 0xFFFFFFFF;
		clear_mask_right = clear_mask_right << from;

		int clear_mask_left = 0xFFFFFFFF;
		clear_mask_left = clear_mask_left << (to + 1);
		clear_mask_left = clear_mask_left ^ 0xFFFFFFFF;

		value = clear_mask_right & value;
		value = clear_mask_left & value;

		return (static_cast<T>(value >> from));
	};

	std::string get_working_directory();
	std::string get_rom_directory();
	char* load_file(std::string filename, int* len);

	std::string value_to_string(const int value, const bool thumb_mode_, const number_type number_type = hexadecimal);
}
