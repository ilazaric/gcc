/* { dg-do compile { target c++26 } } */
/* { dg-options "-O3 -fdump-ipa-cp-details -fdump-tree-optimized" } */

struct S {
  bool x;
  bool pred() { return x; }
};

struct T : S {};

void foo(T& t) {
  [[assume(!t.pred())]];
  if (t.pred()) __builtin_abort();
}

/* { dg-final { scan-tree-dump-not "abort" "optimized" } } */
