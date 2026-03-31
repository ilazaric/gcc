struct T {};

T t;

using Tref = T&;

struct S {
  static constexpr int mem = 123;
  // static constexpr int mema = 123;
  // static constexpr T memt = T{};
  // static constexpr Tref memtref = t;
  // static constexpr int memb = 123;
  // static constexpr int memc = 123;
};
