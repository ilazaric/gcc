// { dg-do compile { target c++26 } }

#include <vector>
#include <type_traits>

struct A {
  A() {}
  A(const A&) = delete;
  A(A&&) noexcept {}
  A& operator=(const A&) = delete;
  A& operator=(A&&) noexcept { return *this; }
};

struct B {
  A a;
  B(B&&) = default;
  B& operator=(B&&) = default;
  ~B() {}
};

static_assert(std::is_aggregate_v<B>);

void test() {
  std::vector<B> vec;
  vec.emplace_back(B{.a{}});
  vec.emplace_back(B{.a{}});
  vec.emplace_back(B{.a{}});
  vec.emplace_back(B{.a{}});
}

struct C {
  C(const C&) = delete;
};

static_assert(std::is_aggregate_v<C>);

struct D {
  D(D&&, int = 0);
};

static_assert(!std::is_aggregate_v<D>);
