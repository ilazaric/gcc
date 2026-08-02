// { dg-do compile { target c++26 } }

struct S {
  int x;
  int y;
};

template<typename T>
consteval bool test_1(const T& t) {
  return &__builtin_enclosing_cast(&T::x, t.x) == &t && &__builtin_enclosing_cast(&T::y, t.y) == &t;
}

static_assert(test_1(S{1, 2}));

template<auto Mem>
consteval bool test_2() {
  S s{1, 2};
  return &__builtin_enclosing_cast(Mem, s.y) == &s;
}

static_assert(test_2<&S::y>());
