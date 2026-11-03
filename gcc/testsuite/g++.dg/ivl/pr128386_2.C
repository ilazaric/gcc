// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -fsanitize=undefined" }

void foo() {
  static constexpr auto x = ^^int;
}
