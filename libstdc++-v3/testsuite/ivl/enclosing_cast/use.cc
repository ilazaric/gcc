// { dg-do run { target c++26 } }
// { dg-options "-freflection -fsanitize=address,undefined" }

#include <enclosing_cast>
#include <meta>

constexpr auto ctx = std::meta::access_context::unchecked();

template<typename Parent, size_t Index>
struct first_t {
  int data;
  template<typename Self>
  constexpr decltype(auto) operator()(this Self&& self) {
    return std::enclosing_cast<&[:nonstatic_data_members_of(^^Parent, ctx)[Index]:]>(static_cast<Self&&>(self)).second(self.data);
  }
};

template<typename Parent, size_t Index>
struct second_t {
  int data;
  template<typename Self>
  constexpr decltype(auto) operator()(this Self&& self, int a) {
    return std::enclosing_cast<&[:nonstatic_data_members_of(^^Parent, ctx)[Index]:]>(static_cast<Self&&>(self)).third(a, self.data);
  }
};

template<typename Parent, size_t Index>
struct third_t {
  int data;
  template<typename Self>
  constexpr decltype(auto) operator()(this Self&& self, int a, int b) {
    return std::enclosing_cast<&[:nonstatic_data_members_of(^^Parent, ctx)[Index]:]>(static_cast<Self&&>(self)).check(a, b, self.data);
  }
};

struct parent {
  first_t<parent, 0> first;
  second_t<parent, 1> second;
  third_t<parent, 2> third;

  constexpr bool check(int a, int b, int c) {
    return a * b == c;
  }
};

static_assert(parent{2, 3, 6}.first());

[[gnu::noinline]]
int id(int x) { return x; }

int main() {
  return parent{id(2), id(3), id(6)}.first() ? 0 : 1;
}
