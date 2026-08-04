// { dg-do compile { target c++26 } }

struct S {
  int x;
  int y;
};

constexpr S s{42};

using MemPtr = int S::*;

constexpr MemPtr np = nullptr;

constexpr auto&& ref1 = __builtin_enclosing_cast(np, s.x); // { dg-error "'__builtin_enclosing_cast' is not a constant expression because first argument is nullptr" }

constexpr auto&& ref2 = __builtin_enclosing_cast(123.456, s.x); // { dg-error "'__builtin_enclosing_cast' argument '1.23456e\\+2' is not a pointer to data member" }

constexpr auto&& ref3 = __builtin_enclosing_cast(&S::x, 123); // { dg-error "'__builtin_enclosing_cast' argument '123' is not a reference" }

constexpr auto&& ref4 = __builtin_enclosing_cast(&S::y, s.x); // { dg-error "'__builtin_enclosing_cast' is not a constant expression because arguments do not refer to same field" }

constexpr int z = 123;

constexpr auto&& ref5 = __builtin_enclosing_cast(&S::x, z); // { dg-error "'__builtin_enclosing_cast' is not a constant expression because second argument is not a sub-object of corresponding class" }
