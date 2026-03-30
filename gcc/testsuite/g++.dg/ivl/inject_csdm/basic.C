// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -fimplicit-constexpr" }

#include <meta>

consteval int count_members(std::meta::info type, std::string_view sv) {
  int ret = 0;
  for (auto mem : members_of(type, std::meta::access_context::unchecked()))
    if (display_string_of(mem).contains(sv))
      ++ret;
  return ret;
}

struct S {
  int fn();
  char mem;
};

consteval {
  ivl_inject_csdm(^^S, "csdm", std::meta::reflect_constant(123));
}

static_assert(S::csdm == 123);
static_assert(^^decltype(S::csdm) == ^^const int);
static_assert(parent_of(^^S::csdm) == ^^S);
static_assert(count_members(^^S, "csdm") == 1);

struct T {
private:
  int fn();
  char mem;
};

static_assert(count_members(^^T, "csdm") == 0);

consteval {
  sizeof(T);
  ivl_inject_csdm(^^T, "csdm1", std::meta::reflect_constant(&S::csdm));
}

// have to split these up into separate consteval blocks,
// otherwise it doesn't recognize T::csdm1, don't really care why
consteval {
  ivl_inject_csdm(^^T, "csdm2", std::meta::reflect_constant(&T::csdm1));
}

consteval {
  ivl_inject_csdm(^^T, "csdm3", std::meta::reflect_constant(&T::csdm2));
}

static_assert(T::csdm1 == &S::csdm);
static_assert(^^decltype(T::csdm1) == ^^const int*const);
static_assert(parent_of(^^T::csdm1) == ^^T);
static_assert(count_members(^^T, "csdm") == 3);

template<typename>
struct TT {};

consteval {
  sizeof(TT<int>);
  ivl_inject_csdm(^^TT<int>, "csdm", std::meta::reflect_constant(123));
}

static_assert(count_members(^^TT<int>, "csdm") == 1);

struct U {};

template<typename>
struct UU {
  consteval {
    ivl_inject_csdm(^^U, "csdm" + std::to_string(count_members(^^U, "csdm")), std::meta::reflect_constant(123));
  }
};

static_assert(sizeof(UU<int>) + sizeof(UU<char>) + sizeof(UU<float>) > 0);
static_assert(count_members(^^U, "csdm") == 3);

template<typename>
struct VV {
  struct V {};

  consteval {
    sizeof(V);
    ivl_inject_csdm(^^V, "csdm1", std::meta::reflect_constant(123));
    ivl_inject_csdm(^^V, "csdm2", std::meta::reflect_constant(123));
  }
};

static_assert(count_members(^^VV<int>::V, "csdm") == 2);

struct W1 {};
struct W2 : W1 {};
static_assert(count_members(^^W1, "csdm") == 0);
static_assert(count_members(^^W2, "csdm") == 0);

consteval {
  ivl_inject_csdm(^^W1, "csdm", std::meta::reflect_constant(123));
}

// spooky action at a distance
static_assert(W2::csdm == 123);
