// { dg-do compile { target c++26 } }

#include <enclosing_cast>

struct S {
  int x;
private:
  int y;
};

struct T {
  int x;
  float y;
};

struct U {
  int x;
  int y;
};

constexpr auto&& a = std::enclosing_cast<&S::x>(S{}.x); // { dg-error "no matching function for call to .enclosing_cast<&S::x>.int.." }
                                                        // { dg-error "note: .S. is not a standard layout type" "" { target *-*-* } 0 }

constexpr auto&& b = std::enclosing_cast<&T::y>(T{}.x); // { dg-error "no matching function for call to 'enclosing_cast<&T::y>.int.'" }
                                                        // { dg-error "note: 'int' is not the same as 'float'" "" { target *-*-* } 0 }

constexpr auto&& c = std::enclosing_cast<123>(456); // { dg-error "no matching function for call to 'enclosing_cast<123>.int.'" }
                                                    // { dg-error "note: 'int' is not a member object pointer" "" { target *-*-* } 0 }

constexpr auto&& d = std::enclosing_cast<static_cast<float T::*>(nullptr)>(T{}.y); // { dg-error "no matching function for call to 'enclosing_cast<-1>.float.'" }
                                                                                   // { dg-error "note: the expression '_Mp != nullptr .with _Mp = -1.' evaluated to 'false'" "" { target *-*-* } 0 }

constexpr auto&& e = std::enclosing_cast<&U::x>(U{}.y); // { dg-error "in 'constexpr' expansion of 'std::enclosing_cast<&U::x, int>.U...U::y.'" }
                                                        // { dg-error "'__builtin_enclosing_cast' is not a constant expression because arguments do not refer to same field" "" { target *-*-* } 0 }

constexpr auto&& f = std::enclosing_cast<&U::x>(U{}.x); // { dg-error "'<anonymous>' is not a constant expression" }
