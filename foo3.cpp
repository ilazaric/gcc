#include <meta>

template<typename>
struct St {
  static inline int x = 1;
  static constexpr int y = 2;
};

using S = St<int>;

consteval {
  S{};
  ivl_inject_csdm(dealias(^^S), "hello", std::meta::reflect_constant(123));
}

consteval {
  for (auto mem : members_of(^^S, std::meta::access_context::unchecked()))
    __builtin_constexpr_diag(32, "", display_string_of(mem));
}

static_assert(S::hello == 123);
