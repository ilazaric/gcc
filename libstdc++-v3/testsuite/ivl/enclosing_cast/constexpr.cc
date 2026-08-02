// { dg-do compile { target c++26 } }

#include <enclosing_cast>

#ifndef __cpp_lib_enclosing_cast
# error "missing __cpp_lib_enclosing_cast"
#endif

struct S {
  int x;
  int y;
  mutable int z;
  const int w;
  volatile int u;
};

consteval bool test_1() {
  S s{1, 2};
  S& sx = std::enclosing_cast<&S::x>(s.x);
  S& sy = std::enclosing_cast<&S::y>(s.y);
  return (&s == &sx) && (&s == &sy);
}

static_assert(test_1());

template<auto P, typename T>
using enc = decltype(std::enclosing_cast<P>(std::declval<T>()));

static_assert(std::is_same_v<S&, enc<&S::y, int&>>);
static_assert(std::is_same_v<S&&, enc<&S::y, int&&>>);
static_assert(std::is_same_v<const S&, enc<&S::y, const int&>>);
static_assert(std::is_same_v<const S&&, enc<&S::y, const int&&>>);
static_assert(std::is_same_v<volatile S&, enc<&S::y, volatile int&>>);
static_assert(std::is_same_v<volatile S&&, enc<&S::y, volatile int&&>>);
static_assert(std::is_same_v<const volatile S&, enc<&S::y, const volatile int&>>);
static_assert(std::is_same_v<const volatile S&&, enc<&S::y, const volatile int&&>>);

static_assert(std::is_same_v<S&, enc<&S::z, int&>>);
static_assert(std::is_same_v<S&&, enc<&S::z, int&&>>);
static_assert(std::is_same_v<const S&, enc<&S::z, const int&>>);
static_assert(std::is_same_v<const S&&, enc<&S::z, const int&&>>);
static_assert(std::is_same_v<volatile S&, enc<&S::z, volatile int&>>);
static_assert(std::is_same_v<volatile S&&, enc<&S::z, volatile int&&>>);
static_assert(std::is_same_v<const volatile S&, enc<&S::z, const volatile int&>>);
static_assert(std::is_same_v<const volatile S&&, enc<&S::z, const volatile int&&>>);

static_assert(std::is_same_v<S&, enc<&S::w, int&>>);
static_assert(std::is_same_v<S&&, enc<&S::w, int&&>>);
static_assert(std::is_same_v<const S&, enc<&S::w, const int&>>);
static_assert(std::is_same_v<const S&&, enc<&S::w, const int&&>>);
static_assert(std::is_same_v<volatile S&, enc<&S::w, volatile int&>>);
static_assert(std::is_same_v<volatile S&&, enc<&S::w, volatile int&&>>);
static_assert(std::is_same_v<const volatile S&, enc<&S::w, const volatile int&>>);
static_assert(std::is_same_v<const volatile S&&, enc<&S::w, const volatile int&&>>);

static_assert(std::is_same_v<S&, enc<&S::u, int&>>);
static_assert(std::is_same_v<S&&, enc<&S::u, int&&>>);
static_assert(std::is_same_v<const S&, enc<&S::u, const int&>>);
static_assert(std::is_same_v<const S&&, enc<&S::u, const int&&>>);
static_assert(std::is_same_v<volatile S&, enc<&S::u, volatile int&>>);
static_assert(std::is_same_v<volatile S&&, enc<&S::u, volatile int&&>>);
static_assert(std::is_same_v<const volatile S&, enc<&S::u, const volatile int&>>);
static_assert(std::is_same_v<const volatile S&&, enc<&S::u, const volatile int&&>>);


struct A {
  int x;
  int y;
};

struct B {
  int z;
  int w;
};

struct AB : A, B {};

constexpr AB ab{};

static_assert(&std::enclosing_cast<&AB::z>(ab.z) == static_cast<const B*>(&ab));
