// { dg-do compile { target c++26 } }

#include <type_traits>

struct S {
  int x;
  char y;
};

constexpr S s{42, 'a'};

constexpr const int& x = s.x;
constexpr auto memx = &S::x;
constexpr const S& srx = __builtin_enclosing_cast(memx, x);
static_assert(srx.x == 42);
static_assert(&srx == &s);

constexpr const char& y = s.y;
constexpr auto memy = &S::y;
constexpr const S& sry = __builtin_enclosing_cast(memy, y);
static_assert(sry.y == 'a');
static_assert(&sry == &s);

template<typename Arg>
using enc_type = decltype(__builtin_enclosing_cast(&S::x, std::declval<Arg>()));

static_assert(std::is_same_v<S&, enc_type<int&>>);
static_assert(std::is_same_v<S&&, enc_type<int&&>>);
static_assert(std::is_same_v<const S&, enc_type<const int&>>);
static_assert(std::is_same_v<const S&&, enc_type<const int&&>>);
static_assert(std::is_same_v<volatile S&, enc_type<volatile int&>>);
static_assert(std::is_same_v<volatile S&&, enc_type<volatile int&&>>);
static_assert(std::is_same_v<volatile const S&, enc_type<volatile const int&>>);
static_assert(std::is_same_v<volatile const S&&, enc_type<volatile const int&&>>);

consteval bool test_1() {
  S s{1, 'z'};
  int& x = s.x;
  char& y = s.y;
  auto&& sx = __builtin_enclosing_cast(&S::x, x);
  auto&& sy = __builtin_enclosing_cast(&S::y, static_cast<char&&>(y));
  static_assert(std::is_same_v<decltype(sx), S&>);
  static_assert(std::is_same_v<decltype(sy), S&&>);
  return (&sx == &s) && (&sy == &s);
}

static_assert(test_1());

struct T {
  const long x;
  mutable short y;
};

template<typename A>
consteval bool test_2() {
  A t{3, 4};
  auto&& tx = __builtin_enclosing_cast(&T::x, t.x);
  auto&& ty = __builtin_enclosing_cast(&T::y, t.y);
  static_assert(std::is_same_v<decltype(tx), const T&>);
  static_assert(std::is_same_v<decltype(ty), T&>);
  return (&tx == &t) && (&ty == &t);
}

static_assert(test_2<T>());
static_assert(test_2<const T>());

S global{4,5};
constexpr S* global_ptr = &__builtin_enclosing_cast(&S::y, global.y);
static_assert(global_ptr == &global);

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

static_assert(&__builtin_enclosing_cast(&AB::z, ab.z) == static_cast<const B*>(&ab));
