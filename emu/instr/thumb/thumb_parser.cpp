#include "thumb_parser.h"
#include "util.h"
#include "thumb_add_offset_relative.h"
#include "thumb_add_offset_sp.h"
#include "thumb_add_sub.h"
#include "thumb_alu.h"
#include "thumb_conditional_branch.h"
#include "thumb_hireg_bx.h"
#include "thumb_immediate.h"
#include "thumb_ldr_pc.h"
#include "thumb_ldr_str.h"
#include "thumb_ldr_str_byte_half.h"
#include "thumb_ldr_str_half.h"
#include "thumb_ldr_str_immediate.h"
#include "thumb_ldr_str_sp.h"
#include "thumb_long_branch_link.h"
#include "thumb_multiple_ld_st.h"
#include "thumb_push_pop.h"
#include "thumb_shift.h"
#include "thumb_software_interrupt.h"
#include "thumb_unconditional_branch.h"

instruction * thumb_parser::parse_thumb_shift(unsigned int current_instruction) // 1
{
	const thumb_shift_opcode_type opcode = util::extract_bits<thumb_shift_opcode_type>(current_instruction, 12, 11);
	const unsigned int offset = util::extract_bits<unsigned int>(current_instruction, 10, 6);
	const cpu::cpu_register_id src_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 5, 3);
	const cpu::cpu_register_id dest_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 2, 0);

	auto instruction = new thumb_shift_instruction(offset, src_reg, dest_reg);

	switch (opcode)
	{
	case thumb_shift_opcode_type::t_lsl: 
		return new thumb_shift_lsl(instruction);
	case thumb_shift_opcode_type::t_lsr: 
		return new thumb_shift_lsr(instruction);
	case thumb_shift_opcode_type::t_asr: 
		return new thumb_shift_asr(instruction);
	default:
		throw std::exception("invalid thumb_shift_opcode");
	}
}

instruction * thumb_parser::parse_thumb_add_sub(unsigned int current_instruction) // 2
{
	const thumb_add_sub_opcode_type opcode = util::extract_bits<thumb_add_sub_opcode_type>(current_instruction, 10, 9);
	const unsigned int offset = util::extract_bits<unsigned int>(current_instruction, 8, 6);
	const cpu::cpu_register_id reg = static_cast<cpu::cpu_register_id>(offset);
	const cpu::cpu_register_id src_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 5, 3);
	const cpu::cpu_register_id dest_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 2, 0);

	switch (opcode)
	{
	case thumb_add_sub_opcode_type::t_add_reg: 
		return new thumb_add_sub_add_reg(
			new thumb_add_sub_instruction(reg, src_reg, dest_reg)
		);
	case thumb_add_sub_opcode_type::t_sub_reg: 
		return new thumb_add_sub_sub_reg(
			new thumb_add_sub_instruction(reg, src_reg, dest_reg)
		);
	case thumb_add_sub_opcode_type::t_add_imm: 
		return new thumb_add_sub_add_imm(
			new thumb_add_sub_instruction(offset, src_reg, dest_reg)
		);
	case thumb_add_sub_opcode_type::t_sub_imm:
		return new thumb_add_sub_sub_imm(
			new thumb_add_sub_instruction(offset, src_reg, dest_reg)
		);
	default: 
		throw std::exception("invalid thumb_add_sub_opcode");
	}
}

instruction * thumb_parser::parse_thumb_immediate(unsigned int current_instruction) // 3
{
	const thumb_immediate_opcode_type opcode = util::extract_bits<thumb_immediate_opcode_type>(current_instruction, 12, 11);
	const cpu::cpu_register_id dest_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 10, 8);
	const unsigned int unsigned_imm = util::extract_bits<unsigned int>(current_instruction, 7, 0);

	auto instruction = new thumb_immediate_instruction(unsigned_imm, dest_reg);

	switch (opcode)
	{
	case thumb_immediate_opcode_type::t_mov: 
		return new thumb_immediate_mov(instruction);
	case thumb_immediate_opcode_type::t_cmp: 
		return new thumb_immediate_cmp(instruction);
	case thumb_immediate_opcode_type::t_add: 
		return new thumb_immediate_add(instruction);
	case thumb_immediate_opcode_type::t_sub: 
		return new thumb_immediate_sub(instruction);
	default:
		throw std::exception("invalid thumb_immediate_opcode");
	}
}

instruction * thumb_parser::parse_thumb_alu(unsigned int current_instruction) // 4
{
	const thumb_alu_opcode_type opcode = util::extract_bits<thumb_alu_opcode_type>(current_instruction, 9, 6);
	const cpu::cpu_register_id src_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 5, 3);
	const cpu::cpu_register_id dest_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 2, 0);

	auto instruction = new thumb_alu_instruction(src_reg, dest_reg);

	switch (opcode)		 
	{
	case thumb_alu_opcode_type::t_and:
		return new thumb_alu_and(instruction);
	case thumb_alu_opcode_type::t_eor:
		return new thumb_alu_eor(instruction);
	case thumb_alu_opcode_type::t_lsl:
		return new thumb_alu_lsl(instruction);
	case thumb_alu_opcode_type::t_lsr:
		return new thumb_alu_lsr(instruction);
	case thumb_alu_opcode_type::t_asr:
		return new thumb_alu_asr(instruction);
	case thumb_alu_opcode_type::t_adc:
		return new thumb_alu_adc(instruction);
	case thumb_alu_opcode_type::t_sbc:
		return new thumb_alu_sbc(instruction);
	case thumb_alu_opcode_type::t_ror:
		return new thumb_alu_ror(instruction);
	case thumb_alu_opcode_type::t_tst:
		return new thumb_alu_tst(instruction);
	case thumb_alu_opcode_type::t_neg:
		return new thumb_alu_neg(instruction);
	case thumb_alu_opcode_type::t_cmp:
		return new thumb_alu_cmp(instruction);
	case thumb_alu_opcode_type::t_cmn:
		return new thumb_alu_cmn(instruction);
	case thumb_alu_opcode_type::t_orr:
		return new thumb_alu_orr(instruction);
	case thumb_alu_opcode_type::t_mul:
		return new thumb_alu_mul(instruction);
	case thumb_alu_opcode_type::t_bic:
		return new thumb_alu_bic(instruction);
	case thumb_alu_opcode_type::t_mvn:
		return new thumb_alu_mvn(instruction);
	default:
		throw std::exception("invalid thumb_alu_opcode");
	}
}

instruction * thumb_parser::parse_thumb_hireg_bx(unsigned int current_instruction) // 5
{
	const thumb_hireg_bx_opcode_type opcode = util::extract_bits<thumb_hireg_bx_opcode_type>(current_instruction, 9, 8);
	const bool msbd = util::is_bit_set(7, current_instruction);
	const bool msbs = util::is_bit_set(6, current_instruction);
	auto src_reg_temp = util::extract_bits<int>(current_instruction, 5, 3);
	auto dest_reg_temp = util::extract_bits<int>(current_instruction, 2, 0);

	cpu::cpu_register_id dest_reg;
	if (msbd)
	{
		dest_reg = static_cast<cpu::cpu_register_id>(dest_reg_temp + 8);
	}
	else
	{
		dest_reg = static_cast<cpu::cpu_register_id>(dest_reg_temp);
	}

	cpu::cpu_register_id src_reg;
	if (msbs)
	{
		src_reg = static_cast<cpu::cpu_register_id>(src_reg_temp + 8);
	}
	else
	{
		src_reg = static_cast<cpu::cpu_register_id>(src_reg_temp);
	}
	
	auto instruction = new thumb_hireg_bx_instruction(msbd, msbs, src_reg, dest_reg);

	switch (opcode) { 
		case thumb_hireg_bx_opcode_type::t_add: 
			return new thumb_hireg_bx_add(instruction);
		case thumb_hireg_bx_opcode_type::t_cmp: 
			return new thumb_hireg_bx_cmp(instruction);
		case thumb_hireg_bx_opcode_type::t_mov: 
			return new thumb_hireg_bx_mov(instruction);
		case thumb_hireg_bx_opcode_type::t_bx: 
			if (msbd)
				throw std::exception("BLX ARM 9 not supported");
			return new thumb_hireg_bx_bx(instruction);
		default: 
			throw std::exception("invalid thumb_hireg_bx_opcode");
	}
}

instruction * thumb_parser::parse_thumb_ldr_pc(unsigned int current_instruction) // 6
{
	const cpu::cpu_register_id dest_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 10, 8);
	const cpu::cpu_register_id offset = util::extract_bits<cpu::cpu_register_id>(current_instruction, 7, 0);

	return new thumb_ldr_pc_ldr(dest_reg, offset);
}

instruction * thumb_parser::parse_thumb_ldr_str(unsigned int current_instruction) // 7
{
	const thumb_ldr_str_opcode_type opcode = util::extract_bits<thumb_ldr_str_opcode_type>(current_instruction, 11, 10);
	const cpu::cpu_register_id off_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 8, 6);
	const cpu::cpu_register_id base_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 5, 3);
	const cpu::cpu_register_id src_dest_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 2, 0);

	auto instruction = new thumb_ldr_str_instruction(off_reg, base_reg, src_dest_reg);

	switch (opcode) {
	case thumb_ldr_str_opcode_type::t_str: 
		return new thumb_ldr_str_str(instruction);
	case thumb_ldr_str_opcode_type::t_strb: 
		return new thumb_ldr_str_strb(instruction);
	case thumb_ldr_str_opcode_type::t_ldr: 
		return new thumb_ldr_str_ldr(instruction);
	case thumb_ldr_str_opcode_type::t_ldrb: 
		return new thumb_ldr_str_ldrb(instruction);
	default:
		throw std::exception("invalid thumb_ldr_str");
	}
}

instruction * thumb_parser::parse_thumb_ldr_str_byte_half(unsigned int current_instruction) // 8
{
	const thumb_ldr_str_byte_half_opcode_type opcode = util::extract_bits<thumb_ldr_str_byte_half_opcode_type>(current_instruction, 11, 10);
	const cpu::cpu_register_id off_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 5, 3);
	const cpu::cpu_register_id base_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 2, 0);
	const cpu::cpu_register_id src_dest_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 2, 0);

	auto instruction = new thumb_ldr_str_byte_half_instruction(off_reg, base_reg, src_dest_reg);

	switch (opcode) {
	case thumb_ldr_str_byte_half_opcode_type::t_strh:
		return new thumb_ldr_str_byte_half_strh(instruction);
	case thumb_ldr_str_byte_half_opcode_type::t_ldsb:
		return new thumb_ldr_str_byte_half_ldsb(instruction);
	case thumb_ldr_str_byte_half_opcode_type::t_ldrh:
		return new thumb_ldr_str_byte_half_ldrh(instruction);
	case thumb_ldr_str_byte_half_opcode_type::t_ldsh:
		return new thumb_ldr_str_byte_half_ldsh(instruction);
	default:
		throw std::exception("invalid thumb_ldr_str_byte_half");
	}
}

instruction * thumb_parser::parse_thumb_ldr_str_immediate(unsigned int current_instruction) // 9
{
	const thumb_ldr_str_immediate_opcode_type opcode = util::extract_bits<thumb_ldr_str_immediate_opcode_type>(current_instruction, 12, 11);
	const unsigned int  off_reg = util::extract_bits<unsigned int>(current_instruction, 10, 6);
	const cpu::cpu_register_id base_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 5, 3);
	const cpu::cpu_register_id src_dest_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 2, 0);

	auto instruction = new thumb_ldr_str_immediate_instruction(off_reg, base_reg, src_dest_reg); 
		
		switch (opcode) {
		case thumb_ldr_str_immediate_opcode_type::t_str:											
			return new thumb_ldr_str_immediate_str(instruction);
		case thumb_ldr_str_immediate_opcode_type::t_ldr:
			return new thumb_ldr_str_immediate_ldr(instruction);
		case thumb_ldr_str_immediate_opcode_type::t_strb:
			return new thumb_ldr_str_immediate_strb(instruction);
		case thumb_ldr_str_immediate_opcode_type::t_ldrb:
			return new thumb_ldr_str_immediate_ldrb(instruction);
	default:
		throw std::exception("invalid thumb_ldr_str_immediate");
	}
}

instruction * thumb_parser::parse_thumb_ldr_str_half(unsigned int current_instruction) // 10 
{
	const thumb_ldr_str_half_opcode_type opcode = util::extract_bits<thumb_ldr_str_half_opcode_type>(current_instruction, 11, 11);
	const unsigned int off_reg = util::extract_bits<unsigned int>(current_instruction, 10, 6);
	const cpu::cpu_register_id base_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 5, 3);
	const cpu::cpu_register_id src_dest_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 2, 0);

	auto instruction = new thumb_ldr_str_half_instruction(off_reg, base_reg, src_dest_reg);

	switch (opcode) {
	case thumb_ldr_str_half_opcode_type::t_ldrh:
		return new thumb_ldr_str_half_ldrh(instruction);
	case thumb_ldr_str_half_opcode_type::t_strh:
		return new thumb_ldr_str_half_strh(instruction);
	default:
		throw std::exception("invalid thumb_ldr_str_half");
	}
}

instruction * thumb_parser::parse_thumb_ldr_str_sp(unsigned int current_instruction) // 11
{
	const thumb_ldr_str_sp_opcode_type opcode = util::extract_bits<thumb_ldr_str_sp_opcode_type>(current_instruction, 11, 11);
	const cpu::cpu_register_id src_dest_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 10, 8);
	const unsigned int off_reg = util::extract_bits<unsigned int>(current_instruction, 7, 0);

	auto instruction = new thumb_ldr_str_sp_instruction(src_dest_reg, off_reg);

	switch (opcode) {
	case thumb_ldr_str_sp_opcode_type::t_ldr:
		return new thumb_ldr_str_sp_ldr(instruction);
	case thumb_ldr_str_sp_opcode_type::t_str:
		return new thumb_ldr_str_sp_str(instruction);
	default:
		throw std::exception("invalid thumb_ldr_str_sp");
	}
}

instruction * thumb_parser::parse_thumb_add_offset_relative(unsigned int current_instruction) // 12
{
	const thumb_add_offset_relative_opcode_type opcode = util::extract_bits<thumb_add_offset_relative_opcode_type>(current_instruction, 11, 11);
	const cpu::cpu_register_id dest_reg = util::extract_bits<cpu::cpu_register_id>(current_instruction, 10, 8);
	const unsigned int offset = util::extract_bits<unsigned int>(current_instruction, 7, 0);

	auto instruction = new thumb_add_offset_relative_instruction(dest_reg, offset);

	switch (opcode) {
	case thumb_add_offset_relative_opcode_type::t_add_pc:
		return new thumb_add_offset_relative_add_pc(instruction);
	case thumb_add_offset_relative_opcode_type::t_add_sp:
		return new thumb_add_offset_relative_add_sp(instruction);
	default:
		throw std::exception("invalid thumb_add_offset_relative");
	}
}

instruction * thumb_parser::parse_thumb_add_offset_sp(unsigned int current_instruction) // 13 
{
	const thumb_add_offset_sp_opcode_type opcode = util::extract_bits<thumb_add_offset_sp_opcode_type>(current_instruction, 7, 7);
	const unsigned int offset = util::extract_bits<unsigned int>(current_instruction, 6, 0);

	auto instruction = new thumb_add_offset_sp_instruction(offset);

	switch (opcode) {
	case thumb_add_offset_sp_opcode_type::t_add_neg:
		return new thumb_add_offset_sp_add_neg(instruction);
	case thumb_add_offset_sp_opcode_type::t_add_pos:
		return new thumb_add_offset_sp_add_pos(instruction);
	default:
		throw std::exception("invalid thumb_add_offset_sp");
	}
}

instruction * thumb_parser::parse_thumb_push_pop(unsigned int current_instruction) // 14
{
	const thumb_push_pop_opcode_type opcode = util::extract_bits<thumb_push_pop_opcode_type>(current_instruction, 11, 11);
	const bool pc_lr = util::is_bit_set(8, current_instruction);
	const unsigned int rList = util::extract_bits<unsigned int>(current_instruction, 7, 0);

	auto instruction = new thumb_push_pop_instruction(pc_lr, rList);

	switch (opcode) {
	case thumb_push_pop_opcode_type::t_push:
		return new thumb_push_pop_push(instruction);
	case thumb_push_pop_opcode_type::t_pop:
		return new thumb_push_pop_pop(instruction);
	default:
		throw std::exception("invalid thumb_push_pop");
	}
}

instruction * thumb_parser::parse_thumb_multiple_ld_st(unsigned int current_instruction) // 15 
{
	const thumb_multiple_ld_st_opcode_type opcode = util::extract_bits<thumb_multiple_ld_st_opcode_type>(current_instruction, 11, 11);
	const cpu::cpu_register_id offset_ref = util::extract_bits<cpu::cpu_register_id>(current_instruction, 10, 8);
	std::vector<bool> r_list = arm_util::parse_register_list(current_instruction, 7, 0);

	auto instruction = new thumb_multiple_ld_st_instruction(offset_ref, r_list);

	switch (opcode) {
	case thumb_multiple_ld_st_opcode_type::t_ldmia:
		return new thumb_multiple_ld_st_ldmia(instruction);
	case thumb_multiple_ld_st_opcode_type::t_stmia:
		return new thumb_multiple_ld_st_stmia(instruction);
	default:
		throw std::exception("invalid thumb_multiple_ld_st");
	}
}

instruction * thumb_parser::parse_thumb_conditional_branch(unsigned int current_instruction) // 16 & 17
{
	const thumb_conditional_branch_opcode_type opcode = util::extract_bits<thumb_conditional_branch_opcode_type>(current_instruction, 11, 8);
	const signed char offset_ref = util::extract_bits<signed char>(current_instruction, 7, 0);

	auto instruction = new thumb_conditional_branch_instruction(offset_ref);

	switch (opcode) {
	case thumb_conditional_branch_opcode_type::t_beq: 
		return new thumb_conditional_branch_beq(instruction);
	case thumb_conditional_branch_opcode_type::t_bne: 
		return new thumb_conditional_branch_bne(instruction);
	case thumb_conditional_branch_opcode_type::t_bcs: 
		return new thumb_conditional_branch_bcs(instruction);
	case thumb_conditional_branch_opcode_type::t_bcc: 
		return new thumb_conditional_branch_bcc(instruction);
	case thumb_conditional_branch_opcode_type::t_bmi: 
		return new thumb_conditional_branch_bmi(instruction);
	case thumb_conditional_branch_opcode_type::t_bpl: 
		return new thumb_conditional_branch_bpl(instruction);
	case thumb_conditional_branch_opcode_type::t_bvs: 
		return new thumb_conditional_branch_bvs(instruction);
	case thumb_conditional_branch_opcode_type::t_bvc: 
		return new thumb_conditional_branch_bvc(instruction);
	case thumb_conditional_branch_opcode_type::t_bhi: 
		return new thumb_conditional_branch_bhi(instruction);
	case thumb_conditional_branch_opcode_type::t_bls: 
		return new thumb_conditional_branch_bls(instruction);
	case thumb_conditional_branch_opcode_type::t_bge: 
		return new thumb_conditional_branch_bge(instruction);
	case thumb_conditional_branch_opcode_type::t_blt: 
		return new thumb_conditional_branch_blt(instruction);
	case thumb_conditional_branch_opcode_type::t_bgt: 
		return new thumb_conditional_branch_bgt(instruction);
	case thumb_conditional_branch_opcode_type::t_ble: 
		return new thumb_conditional_branch_ble(instruction);
	case thumb_conditional_branch_opcode_type::swi:
		throw std::exception("wrong swi handling");
	default: 
		throw std::exception("invalid thumb_conditional_branch");
	}
}

instruction * thumb_parser::parse_thumb_software_interrupt(unsigned int current_instruction)
{
	const unsigned int comment = util::extract_bits<unsigned int>(current_instruction, 7, 0);
	return new thumb_software_interrupt(comment);
}

instruction * thumb_parser::parse_thumb_unconditional_branch(unsigned int current_instruction) // 18
{
	const int offset_ref = util::extract_bits<int>(current_instruction, 10, 0);
	return new thumb_unconditional_branch_b(offset_ref);
}

instruction * thumb_parser::parse_thumb_long_branch_link(unsigned int current_instruction) // 19
{
	const unsigned int upper_address = util::extract_bits<unsigned int>(current_instruction, 10, 0);
	return new thumb_long_branch_link_bl(upper_address);
}
