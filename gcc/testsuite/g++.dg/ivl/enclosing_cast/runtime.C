// { dg-do run { target c++26 } }
// { dg-options "-fsanitize=address,undefined" }

#include <cassert>
#include <cstdint>

struct S {
  int x;
  int y;
};

S& get(int S::* ptr, int& o) {
  return __builtin_enclosing_cast(ptr, o);
}

int main() {
  S s{1, 3};
  int& x = s.x;
  int& y = s.y;
  S& sx = get(&S::x, x);
  S& sy = get(&S::y, y);
  assert(reinterpret_cast<uintptr_t>(&s) == reinterpret_cast<uintptr_t>(&sx));
  assert(reinterpret_cast<uintptr_t>(&s) == reinterpret_cast<uintptr_t>(&sy));
  return 0;
}
