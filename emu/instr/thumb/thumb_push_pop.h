#pragma once
#include "thumb_instruction.h"
#include "instruction_string.h"
#include "arm_util.h"

enum class thumb_push_pop_opcode_type
{
	t_push = 0,
	t_pop = 1
};

class thumb_push_pop_instruction : public thumb_instruction
{
public:
	std::vector<bool> r_list{};
	bool pc_lr{};
private:
public:
	thumb_push_pop_instruction(const bool pc_lr_, const unsigned int rList_) {
		this->pc_lr = pc_lr_;
		this->r_list = arm_util::parse_register_list(rList_, 0, 7);
	}

	virtual void run(gba_context* gba_) override;
	virtual instruction_string print() override;
private:
};

class thumb_push_pop_push : public thumb_push_pop_instruction
{
public:
	thumb_push_pop_push(thumb_push_pop_instruction* base_) : thumb_push_pop_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};

class thumb_push_pop_pop : public thumb_push_pop_instruction
{
public:
	thumb_push_pop_pop(thumb_push_pop_instruction* base_) : thumb_push_pop_instruction(*base_) {};
private:
public:
	void run(gba_context* gba_) override;
	instruction_string print() override;
private:
};
