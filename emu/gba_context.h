#pragma once
#include "cpu.h"
#include "memory.h"
#include "parser_memory.h"

class gba_context
{
public:
	cpu cpu;
	memory * memory;
	bool thumb_mode_;
private:
public:
	gba_context()
	{
		this->cpu = cpu::cpu();
		this->thumb_mode_ = false;
	};

	gba_context(const gba_context& base)
	{
		this->cpu = cpu::cpu(base.cpu);
		this->memory = base.memory->clone();
		this->thumb_mode_ = base.thumb_mode_;
	};

	~gba_context()
	{
		delete memory;
	}

	unsigned get_next_instruction_offset_(unsigned int address) const;
private:
};

// ldr, str, mov, add