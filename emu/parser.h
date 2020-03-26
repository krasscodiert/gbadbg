#pragma once
#include <map>
#include "instruction.h"

class parser
{
public:
	unsigned int position = 0;
private:
	unsigned char* file_;
	unsigned int file_len_;
	std::map<unsigned int, instruction *> code_;
public:
	parser(unsigned char* file, int len);
	void parse();
private:
	void parse_(gba_context* context);
	instruction* parse_current_arm_(unsigned int address) const;
	instruction* parse_current_thumb_(unsigned int address, gba_context * context) const;
	void register_instruction_(unsigned int address, instruction * i);
	bool is_address_registered_(unsigned int address);
	bool is_opcode_of_type(const char* mask, unsigned int opcode, bool is_thumb = false) const;
	bool is_current_cond_flag_equal_(unsigned char cond, unsigned int opcode) const;
	unsigned int get_current_arm_opcode_(unsigned int address) const;
	unsigned short get_current_thumb_opcode_(unsigned int address) const;
};
