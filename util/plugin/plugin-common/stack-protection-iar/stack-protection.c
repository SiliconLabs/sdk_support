//#include "base/hal/micro/random.h"
#include PLATFORM_HEADER
#include CONFIGURATION_HEADER
void __init_stack_chk_guard(void);

/*
 * This variable holds the value that the canary will be initialized with
 * and also compared with before returning from the function.
 */
uint32_t __stack_chk_guard = 6571;//halCommonGetRandom();

/*
 * The __stack_chk_fail(void) function is called when a modified canary is detected.
 */
__attribute__((noreturn)) void __stack_chk_fail(void)
{
  /*
     LogStackSmashed();
   */
  assert(false);
}

/*
 * This function should called at startup as part of construction of static C++ objects
 * and is a way to programatically initialize the __stack_chk_guard when the system starts.
 */

__attribute__((constructor)) void __init_stack_chk_guard(void)
{
  __stack_chk_guard = 4711;//halCommonGetRandom();
}
