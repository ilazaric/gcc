/* { dg-do compile { target c++26 } } */
/* { dg-options "-O3 -fdump-ipa-cp-details -fdump-tree-optimized" } */

using el = int;

struct S {
  el i;
  bool pred() { return i != 42; }
};

void foo(S& s) {
  [[assume(!s.pred())]];
  if (s.pred()) __builtin_abort();
}

/* { dg-final { scan-tree-dump-not "abort" "optimized" } } */
