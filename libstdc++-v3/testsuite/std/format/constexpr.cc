// { dg-do compile { target c++26 } }

#include <format>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>
#include <testsuite_hooks.h>

constexpr void
test_format()
{
  using namespace std;
  string res;

  res = format("{}", 'c');
  VERIFY( res == "c" );
  res = format("{1} {0} {0}", 'a', 'b');
  VERIFY( res == "b a a" );
  res = format("{:?}", '\n');
  VERIFY( res == "'\\n'" );
  res = format("{:.^10}", "hello");
  VERIFY( res == "..hello..." );
  res = format("{:.>{}}", "world", 8);
  VERIFY( res == "...world" );
  res = format("{:+#06X}", 0xa);
  VERIFY( res == "+0X00A" );
  res = format("{:p}", nullptr);
  VERIFY( res == "0x0" );
  res = format("{:07P}", nullptr);
  VERIFY( res == "0X00000" );
  res = format("{} {}", true, false);
  VERIFY( res == "true false" );
  res = format("{:+#06b}", true);
  VERIFY( res == "+0b001" );
  res = format("{} {} {} {}", "abc", +"def", string_view("ghi"), string("jkl"));
  VERIFY( res == "abc def ghi jkl" );
  res = format("{:?}", "hello\nworld");
  VERIFY( res == "\"hello\\nworld\"" );
  res = format("{}", tuple(1, true));
  VERIFY( res == "(1, true)" );
  res = format("{:t<12m}", tuple('a', "bc"));
  VERIFY( res == "'a': \"bc\"ttt" );
  res = format("{:n}", tuple(nullptr, -1, 1));
  VERIFY( res == "0x0, -1, 1" );
  res = format("{}", vector{1, 2, 3, 4});
  VERIFY( res == "[1, 2, 3, 4]" );
  res = format("{:?s}", vector{'a', '\n', 'b'});
  VERIFY( res == "\"a\\nb\"" );
  res = format("{:n:+}", vector{1, 2, 3});
  VERIFY( res == "+1, +2, +3" );
}

constexpr void
test_format_to()
{
  using namespace std;
  char buf[100];
  char* out;

  out = format_to(buf, "{:.^5}", "foo");
  VERIFY( string_view(buf, out) == ".foo." );
  out = format_to(buf, "{} {}", nullptr, true);
  VERIFY( string_view(buf, out) == "0x0 true" );
}

constexpr void
test_vformat()
{
  using namespace std;
  string res;

  int arg1 = 1;
  char arg2 = 'a';
  bool arg3 = true;
  res = vformat("{} {:?} {}", make_format_args(arg1, arg2, arg3));
  VERIFY( res == "1 'a' true" );
}

constexpr void
test_vformat_to()
{
  using namespace std;
  char buf[100];
  char* out;

  nullptr_t arg1 = nullptr;
  string arg2 = "foo";
  tuple<int, int> arg3{-3, 5};
  out = vformat_to(buf, "{} {:?} {}", make_format_args(arg1, arg2, arg3));
  VERIFY( string_view(buf, out) == "0x0 \"foo\" (-3, 5)" );
}

constexpr void
test_format_to_n()
{
  using namespace std;
  char buf[100];
  format_to_n_result<char*> out;
  int n;

  n = 100;
  out = format_to_n(buf, n, "{:+} {:?} {}", 1, "\n\n", vector{1, 2, 3});
  VERIFY( out.size <= n );
  VERIFY( out.out - buf == out.size );
  VERIFY( string_view(buf, out.size) == "+1 \"\\n\\n\" [1, 2, 3]" );
  n = 12;
  out = format_to_n(buf, n, "{} {} {}", true, nullptr, "long string");
  VERIFY( out.size > n );
  VERIFY( out.out - buf == n );
  VERIFY( string_view(buf, out.out) == "true 0x0 lon" );
}

constexpr bool
all_tests()
{
  test_format();
  test_format_to();
  test_vformat();
  test_vformat_to();
  test_format_to_n();

  return true;
}

static_assert(all_tests());
