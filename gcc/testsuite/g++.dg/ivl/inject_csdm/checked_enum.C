// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }

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

template<typename E>
  requires std::is_enum_v<E>
using checked_enum = checked_enum_impl<E>::type;

enum class colors { RED, GREEN, BLUE };

using checked_colors = checked_enum<colors>;

static_assert(std::is_same_v<decltype(checked_colors::RED), const checked_colors>);
static_assert(checked_colors::RED == checked_colors(colors::RED));

// was testing some properties, like "are synthesized members inline?" (via objdump), ...
// #include <iostream>
// #include <utility>

// int main() {
//   auto r = checked_colors::BLUE;
//   std::cout << display_string_of(^^decltype(r)) << std::endl;
//   std::cout << std::to_underlying(r.e) << std::endl;
//   std::cout << (void*)&checked_colors::GREEN << std::endl;
// }
