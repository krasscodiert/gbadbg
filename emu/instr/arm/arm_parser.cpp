#include "arm_parser.h"
#include "util.h"
#include "arm_branch.h"
#include "arm_alu.h"
#include "arm_block_data_transfer.h"
#include "arm_coprocessor.h"
#include "arm_half_double_signed_transfer.h"
#include "arm_multiply.h"
#include "arm_psr_transfer.h"
#include "arm_single_data_transfer.h"
#include "arm_swap.h"

instruction * arm_parser::parse_arm_branch(const unsigned int current_instruction)
{
	const arm_instruction::condition_flag flag = util::extract_bits<arm_instruction::condition_flag>(current_instruction, 28, 31);
	int offset =	util::extract_bits<int>(current_instruction, 0, 23);
	offset =		util::sign_extend(offset, 24);

	if (!util::is_bit_set(24, current_instruction))
	{
		return new arm_b(offset, flag);
	}
	return new arm_bl(offset, flag);
}

instruction * arm_parser::parse_arm_exchange(const unsigned int current_instruction)
{
	const arm_instruction::condition_flag flag = util::extract_bits<arm_instruction::condition_flag>(current_instruction, 28, 31);
	const int reg_num = util::extract_bits<int>(current_instruction, 0, 3);
	if (util::is_bit_set(5, current_instruction))
	{
		return new arm_blx(cpu::cpu_register_id(reg_num), flag);
	}
	return new arm_bx(cpu::cpu_register_id(reg_num), flag);
}

instruction * arm_parser::parse_arm_software_interrupt(unsigned int current_instruction)
{
	const arm_instruction::condition_flag flag = util::extract_bits<arm_instruction::condition_flag>(current_instruction, 28, 31);
	const int opcode = util::extract_bits<int>(current_instruction, 24, 27);
	if (util::are_bits_equal(opcode, 0b1111))
	{
		const unsigned int comment = util::extract_bits<int>(current_instruction, 0, 23);
		return new arm_swi(comment, flag);
	}
	return nullptr;
}

instruction * arm_parser::parse_arm_alu(unsigned int current_instruction)
{
	const arm_instruction::condition_flag flag =		util::extract_bits<arm_instruction::condition_flag>(current_instruction, 28, 31);
	const arm_alu_opcode_type opcode =					util::extract_bits<arm_alu_opcode_type>(current_instruction, 21, 24);
	const cpu::cpu_register_id reg_src =				util::extract_bits<cpu::cpu_register_id>(current_instruction, 16, 19);
	const cpu::cpu_register_id second_op =				util::extract_bits<cpu::cpu_register_id>(current_instruction, 0, 3);
	const cpu::cpu_register_id reg_dest =				util::extract_bits<cpu::cpu_register_id>(current_instruction, 12, 15);
	const cpu::cpu_register_id reg_shift =				util::extract_bits<cpu::cpu_register_id>(current_instruction, 8, 11);
	const int shift_amount_immediate =					util::extract_bits<cpu::cpu_register_id>(current_instruction, 8, 11);// alternatively shift values register
	const int shift_amount =							util::extract_bits<int>(current_instruction, 7, 11);
	const int shift_immediate =							util::extract_bits<int>(current_instruction, 0, 7);
	const arm_globals::arm_shift_type type =			util::extract_bits<arm_globals::arm_shift_type>(current_instruction, 5, 6);
	const bool set_condition_flags =					util::is_bit_set(20, current_instruction);
	const bool is_2op_immediate =						util::is_bit_set(25, current_instruction);
	const bool is_shift_by_register =					util::is_bit_set(4, current_instruction);

	arm_alu_instruction *instr = nullptr;
	if (is_2op_immediate)
		instr = new arm_alu_instruction(reg_dest, reg_src, shift_amount_immediate, shift_immediate, set_condition_flags, flag);
	else
	{
		if (is_shift_by_register)
			instr = new arm_alu_instruction(reg_dest, reg_src, type, reg_shift, second_op, set_condition_flags, flag);
		else
			instr = new arm_alu_instruction(reg_dest, reg_src, shift_amount, type, second_op, set_condition_flags, flag);
	}

	if (instr == nullptr)
		throw std::exception("invalid arm_alu_instruction format");

	switch (opcode)
	{
	case arm_alu_opcode_type::a_and:
		return new arm_and(instr);
	case arm_alu_opcode_type::a_eor:
		return new arm_eor(instr);
	case arm_alu_opcode_type::a_sub:
		return new arm_sub(instr);
	case arm_alu_opcode_type::a_rsb:
		return new arm_rsb(instr);
	case arm_alu_opcode_type::a_add:
		return new arm_add(instr);
	case arm_alu_opcode_type::a_adc:
		return new arm_adc(instr);
	case arm_alu_opcode_type::a_sbc:
		return new arm_sbc(instr);
	case arm_alu_opcode_type::a_rsc:
		return new arm_rsc(instr);
	case arm_alu_opcode_type::a_tst:
		return new arm_tst(instr);
	case arm_alu_opcode_type::a_teq:
		return new arm_teq(instr);
	case arm_alu_opcode_type::a_cmp:
		return new arm_cmp(instr);
	case arm_alu_opcode_type::a_cmn:
		return new arm_cmn(instr);
	case arm_alu_opcode_type::a_orr:
		return new arm_orr(instr);
	case arm_alu_opcode_type::a_mov:
		return new arm_mov(instr);
	case arm_alu_opcode_type::a_bic:
		return new arm_bic(instr);
	case arm_alu_opcode_type::a_mvn:
		return new arm_mvn(instr);
	default:
		throw std::exception("invalid arm_alu_opcode");
	}
}

instruction * arm_parser::parse_arm_multiply(unsigned int current_instruction)
{
	const arm_instruction::condition_flag flag = util::extract_bits<arm_instruction::condition_flag>(current_instruction, 28, 31);
	const arm_mul_opcode_type opcode =		util::extract_bits<arm_mul_opcode_type>(current_instruction, 21, 24);
	const bool set_condition_codes =		util::extract_bits<bool>(current_instruction, 20, 20);
	const cpu::cpu_register_id reg_dest =	util::extract_bits<cpu::cpu_register_id>(current_instruction, 16, 19);
	const cpu::cpu_register_id reg_acc =	util::extract_bits<cpu::cpu_register_id>(current_instruction, 12, 15);
	const cpu::cpu_register_id reg_rs =		util::extract_bits<cpu::cpu_register_id>(current_instruction, 8, 11);
	const cpu::cpu_register_id reg_rm =		util::extract_bits<cpu::cpu_register_id>(current_instruction, 0, 3);
	const bool use_rs_upper =				util::extract_bits<bool>(current_instruction, 6, 6);
	const bool use_rm_upper =				util::extract_bits<bool>(current_instruction, 5, 5);

	const bool is_halfword =				util::extract_bits<unsigned int>(current_instruction, 4, 7) == 0b1000;

	arm_multiply_instruction *instr = nullptr;

	if (is_halfword)
		instr = new arm_multiply_instruction(reg_dest, reg_acc, reg_rs, reg_rm, set_condition_codes, flag);
	else
		instr = new arm_multiply_instruction(reg_dest, reg_acc, reg_rs, reg_rm, use_rs_upper, use_rm_upper, set_condition_codes, flag);

	switch (opcode)
	{
	case arm_mul_opcode_type::mul:
		return new arm_mul(instr);
	case arm_mul_opcode_type::mla:
		return new arm_mla(instr);
	case arm_mul_opcode_type::umull:
		return new arm_umull(instr);
	case arm_mul_opcode_type::umlal:
		return new arm_umlal(instr);
	case arm_mul_opcode_type::smull:
		return new arm_smull(instr);
	case arm_mul_opcode_type::smlal:
		return new arm_smlal(instr);
	case arm_mul_opcode_type::smla:
		return new arm_smla(instr);
	case arm_mul_opcode_type::smlaw:
		if (use_rm_upper)
			return new arm_smulw(instr);
		return new arm_smlaw(instr);
	case arm_mul_opcode_type::smlal_xy:
		return new arm_smlal_xy(instr);
	case arm_mul_opcode_type::smul:
		return new arm_smul(instr);
	default:
		throw std::exception("invalid arm_mul_opcode");;
	}
}

instruction * arm_parser::parse_arm_psr(unsigned int current_instruction)
{
	const arm_instruction::condition_flag flag =	util::extract_bits<arm_instruction::condition_flag>(current_instruction, 28, 31);
	const bool is_immediate =						util::extract_bits<bool>(current_instruction, 25, 25);
	const bool is_msr =								util::extract_bits<bool>(current_instruction, 21, 21);
	const bool use_spsr =							util::extract_bits<bool>(current_instruction, 22, 22);
	const bool write_f =							util::extract_bits<bool>(current_instruction, 19, 19);
	const bool write_s =							util::extract_bits<bool>(current_instruction, 18, 18);
	const bool write_x =							util::extract_bits<bool>(current_instruction, 17, 17);
	const bool write_c =							util::extract_bits<bool>(current_instruction, 16, 16);
	const cpu::cpu_register_id reg_src =			util::extract_bits<cpu::cpu_register_id>(current_instruction, 0, 3);
	const cpu::cpu_register_id reg_dest =			util::extract_bits<cpu::cpu_register_id>(current_instruction, 12, 15);
	const int shift_amount =						util::extract_bits<int>(current_instruction, 8, 11);
	const unsigned char immediate =					util::extract_bits<unsigned char>(current_instruction, 0, 7);

	if (is_msr) {
		if (is_immediate)
			return new arm_msr(use_spsr, write_f, write_s, write_x, write_s, shift_amount, immediate, flag);
		return new arm_msr(use_spsr, write_f, write_s, write_x, write_c, reg_src, flag);
	}
	return new arm_mrs(use_spsr, reg_dest, flag);
}

instruction * arm_parser::parse_arm_swap(unsigned int current_instruction)
{
	const arm_instruction::condition_flag flag =	util::extract_bits<arm_instruction::condition_flag>(current_instruction, 28, 31);
	const bool swap_byte =							util::extract_bits<bool>(current_instruction, 22, 22);
	const cpu::cpu_register_id reg_base =			util::extract_bits<cpu::cpu_register_id>(current_instruction, 16, 19);
	const cpu::cpu_register_id reg_dest =			util::extract_bits<cpu::cpu_register_id>(current_instruction, 12, 15);
	const cpu::cpu_register_id reg_src =			util::extract_bits<cpu::cpu_register_id>(current_instruction, 0, 3);

	return new arm_swp(swap_byte, reg_base, reg_dest, reg_src, flag);
}

instruction * arm_parser::parse_arm_single_data_transfer(unsigned int current_instruction)
{
	const arm_instruction::condition_flag flag =		util::extract_bits<arm_instruction::condition_flag>(current_instruction, 28, 31);
	const bool is_shifted_register =					util::extract_bits<bool>(current_instruction, 25, 25);
	const bool is_ldr =									util::extract_bits<bool>(current_instruction, 20, 20);
	const bool is_pre_indexing =						util::extract_bits<bool>(current_instruction, 24, 24);
	const bool add_to_base =							util::extract_bits<bool>(current_instruction, 23, 23);
	const bool transfer_byte =							util::extract_bits<bool>(current_instruction, 22, 22);
	const bool param =									util::extract_bits<bool>(current_instruction, 21, 21);
	const cpu::cpu_register_id reg_base =				util::extract_bits<cpu::cpu_register_id>(current_instruction, 16, 19);
	const cpu::cpu_register_id reg_dest =				util::extract_bits<cpu::cpu_register_id>(current_instruction, 12, 15);
	const cpu::cpu_register_id reg_offset =				util::extract_bits<cpu::cpu_register_id>(current_instruction, 0, 3);
	const int shift_amount =							util::extract_bits<int>(current_instruction, 7, 11);
	const arm_globals::arm_shift_type shift_type =		util::extract_bits<arm_globals::arm_shift_type>(current_instruction, 5, 6);
	const int immediate_offset =						util::extract_bits<int>(current_instruction, 0, 11);

	arm_single_data_transfer_instruction *instr = nullptr;
	if (!is_shifted_register)
		instr = new arm_single_data_transfer_instruction(is_pre_indexing, add_to_base, transfer_byte, param, reg_base, reg_dest, immediate_offset, flag);
	else
		instr = new arm_single_data_transfer_instruction(is_pre_indexing, add_to_base, transfer_byte, param, reg_base, reg_dest, shift_amount, shift_type, reg_offset, flag);

	if (is_ldr)
		return new arm_ldr(instr);
	return new arm_str(instr);
}

instruction * arm_parser::parse_arm_half_double_signed_transfer(unsigned int current_instruction)
{
	const arm_instruction::condition_flag flag =	util::extract_bits<arm_instruction::condition_flag>(current_instruction, 28, 31);
	const bool is_immediate_offset =				util::extract_bits<bool>(current_instruction, 22, 22);
	const bool is_pre_indexing =					util::extract_bits<bool>(current_instruction, 24, 24);
	const bool add_to_base =						util::extract_bits<bool>(current_instruction, 23, 23);
	const bool param =								util::extract_bits<bool>(current_instruction, 21, 21);
	const bool load_from_memory =					util::extract_bits<bool>(current_instruction, 20, 20);

	const cpu::cpu_register_id reg_base =			util::extract_bits<cpu::cpu_register_id>(current_instruction, 16, 19);
	const cpu::cpu_register_id reg_dest =			util::extract_bits<cpu::cpu_register_id>(current_instruction, 12, 15);
	const cpu::cpu_register_id reg_offset =			util::extract_bits<cpu::cpu_register_id>(current_instruction, 0, 3);
	const int immediate_offset =				   (util::extract_bits<int>(current_instruction, 8, 11) << 4 ) | util::extract_bits<int>(current_instruction, 0, 3);

	const arm_half_double_signed_transfer_load_opcode_type opcode_load =	util::extract_bits<arm_half_double_signed_transfer_load_opcode_type>(current_instruction, 5, 6);
	const arm_half_double_signed_transfer_store_opcode_type opcode_store =	util::extract_bits<arm_half_double_signed_transfer_store_opcode_type>(current_instruction, 5, 6);

	arm_half_double_signed_transfer_instruction *instr = nullptr;
	if (is_immediate_offset)
		instr = new arm_half_double_signed_transfer_instruction(is_pre_indexing, add_to_base, param, load_from_memory, reg_base, reg_dest, immediate_offset, flag);
	else
		instr = new arm_half_double_signed_transfer_instruction(is_pre_indexing, add_to_base, param, load_from_memory, reg_base, reg_dest, reg_offset, flag);

	if (load_from_memory)
	{
		switch (opcode_store)
		{
		case arm_half_double_signed_transfer_store_opcode_type::a_str_h: 
			return new arm_str_h(instr);
		case arm_half_double_signed_transfer_store_opcode_type::a_ldr_d:
			return new arm_ldr_d(instr);
		case arm_half_double_signed_transfer_store_opcode_type::a_str_d:
			return new arm_str_d(instr);
		default:;
		}
	}
	else
	{
		switch (opcode_load)
		{
		case arm_half_double_signed_transfer_load_opcode_type::a_ldr_h:
			return new arm_ldr_h(instr);
		case arm_half_double_signed_transfer_load_opcode_type::a_ldr_sb:
			return new arm_ldr_sb(instr);
		case arm_half_double_signed_transfer_load_opcode_type::a_ldr_sh:
			return new arm_ldr_sh(instr);
		default: ;
		}
	}
	return nullptr;
}

instruction * arm_parser::parse_arm_block_data_transfer(unsigned int current_instruction)
{
	const arm_instruction::condition_flag flag =	util::extract_bits<arm_instruction::condition_flag>(current_instruction, 28, 31);
	const bool is_pre_indexing =					util::extract_bits<bool>(current_instruction, 24, 24);
	const bool add_to_base =						util::extract_bits<bool>(current_instruction, 23, 23);
	const bool load_psr =							util::extract_bits<bool>(current_instruction, 22, 22);
	const bool write_into_base =					util::extract_bits<bool>(current_instruction, 21, 21);
	const bool is_ldm =								util::extract_bits<bool>(current_instruction, 20, 20);
	const cpu::cpu_register_id reg_base =			util::extract_bits<cpu::cpu_register_id>(current_instruction, 16, 19);
	const unsigned int register_list =				util::extract_bits<unsigned int>(current_instruction, 0, 15);

	arm_block_data_transfer_instruction *instr = new arm_block_data_transfer_instruction(is_pre_indexing, add_to_base, load_psr, write_into_base, reg_base, register_list, flag);

	if (is_ldm)
		return new arm_ldm(instr);
	return new arm_stm(instr);
}

instruction * arm_parser::parse_arm_coprocessor_register_transfer(unsigned int current_instruction)
{
	const arm_instruction::condition_flag flag =	util::extract_bits<arm_instruction::condition_flag>(current_instruction, 28, 31);
	const unsigned int coproc_opcode =				util::extract_bits<unsigned int>(current_instruction, 21, 23);
	const bool is_mrc =								util::extract_bits<bool>(current_instruction, 20, 20);
	const cpu::cpu_register_id cp_source_reg =		util::extract_bits<cpu::cpu_register_id>(current_instruction, 16, 19);
	const cpu::cpu_register_id arm_source_reg =		util::extract_bits<cpu::cpu_register_id>(current_instruction, 12, 15);
	const unsigned int coproc_number =				util::extract_bits<unsigned int>(current_instruction, 8, 11);
	const unsigned int coproc_information =			util::extract_bits<unsigned int>(current_instruction, 5, 7);
	const cpu::cpu_register_id cp_operand_reg =		util::extract_bits<cpu::cpu_register_id>(current_instruction, 0, 3);

	arm_coprocessor_register_transfer_instruction *instr = new arm_coprocessor_register_transfer_instruction(coproc_opcode, cp_source_reg, arm_source_reg, coproc_number, coproc_information, cp_operand_reg, flag);

	if (is_mrc)
		return new arm_mrc(instr);
	return new arm_mcr(instr);
}

instruction * arm_parser::parse_arm_coprocessor_data_transfer(unsigned int current_instruction)
{
	const arm_instruction::condition_flag flag =	util::extract_bits<arm_instruction::condition_flag>(current_instruction, 28, 31);
	const bool is_pre_indexing =					util::extract_bits<bool>(current_instruction, 24, 24);
	const bool add_to_base =						util::extract_bits<bool>(current_instruction, 23, 23);
	const bool transfer_length =					util::extract_bits<bool>(current_instruction, 22, 22);
	const bool address_into_base =					util::extract_bits<bool>(current_instruction, 21, 21);
	const bool is_ldc =								util::extract_bits<bool>(current_instruction, 20, 20);
	const cpu::cpu_register_id arm_base_reg =		util::extract_bits<cpu::cpu_register_id>(current_instruction, 16, 19);
	const cpu::cpu_register_id cp_src_reg =			util::extract_bits<cpu::cpu_register_id>(current_instruction, 12, 15);
	const unsigned int coproc_number =				util::extract_bits<unsigned int>(current_instruction, 8, 11);
	const unsigned char immediate =					util::extract_bits<unsigned char>(current_instruction, 0, 7);

	arm_coprocessor_data_transfer_instruction *instr = new arm_coprocessor_data_transfer_instruction(is_pre_indexing, add_to_base, transfer_length, address_into_base, arm_base_reg, cp_src_reg, coproc_number, immediate, flag);

	if (is_ldc)
		return new arm_ldc(instr);
	return new arm_stc(instr);
}

instruction * arm_parser::parse_arm_coprocessor_data_operations(unsigned int current_instruction)
{
	const arm_instruction::condition_flag flag =	util::extract_bits<arm_instruction::condition_flag>(current_instruction, 28, 31);
	const unsigned int cp_operation_code =			util::extract_bits<unsigned int>(current_instruction, 20, 23);
	const cpu::cpu_register_id cp_operand_reg_1 =	util::extract_bits<cpu::cpu_register_id>(current_instruction, 16, 19);
	const cpu::cpu_register_id cp_dest_reg =		util::extract_bits<cpu::cpu_register_id>(current_instruction, 12, 15);
	const unsigned int coprocessor_number =			util::extract_bits<unsigned int>(current_instruction, 8, 11);
	const unsigned int coprocessor_information =	util::extract_bits<unsigned int>(current_instruction, 5, 7);
	const cpu::cpu_register_id cp_operand_reg_2 =	util::extract_bits<cpu::cpu_register_id>(current_instruction, 0, 3);

	return new arm_cdp(cp_operation_code, cp_operand_reg_1, cp_dest_reg, coprocessor_number, coprocessor_information, cp_operand_reg_2, flag);
}
