// { dg-do run { target c++20 } }

#if __cplusplus >= 202400L
# define constexpr26 constexpr
#else
# define constexpr26
#endif

#include <format>
#include <string>
#include <testsuite_hooks.h>

constexpr26 void
test()
{
  auto n = std::formatted_size("");
  static_assert( std::is_same_v<std::size_t, decltype(n)> );
  VERIFY( n == 0 );

  n = std::formatted_size("abc");
  VERIFY( n == 3 );

  n = std::formatted_size("{{abc}}");
  VERIFY( n == 5 );

  n = std::formatted_size("{{{}}}", 1);
  VERIFY( n == 3 );

  n = std::formatted_size("{{{}}}", "abc");
  VERIFY( n == 5 );
}

void
test_wchar()
{
  auto n = std::formatted_size(L"");
  static_assert( std::is_same_v<std::size_t, decltype(n)> );
  VERIFY( n == 0 );

  n = std::formatted_size(L"abc");
  VERIFY( n == 3 );

  n = std::formatted_size(L"{{abc}}");
  VERIFY( n == 5 );

  n = std::formatted_size(L"{{{}}}", 1);
  VERIFY( n == 3 );

  n = std::formatted_size(L"{{{}}}", L"abc");
  VERIFY( n == 5 );
}

constexpr26 bool
test_all()
{
  test();
  if (!std::is_constant_evaluated())
    test_wchar();
  return true;
}

#if __cplusplus >= 202400L
static_assert(test_all());
#endif

int main()
{
  test_all();
}
