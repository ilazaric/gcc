// { dg-do run { target c++26 } }

#include <cassert>
#include <cstdint>

struct S {
  int x;
  int y;
};

[[gnu::noinline]]
bool test(S& s, int& o, int S::* p) {
  return &s == &__builtin_enclosing_cast(p, o);
}

int main() {
  S s{1, 3};
  assert(test(s, s.x, &S::x));
  assert(test(s, s.y, &S::y));
  return 0;
}
