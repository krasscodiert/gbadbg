#include "status_register.h"

void status_register::operator|=(status_flag in)
{
	this->flags_ = this->flags_ | in;
}

void status_register::operator-=(status_flag in)
{
	this->flags_ = status_flag(this->flags_ & ~in);
}

bool status_register::operator[](status_flag is_set) const
{
	return (this->flags_ & is_set) == is_set;
}

bool status_register::operator()(status_flag equals) const
{
	return this->flags_ == equals;
}
