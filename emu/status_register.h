#pragma once
#include <cstdint>

enum status_flag
{
	n = 0x80000000,
	z = 0x40000000,
	c = 0x20000000,
	v = 0x10000000,
	q = 0x08000000,
	i = 0x80,
	f = 0x40,
	t = 0x2
};
constexpr enum status_flag operator |(const status_flag self, const status_flag in)
{
	return static_cast<enum status_flag>(int(self) | int(in));
}

class status_register
{
public:
private:
	status_flag flags_;
public:
	status_register()
	{
		this->flags_ = static_cast<status_flag>(0x00000000);
	}

	status_register(unsigned init_value)
	{
		this->flags_ = static_cast<status_flag>(init_value);
	}

	void operator|=(status_flag in);				// set flags according to input - <in> can contain combined flags
	void operator-=(status_flag in);				// unset flags according to input - <in> can contain combined flags
	bool operator[](status_flag is_set) const;		// returns true if status flag has bits from input set - <is_set> can contain combined flags
	bool operator()(status_flag equals) const;		// returns true if status flag matches input exactly - <equals> can contain combined flags
private:
};
