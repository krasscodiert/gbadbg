#include "thumb_multiple_ld_st.h"

void thumb_multiple_ld_st_ldmia::run(gba_context * gba_)
{
}

instruction_string thumb_multiple_ld_st_ldmia::print()
{
	auto return_vec = instruction_string("LDMIA");
	return_vec.add(expression(this->offset_reg));
	return_vec.add(expression(this->r_list));

	return return_vec;
}
