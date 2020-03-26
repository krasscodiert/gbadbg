#include "gmock/gmock.h"
#include "alu_helper.h"
//#include "../emu/alu_helper.h"

using namespace testing;

namespace testCMake::tests
{
    TEST(GbadbgTests, AluAndTest) {
        ASSERT_THAT(5, Eq(5));
    }
}
