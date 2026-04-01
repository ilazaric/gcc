#include <meta>

// template<typename>
// struct St {};

// using S = St<int>;

struct S {};
// S s;

// consteval {
//   for (auto mem : members_of(^^S, std::meta::access_context::unchecked()))
//     ;
//     // __builtin_constexpr_diag(32, "", display_string_of(mem));
// }

consteval {
  // S{};
  ivl_inject_csdm(dealias(^^S), "hello", std::meta::reflect_constant(123));
}

// consteval {
//   for (auto mem : members_of(^^S, std::meta::access_context::unchecked()))
//     __builtin_constexpr_diag(32, "", display_string_of(mem));
// }

// struct S {};

static_assert(S::hello == 123);

/*
  lookup_field_r
  dfs_walk_all

  
 */

/*
#0  error_at (loc=loc@entry=3263071492, gmsgid=gmsgid@entry=0x2379319 "%qD is not a member of %qT") at /home/ilazaric/repos/ALL/submodules/gcc/gcc/diagnostic-global-context.cc:644
#1  0x000000000088da8a in qualified_name_lookup_error (scope=scope@entry=0x7ffff3e29a80, name=name@entry=0x7ffff778e840, decl=decl@entry=0x7ffff781c2a0, location=location@entry=3263071492) at /home/ilazaric/repos/ALL/submodules/gcc/gcc/cp/error.cc:5096
#2  0x00000000009ecb0a in finish_id_expression_1 (id_expression=0x7ffff778e840, decl=0x7ffff781c2a0, scope=0x7ffff3e29a80, idk=idk@entry=0x7fffffffcefc, integral_constant_expression_p=true, allow_non_integral_constant_expression_p=true, non_integral_constant_expression_p=0x7ffff7fba0fd, template_p=false, 
    done=true, address_p=false, template_arg_p=false, error_msg=0x7fffffffcdf8, location=3263071492) at /home/ilazaric/repos/ALL/submodules/gcc/gcc/cp/semantics.cc:4811
#3  0x00000000009ed634 in finish_id_expression (id_expression=<optimized out>, decl=<optimized out>, scope=<optimized out>, idk=idk@entry=0x7fffffffcefc, integral_constant_expression_p=<optimized out>, allow_non_integral_constant_expression_p=true, non_integral_constant_expression_p=0x7ffff7fba0fd, 
    template_p=false, done=true, address_p=false, template_arg_p=false, error_msg=0x7fffffffcdf8, location=3263071492) at /home/ilazaric/repos/ALL/submodules/gcc/gcc/cp/semantics.cc:5139
#4  0x0000000000956c32 in cp_parser_primary_expression (parser=parser@entry=0x7ffff7fba0d0, address_p=address_p@entry=false, cast_p=cast_p@entry=false, template_arg_p=template_arg_p@entry=false, decltype_p=decltype_p@entry=false, idk=0x7fffffffcefc)
    at /home/ilazaric/repos/ALL/submodules/gcc/gcc/cp/parser.cc:7158
#5  0x0000000000943fb4 in cp_parser_postfix_expression (parser=parser@entry=0x7ffff7fba0d0, address_p=false, cast_p=cast_p@entry=false, member_access_only_p=member_access_only_p@entry=false, decltype_p=decltype_p@entry=false, pidk_return=0x0) at /home/ilazaric/repos/ALL/submodules/gcc/gcc/cp/parser.cc:8912
#6  0x000000000094097e in cp_parser_unary_expression (parser=parser@entry=0x7ffff7fba0d0, pidk=pidk@entry=0x0, address_p=address_p@entry=false, cast_p=cast_p@entry=false, decltype_p=decltype_p@entry=false) at /home/ilazaric/repos/ALL/submodules/gcc/gcc/cp/parser.cc:10625
#7  0x00000000009262b5 in cp_parser_cast_expression (parser=parser@entry=0x7ffff7fba0d0, address_p=address_p@entry=false, cast_p=false, decltype_p=decltype_p@entry=false, pidk=0x0) at /home/ilazaric/repos/ALL/submodules/gcc/gcc/cp/parser.cc:11540
#8  0x0000000000927084 in cp_parser_binary_expression (parser=parser@entry=0x7ffff7fba0d0, cast_p=cast_p@entry=false, no_toplevel_fold_p=no_toplevel_fold_p@entry=false, decltype_p=decltype_p@entry=false, prec=prec@entry=PREC_NOT_OPERATOR, pidk=0x0)
    at /home/ilazaric/repos/ALL/submodules/gcc/gcc/cp/parser.cc:11643
#9  0x0000000000927d63 in cp_parser_assignment_expression (parser=parser@entry=0x7ffff7fba0d0, pidk=pidk@entry=0x0, cast_p=cast_p@entry=false, decltype_p=decltype_p@entry=false) at /home/ilazaric/repos/ALL/submodules/gcc/gcc/cp/parser.cc:11996
#10 0x000000000092d644 in cp_parser_constant_expression (parser=parser@entry=0x7ffff7fba0d0, allow_non_constant_p=allow_non_constant_p@entry=1, non_constant_p=non_constant_p@entry=0x0, strict_p=strict_p@entry=false) at /home/ilazaric/repos/ALL/submodules/gcc/gcc/cp/parser.cc:12316
#11 0x000000000092f3a1 in cp_parser_static_assert (parser=0x7ffff7fba0d0, member_p=false) at /home/ilazaric/repos/ALL/submodules/gcc/gcc/cp/parser.cc:19189
#12 0x000000000097b530 in cp_parser_declaration (parser=0x7ffff7fba0d0, prefix_attrs=0x0) at /home/ilazaric/repos/ALL/submodules/gcc/gcc/cp/parser.cc:17601
#13 0x000000000097db73 in cp_parser_toplevel_declaration (parser=0x7ffff7fba0d0) at /home/ilazaric/repos/ALL/submodules/gcc/gcc/cp/parser.cc:17705
#14 cp_parser_translation_unit (parser=0x7ffff7fba0d0) at /home/ilazaric/repos/ALL/submodules/gcc/gcc/cp/parser.cc:5599
#15 c_parse_file () at /home/ilazaric/repos/ALL/submodules/gcc/gcc/cp/parser.cc:57516
#16 0x0000000000aa701a in c_common_parse_file () at /home/ilazaric/repos/ALL/submodules/gcc/gcc/c-family/c-opts.cc:1430
#17 0x000000000104b611 in compile_file () at /home/ilazaric/repos/ALL/submodules/gcc/gcc/toplev.cc:455
#18 0x00000000007b6090 in do_compile () at /home/ilazaric/repos/ALL/submodules/gcc/gcc/toplev.cc:2225
#19 toplev::main (this=this@entry=0x7fffffffdaf6, argc=<optimized out>, argc@entry=19, argv=<optimized out>, argv@entry=0x7fffffffdc38) at /home/ilazaric/repos/ALL/submodules/gcc/gcc/toplev.cc:2389
#20 0x00000000007b796f in main (argc=19, argv=0x7fffffffdc38) at /home/ilazaric/repos/ALL/submodules/gcc/gcc/main.cc:39
 */
