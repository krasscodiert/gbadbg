#pragma once
#include "status_register.h"
#include <string>
#include <vector>

class cpu
{
private:
	std::vector<int> registers_;
public:
	enum cpu_register_id
	{
		r0,
		r1,
		r2,
		r3,
		r4,
		r5,
		r6,
		r7,
		r8,
		r9,
		r10,
		r11,
		r12,
		r13,
		sp = 13,
		r14,
		lr = 14,
		r15,
		pc = 15,
		cpsr,
		spsr
	};
	status_register reg_status;
private:
public:
	cpu()
	{
		this->registers_ = std::vector<int>(spsr + 1, 0);
		this->reg_status = status_register(0x00);
	}

	cpu(const cpu& base)
	{
		this->registers_ = base.registers_;
		this->reg_status = base.reg_status;
	}

	unsigned int get_pc(bool relative = true);
	void set_pc(unsigned int value, bool relative = true);

	unsigned int get_sp(bool relative = true);
	void set_sp(unsigned int value, bool relative = true);
	void move_sp(const bool push, const bool descending_stack);

	std::string cpu_register_to_string(const unsigned int regiser_id, const bool try_use_name = false) const;
	std::string dump_registers() const;

	template<typename T>
	T reg(cpu_register_id id)
	{
		return static_cast<T>(this->registers_[id]);
	}

	template<typename T>
	void reg(cpu_register_id id, T data)
	{
		this->registers_[id] = static_cast<unsigned int>(data);
	}
};
