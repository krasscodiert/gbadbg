#include "parser.h"
#include "arm_parser.h"
#include "thumb_parser.h"
#include "util.h"

#include "instr/arm/arm_branch.h"
#include "thumb_hireg_bx.h"
#include "thumb_conditional_branch.h"
#include "thumb_unconditional_branch.h"
#include "thumb_long_branch_link.h"
#include "parser_memory.h"

parser::parser(unsigned char * file, int len)
{
	this->file_ = file;
	this->file_len_ = len;
}

void parser::parse()
{	
	gba_context parsing_context;
	parsing_context.memory = new parser_memory(this->file_, this->file_len_);
	parsing_context.cpu.set_pc(0);
	parsing_context.cpu.set_sp(0);
	this->parse_(&parsing_context);
}

void parser::parse_(gba_context* context)
{
	while(true)
	{
		const auto current_offset = context->cpu.get_pc();
		if (this->is_address_registered_(current_offset))
			return;

		instruction* i = nullptr;
		if (!context->thumb_mode_)
		{
			i = this->parse_current_arm_(current_offset);
		}
		else
		{
			i = this->parse_current_thumb_(current_offset, context);

			auto opcode_str_ = util::value_to_string(this->get_current_thumb_opcode_(current_offset), context->thumb_mode_);
			auto opcode = opcode_str_.c_str();

			auto v = util::value_to_string(context->cpu.get_pc(false), false, util::number_type::hexadecimal);
			auto value = v.c_str();
			auto i_str = i->print();
			auto i_str_str = i_str.to_string();
			auto opcode_str = i_str_str.c_str();
			printf("%s| %s: %s \n", value, opcode, opcode_str);
		}

		if (i == nullptr)
			throw std::exception("no instruction parsed");

		//printf("[parser] new instruction @[0x%x]\n", current_offset);
		this->register_instruction_(current_offset, i);

		gba_context alternative_context(*context);

		i->run(context);

		//printf("%s", context->cpu.dump_registers().c_str());

		unsigned int new_offset = 0;
		if (dynamic_cast<arm_bx*>(i))
		{
			const auto branch_exchange = dynamic_cast<arm_bx*>(i);
			alternative_context.thumb_mode_ = true;
			new_offset = branch_exchange->calculate_target_address(context->cpu.reg<unsigned int>(branch_exchange->reg));
			(&alternative_context)->cpu.set_pc(new_offset, false);
			//printf("		- bx @[0x%x]\n", new_offset);
			this->parse_(&alternative_context);
			alternative_context.thumb_mode_ = false;
		}
		else if(dynamic_cast<arm_b*>(i))
		{
			const auto branch = dynamic_cast<arm_b*>(i);
			//printf("		- b @[0x%x]\n", current_offset + branch->calculate_target_address());
			(&alternative_context)->cpu.set_pc(current_offset + branch->calculate_target_address());
			parse_((&alternative_context));
		}
		else if (dynamic_cast<thumb_conditional_branch_instruction*>(i))
		{
			const auto branch = dynamic_cast<thumb_conditional_branch_instruction*>(i);
			if (branch->is_condition_true)
			{
				(&alternative_context)->cpu.set_pc((context->get_next_instruction_offset_(current_offset)));
				parse_(&alternative_context);
			}
			else
			{
				auto alternative_pc = current_offset + branch->calculate_target_address();
				(&alternative_context)->cpu.set_pc(alternative_pc);
				parse_(&alternative_context);
				context->cpu.set_pc(context->get_next_instruction_offset_(current_offset));
			}
		}
		else if (dynamic_cast<thumb_hireg_bx_bx*>(i))
		{
			continue;
		}
		else if (dynamic_cast<thumb_unconditional_branch_b*>(i))
		{
			continue;
		}
		else if (dynamic_cast<thumb_long_branch_link_bl*>(i))
		{
			continue;
		}
		else
		{
			context->cpu.set_pc(context->get_next_instruction_offset_(current_offset));
		}
	}
}

instruction * parser::parse_current_arm_(unsigned int address) const
{
	const auto opcode = this->get_current_arm_opcode_(address);
	instruction * i = nullptr;
	if(this->is_opcode_of_type(A_BRANCH_LINK, opcode))
	{
		i = arm_parser::parse_arm_branch(opcode);
	}
	else if(this->is_opcode_of_type(A_BRANCH_LINK_EXCHANGE, opcode))
	{
		i = arm_parser::parse_arm_exchange(opcode);
	}
	else if (this->is_opcode_of_type(A_SOFWARE_INTERRUPT, opcode))
	{
		i = arm_parser::parse_arm_software_interrupt(opcode);
	}
	else if (this->is_opcode_of_type(A_ALU_IMMEDIATE, opcode) || this->is_opcode_of_type(A_ALU_REGISTER_0, opcode) || this->is_opcode_of_type(A_ALU_REGISTER_1, opcode))
	{
		i = arm_parser::parse_arm_alu(opcode);
	}
	else if (this->is_opcode_of_type(A_PSR_IMMEDIATE, opcode) || this->is_opcode_of_type(A_PST_REGISTER, opcode))
	{
		i = arm_parser::parse_arm_psr(opcode);
	}
	else if (this->is_opcode_of_type(A_BKPT, opcode))
	{
		// ARM9
	}
	else if (this->is_opcode_of_type(A_CLZ, opcode))
	{
		// ARM9
	}
	else if (this->is_opcode_of_type(A_QALU, opcode))
	{
		// ARM9 
	}
	else if (this->is_opcode_of_type(A_MULTIPLY, opcode) || this->is_opcode_of_type(A_MULTIPLY_LONG, opcode) || this->is_opcode_of_type(A_MULTIPLY_HALF, opcode))
	{
		i = arm_parser::parse_arm_multiply(opcode);
	}
	else if (this->is_opcode_of_type(A_TRANS_SWP12, opcode))
	{
		i = arm_parser::parse_arm_swap(opcode);
	}
	else if (this->is_opcode_of_type(A_TRANS_REGISTER_10, opcode) || this->is_opcode_of_type(A_TRANS_IMMEDIATE_10, opcode))
	{
		i = arm_parser::parse_arm_half_double_signed_transfer(opcode);
	}
	else if (this->is_opcode_of_type(A_TRANS_IMMEDIATE_9, opcode) || this->is_opcode_of_type(A_TRANS_REGISTER_9, opcode))
	{
		i = arm_parser::parse_arm_single_data_transfer(opcode);
	}
	else if (this->is_opcode_of_type(A_UNDEFINED, opcode))
	{
		// undefined
	}
	else if (this->is_opcode_of_type(A_BLOCK_TRANS, opcode))
	{
		i = arm_parser::parse_arm_block_data_transfer(opcode);
	}
	else if (this->is_opcode_of_type(A_CO_DATA_TRANS, opcode))
	{
		i = arm_parser::parse_arm_coprocessor_data_transfer(opcode);
	}
	else if (this->is_opcode_of_type(A_CO_RR, opcode))
	{
		// ARM9
	}
	else if (this->is_opcode_of_type(A_CO_DATA_OP, opcode))
	{
		i = arm_parser::parse_arm_coprocessor_data_operations(opcode);
	}
	else if (this->is_opcode_of_type(A_CO_REGISTER_TRANS, opcode))
	{
		i = arm_parser::parse_arm_coprocessor_register_transfer(opcode);
	}
	return i;
}

instruction * parser::parse_current_thumb_(unsigned int address, gba_context * context) const
{
	const auto is_thumb = context->thumb_mode_;
	const unsigned short opcode = this->get_current_thumb_opcode_(address);
	instruction * i = nullptr;
	if (this->is_opcode_of_type(T_ADD_SUB, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_add_sub(opcode);
	}
	else if (this->is_opcode_of_type(T_SHIFT, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_shift(opcode);
	}
	else if (this->is_opcode_of_type(T_IMMEDIATE, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_immediate(opcode);
	}
	else if (this->is_opcode_of_type(T_ALU, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_alu(opcode);
	}
	else if (this->is_opcode_of_type(T_HIREG_BX, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_hireg_bx(opcode);
	}
	else if (this->is_opcode_of_type(T_LDR_PC, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_ldr_pc(opcode);
	}
	else if (this->is_opcode_of_type(T_LDR_STR, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_ldr_str(opcode);
	}
	else if (this->is_opcode_of_type(T_LDR_STR_BYTE_HALF, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_ldr_str_byte_half(opcode);
	}
	else if (this->is_opcode_of_type(T_LDR_STR_IMMEDIATE, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_ldr_str_immediate(opcode);
	}
	else if (this->is_opcode_of_type(T_LDR_STR_HALF, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_ldr_str_half(opcode);
	}
	else if (this->is_opcode_of_type(T_LDR_STR_SP, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_ldr_str_sp(opcode);
	}
	else if (this->is_opcode_of_type(T_ADD_OFFSET_RELATIVE, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_add_offset_relative(opcode);
	}
	else if (this->is_opcode_of_type(T_ADD_OFFSET_SP, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_add_offset_sp(opcode);
	}
	else if (this->is_opcode_of_type(T_PUSH_POP, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_push_pop(opcode);
	}
	else if (this->is_opcode_of_type(T_MULTIPLE_LD_ST, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_multiple_ld_st(opcode);
	}
	else if (this->is_opcode_of_type(T_SOFTWARE_INTERRUPT, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_software_interrupt(opcode);
	}
	else if (this->is_opcode_of_type(T_CONDITIONAL_BRANCH, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_conditional_branch(opcode);
	}
	else if (this->is_opcode_of_type(T_UNCONDITIONAL_BRANCH, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_unconditional_branch(opcode);
	}
	else if (this->is_opcode_of_type(T_LONG_BRANCH_LINK, opcode, is_thumb))
	{
		i = thumb_parser::parse_thumb_long_branch_link(opcode);
		const unsigned int lower_address = context->get_next_instruction_offset_(address);
		auto address_opcode = this->get_current_thumb_opcode_(lower_address);
		const unsigned int lower_address_address = util::extract_bits<unsigned int>(address_opcode, 10, 0);
		dynamic_cast<thumb_long_branch_link_bl *>(i)->set_lower_offset(lower_address_address);
		int a = 1 + 2;
	}
	else
	{
		throw std::exception("no valid thumb instruction");
	}
	return i;
}

bool parser::is_opcode_of_type(const char* mask, unsigned int opcode, bool is_thumb) const
{
	bool match = true;
	int i = 0;
	while (match)
	{
		if (i == (is_thumb ? 8 : 24))
		{
			return match;
		}
		if (mask[i] == 'X')
		{
			i++;
			continue;
		}
		const auto result = util::is_bit_set((is_thumb ? 15 : 27) - i, opcode);
		match = (result && mask[i] == '1') || (!result && mask[i] == '0');
		i++;
	}
	return match;
}

 unsigned int parser::get_current_arm_opcode_(unsigned int address) const
 {
	 unsigned int current_opcode = 0;
	 memcpy(&current_opcode, &(this->file_[address]), 4);
	 return current_opcode;
 }

 unsigned short parser::get_current_thumb_opcode_(unsigned int address) const
 {
	 unsigned short current_opcode = 0;
	 memcpy(&current_opcode, &(this->file_[address]), 2);
	 return current_opcode;
 }

 bool parser::is_current_cond_flag_equal_(unsigned char cond, unsigned int opcode) const
 {
	 int cond_flag = util::extract_bits<int>(opcode, 28, 31);
	 cond_flag &= 0b00001111;
	 //memcpy(&cond_flag, &(this->file_[position + 3]), 1);
	 //cond_flag = cond_flag >> 4;
	 return util::are_bits_equal(cond, cond_flag);
 }

 void parser::register_instruction_(unsigned int address, instruction* instr)
 {
	 this->code_.insert(std::pair<unsigned int, instruction*>(address, instr));
 }

 bool parser::is_address_registered_(unsigned int address)
 {
	 return this->code_.find(address) != this->code_.end();
 }