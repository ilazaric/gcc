#include <meta>

template<typename>
struct St {};

using S = St<int>;

consteval {
  sizeof(S);
  ivl_inject_csdm(dealias(^^S), "hello", std::meta::reflect_constant(123));
}

static_assert(S::hello == 123);
