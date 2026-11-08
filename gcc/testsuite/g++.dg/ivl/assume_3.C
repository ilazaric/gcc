/* { dg-do compile { target { x86_64-*-* } } } */
/* { dg-options "-O2 -march=x86-64 -std=c++26" } */
/* { dg-final { check-function-bodies "**" "" "" { target "*-*-*" } {^\t?\.}  } } */

/*
**_Z10get_stringB5cxx11RSt7variantIJ3foo3barEE:
**.LFB[0-9]+:
**	.cfi_startproc
**	movq	%rdi, %rax
**	ret
**	.cfi_endproc
**.LFE[0-9]+:
*/

#include <variant>
#include <string>

struct foo { std::string s; };
struct bar { std::string s; };

using var = std::variant<foo, bar>;

std::string& get_string(var& v) {
  [[assume(!v.valueless_by_exception())]];
  return std::visit([](auto& x) -> auto& { return x.s; }, v);
}
