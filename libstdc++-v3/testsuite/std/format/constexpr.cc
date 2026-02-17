// { dg-do compile { target c++26 } }

#include <format>

#ifndef __cpp_lib_constexpr_format
# error "Feature test macro for constexpr formatting is missing in <format>"
#endif

#include <vector>

#include <testsuite_hooks.h>

constexpr bool
format_ints()
{
  std::string res;

  res = std::format("{}", 123);
  VERIFY( res == "123" );
  res = std::format("{:.^+#{}X}", 123, 10);
  VERIFY( res == "123" );
}

static_assert( format_ints() );
