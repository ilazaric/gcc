// { dg-do compile { target c++26 } }
// { dg-additional-options "-fcontracts -freflection" }
// { dg-skip-if "requires hosted libstdc++ for stdc++exp" { ! hostedlib } }

void fn() pre(true) {}

#include <source_location>
#include <meta>

static_assert(has_external_linkage(^^std::source_location));
