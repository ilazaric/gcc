// { dg-do compile { target c++26 } }

struct S { int x; };

struct T : S {};

constexpr T t{};

constexpr auto&& ref = __builtin_enclosing_cast(static_cast<int T::*>(&T::x), t.x);

static_assert(&ref == &t);

