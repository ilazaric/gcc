#include <meta>
#include <type_traits>

template<typename E>
  requires std::is_enum_v<E>
consteval std::span<const E> enumerators() {
  std::vector<E> ret;
  for (auto e : enumerators_of(^^E)) ret.push_back(extract<E>(e));
  return define_static_array(ret);
}

template<typename E>
  requires std::is_enum_v<E>
constexpr bool is_enumerator(E e) {
  for (auto enumerator : enumerators<E>())
    if (e == enumerator) return true;
  return false;
}

template<typename E>
requires std::is_enum_v<E>
struct checked_enum_impl {
  struct type {
    E e;

    type() = delete;

    type(const type&) = default;
    type(type&&) = default;

    type& operator=(const type&) = default;
    type& operator=(type&&) = default;
  
    explicit constexpr type(E e) pre(is_enumerator(e)) : e(e) {}

    constexpr auto operator<=>(const type&) const = default;
  };

  consteval {
    for (auto er : enumerators_of(^^E)) {
      auto name = identifier_of(er);
      auto value = extract<E>(er);
      ivl_inject_csdm(^^type, name, std::meta::reflect_constant(type(value)));
    }
  }
};

// template<typename>
// struct checked_enum_impl_done;

// template<typename E>
//   requires std::is_enum_v<E>
// consteval std::meta::info checked_enum_expander() {
//   using RT = checked_enum_impl<E>;
//   auto marker = ^^checked_enum_impl_done<E>;
//   if (is_complete_type(marker))
//     return ^^RT;

//   // for (auto er : enumerators_of(^^E)) {
//   //   auto name = identifier_of(er);
//   //   auto value = extract<E>(er);
//   //   ivl_inject_csdm(dealias(^^RT), name, std::meta::reflect_constant(RT(value)));
//   // }
  
//   define_aggregate(marker, {});
//   return ^^RT;
// }

// template<typename E>
//   requires std::is_enum_v<E>
// using checked_enum = typename [: checked_enum_expander<E>() :];

template<typename E>
  requires std::is_enum_v<E>
using checked_enum = checked_enum_impl<E>::type;

enum class colors { RED, GREEN, BLUE };

using checked_colors = checked_enum<colors>;

struct znj {
  static constexpr auto RED = colors::RED;
};

consteval {
  for (auto mem : members_of(^^checked_colors, std::meta::access_context::unchecked()))
    __builtin_constexpr_diag(32, "", display_string_of(mem));
}

static_assert(std::is_same_v<decltype(checked_colors::RED), const checked_colors>);
static_assert(checked_colors::RED == checked_colors(colors::RED));

#include <iostream>
#include <utility>

int main() {
  auto r = checked_colors::BLUE;
  std::cout << display_string_of(^^decltype(r)) << std::endl;
  std::cout << std::to_underlying(r.e) << std::endl;
}
