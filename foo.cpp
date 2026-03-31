// #include "/home/ilazaric/repos/ALL/submodules/gcc/libstdc++-v3/include/std/meta"
#include <meta>

template<typename>
struct St {
  static inline int x = 1;
  static constexpr int y = 2;
};

using S = St<int>;

// int x;

// struct T;

// consteval {
//   std::meta::data_member_options opts;
//   opts.name = "hiii";
//   data_member_spec(^^int, opts);
// }

// consteval {
//   char msg[] = "hello\0world";
//   std::string_view sv(msg, sizeof(msg)-1);
//   sv = msg;
//   ivl_inject_csdm(^^S,
// 		  sv
// 		  // "hiii"
// 		  ,
// 		  // ^^int
// 		  // std::meta::reflect_object(x)
// 		  std::meta::reflect_constant(123)
// 		  );
// }

consteval {
  S{};
  ivl_inject_csdm(dealias(^^S), "hello", std::meta::reflect_constant(123));
  ivl_inject_csdm(dealias(^^S), "world", std::meta::reflect_constant(321));
}

consteval {
  for (auto mem : members_of(^^S, std::meta::access_context::unchecked()))
    __builtin_constexpr_diag(32, "", display_string_of(mem));
}

static_assert(^^decltype(S::hello) == ^^const int);
static_assert(&S::hello != nullptr);
static_assert(parent_of(^^S::hello) == ^^S);
static_assert(is_static_member(^^S::hello));

static_assert(S::hello == 123);
static_assert(S::world == 321);

// #include <iostream>

// int main() {
//   std::cout << S::hello << std::endl;
// }

// consteval {
//   char bar[] = "hello\0world";
//   std::string_view foo(bar, sizeof(bar) - 1);
//   __builtin_constexpr_diag(0, "", foo);
// }

// static_assert(^^decltype(S::hiii) == ^^const int);
// static_assert(S::hiii == 123);
