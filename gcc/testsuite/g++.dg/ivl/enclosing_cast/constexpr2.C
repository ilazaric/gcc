// { dg-do compile { target c++26 } }

struct S {
  int a;
  int b;
  constexpr decltype(__builtin_enclosing_cast(&S::b, b)) self() {
    return __builtin_enclosing_cast(&S::b, b);
  }
};

consteval bool test() {
  S s{};
  return &s == &s.self();
}

static_assert(test());
