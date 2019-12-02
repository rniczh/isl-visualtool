// #include "islplot.hpp"
#include "islplot.hpp"
#include "isl/set.h"
#include "isl/union_set.h"
#include "isl/union_map.h"

#include <iostream>
#include <vector>


int main(int argc, char *argv[]) {
  isl_ctx *ctx = isl_ctx_alloc();
  isl_set *context = isl_set_read_from_str(ctx, "{ : }");
  isl_set *d2 = isl_set_read_from_str(ctx, "{ S[t,i] : 1<=t<=4 and 1<=i<=4 }");
  isl_set *d3 = isl_set_read_from_str(ctx, "{ A[t,i] : 1<=t<=5 and 1<=i<=5 }");

  isl_union_set *s1 = isl_union_set_from_set(d2);
  isl_union_set *s2 = isl_union_set_from_set(d3);
  isl_union_set *s3 = isl_union_set_union(s1, s2);


  isl_basic_set *bset = isl_basic_set_read_from_str(ctx, "{ A[i,j] : 1 < i < j < 10}");


  islv::ISLVContext vctx;

  // plotting basic set
  vctx.plot(bset);

  // plotting set
  vctx.plot(d2);

  // plotting union set
  vctx.plot(s3);


  return 0;
}
