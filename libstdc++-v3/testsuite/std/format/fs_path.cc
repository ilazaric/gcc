// { dg-do run { target c++26 } }

#include <filesystem>
#include <format>
#include <testsuite_hooks.h>

using std::filesystem::path;

template<typename... Args>
bool
is_format_string_for(const char* str, Args&&... args)
{
  try {
    (void) std::vformat(str, std::make_format_args(args...));
    return true;
  } catch (const std::format_error&) {
    return false;
  }
}

template<typename... Args>
bool
is_format_string_for(const wchar_t* str, Args&&... args)
{
  try {
    (void) std::vformat(str, std::make_wformat_args(args...));
    return true;
  } catch (const std::format_error&) {
    return false;
  }
}

void
test_format_spec()
{
  // [fs.path.fmtr.funcs]
  // \nontermdef{path-format-spec}\br
  //     \opt{fill-and-align} \opt{width} \opt{\terminal{?}} \opt{\terminal{g}}
  path p;
  VERIFY( is_format_string_for("{}", p) );
  VERIFY( is_format_string_for("{:}", p) );
  VERIFY( is_format_string_for("{:?}", p) );
  VERIFY( is_format_string_for("{:g}", p) );
  VERIFY( is_format_string_for("{:?g}", p) );
  VERIFY( is_format_string_for("{:?g}", p) );
  VERIFY( is_format_string_for("{:F^32?g}", p) );
  VERIFY( is_format_string_for("{:G<{}?g}", p, 32) );

  VERIFY( ! is_format_string_for("{:g?}", p) );
}

void
test_format_path()
{
  VERIFY(std::format("{}", path("/usr/include")) == "/usr/include");
  VERIFY(std::format("{:.<10}", path("foo/bar")) == "foo/bar...");
  VERIFY(std::format("{}", path("/path/with/new\nline")) == "/path/with/new\nline");
  VERIFY(std::format("{:?}", path("multi\nline")) == "\"multi\\nline\"");
  VERIFY(std::format("{:g}", path("multi\nline")) == "multi\nline");
  VERIFY(std::format("{:?g}", path("multi\nline")) == "\"multi\\nline\"");
  VERIFY(std::format(L"{}", path(L"\u0428\u0447\u0443\u0447\u044B\u043D\u0448\u0447\u044B\u043D\u0430")) == L"\u0428\u0447\u0443\u0447\u044B\u043D\u0448\u0447\u044B\u043D\u0430");

  if constexpr (path::preferred_separator == L'\\')
  {
    VERIFY( std::format("{}", path("C:\\foo\\bar")) == "C:\\foo\\bar" );
    VERIFY( std::format("{:g}", path("C:\\foo\\bar")) == "C:/foo/bar" );
  }
}

int main()
{
  test_format_spec();
  test_format_path();
}
