/* SIE CONFIDENTIAL
 * Clang/LLVM Toolchain for PS4
 * Copyright(C) 2019 Sony Interactive Entertainment Inc.
 */

#pragma once

/* Defines for indicating IntelliSense */
#define __INTELLISENSE__
#define __ORBIS_INTELLISENSE__
#define __ORBIS_CLANG_INTELLISENSE__

#if (_MSC_VER <= 1600)
 #define __INTELLISENSE_VS10__
 #define __INTELLISENSE_VER 1000
#elif (_MSC_VER == 1700)
 #define __INTELLISENSE_VS11__
 #define __INTELLISENSE_VER 1100
#elif (_MSC_VER == 1800)
 #define __INTELLISENSE_VS12__
 #define __INTELLISENSE_VER 1200
#elif (_MSC_VER == 1900)
 #define __INTELLISENSE_VS14__
 #define __INTELLISENSE_VER 1400
#elif (_MSC_VER >= 1910)
 #define __INTELLISENSE_VS15__
 #define __INTELLISENSE_VER 1500
#endif

/* Undefine built-in MS VC++ defines */
#undef _WIN32
#undef _MSC_VER
#undef _MSC_FULL_VER
#undef _MSC_BUILD
#undef _M_IX86
#undef __EDG__
#undef __EDG_VERSION__
#undef __EDG_SIZE_TYPE__
#undef __EDG_PTRDIFF_TYPE__
#undef __EDG_TYPE_TRAITS_ENABLED

/* Built-in clang defines */

/* Generated Start */
#define _LP64 1
#define __AES__ 1
#define __ATOMIC_ACQUIRE 2
#define __ATOMIC_ACQ_REL 4
#define __ATOMIC_CONSUME 1
#define __ATOMIC_RELAXED 0
#define __ATOMIC_RELEASE 3
#define __ATOMIC_SEQ_CST 5
#define __AVX__ 1
#define __BIGGEST_ALIGNMENT__ 16
#define __BMI__ 1
#define __BYTE_ORDER__ __ORDER_LITTLE_ENDIAN__
#define __CHAR16_TYPE__ unsigned short
#define __CHAR32_TYPE__ unsigned int
#define __CHAR_BIT__ 8
#define __CLANG_ATOMIC_BOOL_LOCK_FREE 2
#define __CLANG_ATOMIC_CHAR16_T_LOCK_FREE 2
#define __CLANG_ATOMIC_CHAR32_T_LOCK_FREE 2
#define __CLANG_ATOMIC_CHAR_LOCK_FREE 2
#define __CLANG_ATOMIC_INT_LOCK_FREE 2
#define __CLANG_ATOMIC_LLONG_LOCK_FREE 2
#define __CLANG_ATOMIC_LONG_LOCK_FREE 2
#define __CLANG_ATOMIC_POINTER_LOCK_FREE 2
#define __CLANG_ATOMIC_SHORT_LOCK_FREE 2
#define __CLANG_ATOMIC_WCHAR_T_LOCK_FREE 2
#define __CONSTANT_CFSTRINGS__ 1
#define __DBL_DECIMAL_DIG__ 17
#define __DBL_DENORM_MIN__ 2.2250738585072014e-308
#define __DBL_DIG__ 15
#define __DBL_EPSILON__ 2.2204460492503131e-16
#define __DBL_HAS_DENORM__ 0
#define __DBL_HAS_INFINITY__ 1
#define __DBL_HAS_QUIET_NAN__ 1
#define __DBL_MANT_DIG__ 53
#define __DBL_MAX_10_EXP__ 308
#define __DBL_MAX_EXP__ 1024
#define __DBL_MAX__ 1.7976931348623157e+308
#define __DBL_MIN_10_EXP__ (-307)
#define __DBL_MIN_EXP__ (-1021)
#define __DBL_MIN__ 2.2250738585072014e-308
#define __DECIMAL_DIG__ __LDBL_DECIMAL_DIG__
#define __ELF__ 1
#define __F16C__ 1
#define __FINITE_MATH_ONLY__ 0
#define __FLT16_DECIMAL_DIG__ 5
#define __FLT16_DENORM_MIN__ 6.103515625e-5F16
#define __FLT16_DIG__ 3
#define __FLT16_EPSILON__ 9.765625e-4F16
#define __FLT16_HAS_DENORM__ 0
#define __FLT16_HAS_INFINITY__ 1
#define __FLT16_HAS_QUIET_NAN__ 1
#define __FLT16_MANT_DIG__ 11
#define __FLT16_MAX_10_EXP__ 4
#define __FLT16_MAX_EXP__ 15
#define __FLT16_MAX__ 6.5504e+4F16
#define __FLT16_MIN_10_EXP__ (-13)
#define __FLT16_MIN_EXP__ (-14)
#define __FLT16_MIN__ 6.103515625e-5F16
#define __FLT_DECIMAL_DIG__ 9
#define __FLT_DENORM_MIN__ 1.17549435e-38F
#define __FLT_DIG__ 6
#define __FLT_EPSILON__ 1.19209290e-7F
#define __FLT_EVAL_METHOD__ 0
#define __FLT_HAS_DENORM__ 0
#define __FLT_HAS_INFINITY__ 1
#define __FLT_HAS_QUIET_NAN__ 1
#define __FLT_MANT_DIG__ 24
#define __FLT_MAX_10_EXP__ 38
#define __FLT_MAX_EXP__ 128
#define __FLT_MAX__ 3.40282347e+38F
#define __FLT_MIN_10_EXP__ (-37)
#define __FLT_MIN_EXP__ (-125)
#define __FLT_MIN__ 1.17549435e-38F
#define __FLT_RADIX__ 2
#define __FXSR__ 1
#define __FreeBSD__ 9
#define __FreeBSD_cc_version 900001
#define __GCC_ATOMIC_BOOL_LOCK_FREE 2
#define __GCC_ATOMIC_CHAR16_T_LOCK_FREE 2
#define __GCC_ATOMIC_CHAR32_T_LOCK_FREE 2
#define __GCC_ATOMIC_CHAR_LOCK_FREE 2
#define __GCC_ATOMIC_INT_LOCK_FREE 2
#define __GCC_ATOMIC_LLONG_LOCK_FREE 2
#define __GCC_ATOMIC_LONG_LOCK_FREE 2
#define __GCC_ATOMIC_POINTER_LOCK_FREE 2
#define __GCC_ATOMIC_SHORT_LOCK_FREE 2
#define __GCC_ATOMIC_TEST_AND_SET_TRUEVAL 1
#define __GCC_ATOMIC_WCHAR_T_LOCK_FREE 2
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 1
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_16 1
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 1
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 1
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_8 1
#define __GNUC_MINOR__ 2
#define __GNUC_PATCHLEVEL__ 1
#define __GNUC__ 4
#define __GXX_ABI_VERSION 1002
#define __INT16_C_SUFFIX__ 
#define __INT16_FMTd__ "hd"
#define __INT16_FMTi__ "hi"
#define __INT16_MAX__ 32767
#define __INT16_TYPE__ short
#define __INT32_C_SUFFIX__ 
#define __INT32_FMTd__ "d"
#define __INT32_FMTi__ "i"
#define __INT32_MAX__ 2147483647
#define __INT32_TYPE__ int
#define __INT64_C_SUFFIX__ L
#define __INT64_FMTd__ "ld"
#define __INT64_FMTi__ "li"
#define __INT64_MAX__ 9223372036854775807L
#define __INT64_TYPE__ long int
#define __INT8_C_SUFFIX__ 
#define __INT8_FMTd__ "hhd"
#define __INT8_FMTi__ "hhi"
#define __INT8_MAX__ 127
#define __INT8_TYPE__ signed char
#define __INTMAX_C_SUFFIX__ L
#define __INTMAX_FMTd__ "ld"
#define __INTMAX_FMTi__ "li"
#define __INTMAX_MAX__ 9223372036854775807L
#define __INTMAX_TYPE__ long int
#define __INTMAX_WIDTH__ 64
#define __INTPTR_FMTd__ "ld"
#define __INTPTR_FMTi__ "li"
#define __INTPTR_MAX__ 9223372036854775807L
#define __INTPTR_TYPE__ long int
#define __INTPTR_WIDTH__ 64
#define __INT_FAST16_FMTd__ "hd"
#define __INT_FAST16_FMTi__ "hi"
#define __INT_FAST16_MAX__ 32767
#define __INT_FAST16_TYPE__ short
#define __INT_FAST32_FMTd__ "d"
#define __INT_FAST32_FMTi__ "i"
#define __INT_FAST32_MAX__ 2147483647
#define __INT_FAST32_TYPE__ int
#define __INT_FAST64_FMTd__ "ld"
#define __INT_FAST64_FMTi__ "li"
#define __INT_FAST64_MAX__ 9223372036854775807L
#define __INT_FAST64_TYPE__ long int
#define __INT_FAST8_FMTd__ "hhd"
#define __INT_FAST8_FMTi__ "hhi"
#define __INT_FAST8_MAX__ 127
#define __INT_FAST8_TYPE__ signed char
#define __INT_LEAST16_FMTd__ "hd"
#define __INT_LEAST16_FMTi__ "hi"
#define __INT_LEAST16_MAX__ 32767
#define __INT_LEAST16_TYPE__ short
#define __INT_LEAST32_FMTd__ "d"
#define __INT_LEAST32_FMTi__ "i"
#define __INT_LEAST32_MAX__ 2147483647
#define __INT_LEAST32_TYPE__ int
#define __INT_LEAST64_FMTd__ "ld"
#define __INT_LEAST64_FMTi__ "li"
#define __INT_LEAST64_MAX__ 9223372036854775807L
#define __INT_LEAST64_TYPE__ long int
#define __INT_LEAST8_FMTd__ "hhd"
#define __INT_LEAST8_FMTi__ "hhi"
#define __INT_LEAST8_MAX__ 127
#define __INT_LEAST8_TYPE__ signed char
#define __INT_MAX__ 2147483647
#define __KPRINTF_ATTRIBUTE__ 1
#define __LDBL_DECIMAL_DIG__ 21
#define __LDBL_DENORM_MIN__ 3.64519953188247460253e-4951L
#define __LDBL_DIG__ 18
#define __LDBL_EPSILON__ 1.08420217248550443401e-19L
#define __LDBL_HAS_DENORM__ 1
#define __LDBL_HAS_INFINITY__ 1
#define __LDBL_HAS_QUIET_NAN__ 1
#define __LDBL_MANT_DIG__ 64
#define __LDBL_MAX_10_EXP__ 4932
#define __LDBL_MAX_EXP__ 16384
#define __LDBL_MAX__ 1.18973149535723176502e+4932L
#define __LDBL_MIN_10_EXP__ (-4931)
#define __LDBL_MIN_EXP__ (-16381)
#define __LDBL_MIN__ 3.36210314311209350626e-4932L
#define __LITTLE_ENDIAN__ 1
#define __LONG_LONG_MAX__ 9223372036854775807LL
#define __LONG_MAX__ 9223372036854775807L
#define __LP64__ 1
#define __LZCNT__ 1
#define __MMX__ 1
#define __MOVBE__ 1
#define __NO_INLINE__ 1
#define __NO_MATH_INLINES 1
#define __OBJC_BOOL_IS_BOOL 0
#define __OPENCL_MEMORY_SCOPE_ALL_SVM_DEVICES 3
#define __OPENCL_MEMORY_SCOPE_DEVICE 2
#define __OPENCL_MEMORY_SCOPE_SUB_GROUP 4
#define __OPENCL_MEMORY_SCOPE_WORK_GROUP 1
#define __OPENCL_MEMORY_SCOPE_WORK_ITEM 0
#define __ORBIS__ 1
#define __ORDER_BIG_ENDIAN__ 4321
#define __ORDER_LITTLE_ENDIAN__ 1234
#define __ORDER_PDP_ENDIAN__ 3412
#define __PCLMUL__ 1
#define __PIC__ 2
#define __POINTER_WIDTH__ 64
#define __POPCNT__ 1
#define __PRAGMA_REDEFINE_EXTNAME 1
#define __PRFCHW__ 1
#define __PTRDIFF_FMTd__ "ld"
#define __PTRDIFF_FMTi__ "li"
#define __PTRDIFF_MAX__ 9223372036854775807L
#define __PTRDIFF_TYPE__ long int
#define __PTRDIFF_WIDTH__ 64
#define __REGISTER_PREFIX__ 
#define __SCE_ORBIS_CLANG_MAJOR__ 7
#define __SCE_ORBIS_CLANG_MINOR__ 00
#define __SCE_ORBIS_CLANG_PATCHLEVEL__ 0
#define __SCE_ORBIS_CLANG_REVISION__ 276
#define __SCHAR_MAX__ 127
#define __SHRT_MAX__ 32767
#define __SIG_ATOMIC_MAX__ 2147483647
#define __SIG_ATOMIC_WIDTH__ 32
#define __SIZEOF_DOUBLE__ 8
#define __SIZEOF_FLOAT__ 4
#define __SIZEOF_INT128__ 16
#define __SIZEOF_INT__ 4
#define __SIZEOF_LONG_DOUBLE__ 16
#define __SIZEOF_LONG_LONG__ 8
#define __SIZEOF_LONG__ 8
#define __SIZEOF_POINTER__ 8
#define __SIZEOF_PTRDIFF_T__ 8
#define __SIZEOF_SHORT__ 2
#define __SIZEOF_SIZE_T__ 8
#define __SIZEOF_WCHAR_T__ 2
#define __SIZEOF_WINT_T__ 4
#define __SIZE_FMTX__ "lX"
#define __SIZE_FMTo__ "lo"
#define __SIZE_FMTu__ "lu"
#define __SIZE_FMTx__ "lx"
#define __SIZE_MAX__ 18446744073709551615UL
#define __SIZE_TYPE__ long unsigned int
#define __SIZE_WIDTH__ 64
#define __SSE2_MATH__ 1
#define __SSE2__ 1
#define __SSE3__ 1
#define __SSE4A__ 1
#define __SSE4_1__ 1
#define __SSE4_2__ 1
#define __SSE_MATH__ 1
#define __SSE__ 1
#define __SSP_STRONG__ 2
#define __SSSE3__ 1
#define __STDC_HOSTED__ 1
#define __STDC_UTF_16__ 1
#define __STDC_UTF_32__ 1
#define __STDC__ 1
#define __UINT16_C_SUFFIX__ 
#define __UINT16_FMTX__ "hX"
#define __UINT16_FMTo__ "ho"
#define __UINT16_FMTu__ "hu"
#define __UINT16_FMTx__ "hx"
#define __UINT16_MAX__ 65535
#define __UINT16_TYPE__ unsigned short
#define __UINT32_C_SUFFIX__ U
#define __UINT32_FMTX__ "X"
#define __UINT32_FMTo__ "o"
#define __UINT32_FMTu__ "u"
#define __UINT32_FMTx__ "x"
#define __UINT32_MAX__ 4294967295U
#define __UINT32_TYPE__ unsigned int
#define __UINT64_C_SUFFIX__ UL
#define __UINT64_FMTX__ "lX"
#define __UINT64_FMTo__ "lo"
#define __UINT64_FMTu__ "lu"
#define __UINT64_FMTx__ "lx"
#define __UINT64_MAX__ 18446744073709551615UL
#define __UINT64_TYPE__ long unsigned int
#define __UINT8_C_SUFFIX__ 
#define __UINT8_FMTX__ "hhX"
#define __UINT8_FMTo__ "hho"
#define __UINT8_FMTu__ "hhu"
#define __UINT8_FMTx__ "hhx"
#define __UINT8_MAX__ 255
#define __UINT8_TYPE__ unsigned char
#define __UINTMAX_C_SUFFIX__ UL
#define __UINTMAX_FMTX__ "lX"
#define __UINTMAX_FMTo__ "lo"
#define __UINTMAX_FMTu__ "lu"
#define __UINTMAX_FMTx__ "lx"
#define __UINTMAX_MAX__ 18446744073709551615UL
#define __UINTMAX_TYPE__ long unsigned int
#define __UINTMAX_WIDTH__ 64
#define __UINTPTR_FMTX__ "lX"
#define __UINTPTR_FMTo__ "lo"
#define __UINTPTR_FMTu__ "lu"
#define __UINTPTR_FMTx__ "lx"
#define __UINTPTR_MAX__ 18446744073709551615UL
#define __UINTPTR_TYPE__ long unsigned int
#define __UINTPTR_WIDTH__ 64
#define __UINT_FAST16_FMTX__ "hX"
#define __UINT_FAST16_FMTo__ "ho"
#define __UINT_FAST16_FMTu__ "hu"
#define __UINT_FAST16_FMTx__ "hx"
#define __UINT_FAST16_MAX__ 65535
#define __UINT_FAST16_TYPE__ unsigned short
#define __UINT_FAST32_FMTX__ "X"
#define __UINT_FAST32_FMTo__ "o"
#define __UINT_FAST32_FMTu__ "u"
#define __UINT_FAST32_FMTx__ "x"
#define __UINT_FAST32_MAX__ 4294967295U
#define __UINT_FAST32_TYPE__ unsigned int
#define __UINT_FAST64_FMTX__ "lX"
#define __UINT_FAST64_FMTo__ "lo"
#define __UINT_FAST64_FMTu__ "lu"
#define __UINT_FAST64_FMTx__ "lx"
#define __UINT_FAST64_MAX__ 18446744073709551615UL
#define __UINT_FAST64_TYPE__ long unsigned int
#define __UINT_FAST8_FMTX__ "hhX"
#define __UINT_FAST8_FMTo__ "hho"
#define __UINT_FAST8_FMTu__ "hhu"
#define __UINT_FAST8_FMTx__ "hhx"
#define __UINT_FAST8_MAX__ 255
#define __UINT_FAST8_TYPE__ unsigned char
#define __UINT_LEAST16_FMTX__ "hX"
#define __UINT_LEAST16_FMTo__ "ho"
#define __UINT_LEAST16_FMTu__ "hu"
#define __UINT_LEAST16_FMTx__ "hx"
#define __UINT_LEAST16_MAX__ 65535
#define __UINT_LEAST16_TYPE__ unsigned short
#define __UINT_LEAST32_FMTX__ "X"
#define __UINT_LEAST32_FMTo__ "o"
#define __UINT_LEAST32_FMTu__ "u"
#define __UINT_LEAST32_FMTx__ "x"
#define __UINT_LEAST32_MAX__ 4294967295U
#define __UINT_LEAST32_TYPE__ unsigned int
#define __UINT_LEAST64_FMTX__ "lX"
#define __UINT_LEAST64_FMTo__ "lo"
#define __UINT_LEAST64_FMTu__ "lu"
#define __UINT_LEAST64_FMTx__ "lx"
#define __UINT_LEAST64_MAX__ 18446744073709551615UL
#define __UINT_LEAST64_TYPE__ long unsigned int
#define __UINT_LEAST8_FMTX__ "hhX"
#define __UINT_LEAST8_FMTo__ "hho"
#define __UINT_LEAST8_FMTu__ "hhu"
#define __UINT_LEAST8_FMTx__ "hhx"
#define __UINT_LEAST8_MAX__ 255
#define __UINT_LEAST8_TYPE__ unsigned char
#define __USER_LABEL_PREFIX__ 
#define __VERSION__ "4.2.1 Compatible Clang 8.0.1 (PS4 clang version 7.00.0.276 83b6df81)"
#define __WCHAR_MAX__ 65535
#define __WCHAR_TYPE__ unsigned short
#define __WCHAR_UNSIGNED__ 1
#define __WCHAR_WIDTH__ 16
#define __WINT_MAX__ 2147483647
#define __WINT_TYPE__ int
#define __WINT_WIDTH__ 32
#define __XSAVEOPT__ 1
#define __XSAVE__ 1
#define __amd64 1
#define __amd64__ 1
#define __btver2 1
#define __btver2__ 1
#define __clang__ 1
#define __clang_major__ 8
#define __clang_minor__ 0
#define __clang_patchlevel__ 1
#define __clang_version__ "8.0.1 (PS4 clang version 7.00.0.276 83b6df81)"
#define __code_model_small_ 1
#define __llvm__ 1
#define __pic__ 2
#define __tune_btver2__ 1
#define __unix 1
#define __unix__ 1
#define __x86_64 1
#define __x86_64__ 1
#define unix 1

#if defined(__cplusplus)
 #define __DEPRECATED 1
 #define __GLIBCXX_BITSIZE_INT_N_0 128
 #define __GLIBCXX_TYPE_INT_N_0 __int128
 #define __GNUC_GNU_INLINE__ 1
 #define __GNUG__ 4
 #define __GXX_EXPERIMENTAL_CXX0X__ 1
 #define __GXX_WEAK__ 1
 #define __STDCPP_DEFAULT_NEW_ALIGNMENT__ 32UL
 #undef __cplusplus
 #define __cplusplus 201402L
 #define __cpp_aggregate_nsdmi 201304L
 #define __cpp_alias_templates 200704L
 #define __cpp_attributes 200809L
 #define __cpp_binary_literals 201304L
 #define __cpp_constexpr 201304L
 #define __cpp_decltype 200707L
 #define __cpp_decltype_auto 201304L
 #define __cpp_delegating_constructors 200604L
 #define __cpp_digit_separators 201309L
 #define __cpp_generic_lambdas 201304L
 #define __cpp_impl_destroying_delete 201806L
 #define __cpp_inheriting_constructors 201511L
 #define __cpp_init_captures 201304L
 #define __cpp_initializer_lists 200806L
 #define __cpp_lambdas 200907L
 #define __cpp_nsdmi 200809L
 #define __cpp_range_based_for 200907
 #define __cpp_raw_strings 200710L
 #define __cpp_ref_qualifiers 200710L
 #define __cpp_return_type_deduction 201304L
 #define __cpp_rvalue_references 200610L
 #define __cpp_static_assert 200410
 #define __cpp_threadsafe_static_init 200806L
 #define __cpp_unicode_characters 200704L
 #define __cpp_unicode_literals 200710L
 #define __cpp_user_defined_literals 200809L
 #define __cpp_variable_templates 201304L
 #define __cpp_variadic_templates 200704L
 #define __private_extern__ extern
#else
 #define __GNUC_STDC_INLINE__ 1
 #define __STDC_VERSION__ 199901L
#endif /* defined(__cplusplus) */
/* Generated End */

/* Provide definitions for other built-in types */
/* Define away __attribute__ usage */
#define __attribute__(x)
#define __extension__(x) (0)
#define __inline__ inline
#define __restrict__ __restrict
#define __asm__ __asm
#define __null 0
/* Use MSVC equivalent for __thread */
#define __thread __declspec(thread)

/* Clang Language Extensions */
#define __has_builtin(x) 0
#define __has_feature(x) 0
#define __has_extension(x) 0
#define __has_cpp_attribute(x) 0
#define __has_attribute(x) 0
#define __has_declspec_attribute(x) 0
#define __is_identifier(x) 0
#define __has_include_next(x) 0
#define __has_warning(x) 0
#define __building_module(x) 0
#if (__INTELLISENSE_VER < 1400)
 #define __has_include(x) 0
#endif

/* Clang Language Extensions for C++11 */
#define _Atomic(x) x

/* MSVC doesn't support some C++11 features */
#if (__INTELLISENSE_VER < 1400)
 #define alignas(x)
 #define alignof(x) 1
 #define constexpr
 #define noexcept
 #define thread_local
#endif

/* A bug in VS2015's IntelliSense means inline isn't a keyword in C, so redefine it as __inline */
#if (__INTELLISENSE_VER == 1400) && !defined(__cplusplus)
 #define inline __inline
#endif

/* Define away __asm to prevent missing } IntelliSense problem in VS11 when using _SCE_BREAK() and _SCE_STOP() */
#define __asm

/* Prevent stdlib.h defining size_t as this then causes IntelliSense errors in the <new> header */
#if defined(__cplusplus)
 #define _SIZE_T_DECLARED
#endif

/* MSVC doesn't support default constructors. _HAS_FUNCTION_DELETE will be defined as 1 in yvals.h */
/* if not already defined, which then enables default constructors in numerous of SDK headers */
#define _HAS_FUNCTION_DELETE 0

#if (__INTELLISENSE_VER < 1400)
 typedef unsigned short char16_t;
 typedef unsigned int char32_t;
#endif

/* MSVC doesn't support the _Pragma keyword, only __pragma */
#define _intellisense_Pragma(x) __pragma(x)
#define _Pragma(x) _intellisense_Pragma(x)

#define __int128 long long
typedef __int128 __int128_t;
typedef unsigned __int128 __uint128_t;

/* types used in GCC description */

typedef char v8qi;
typedef short v4hi;
typedef int v2si;
typedef long long di;
typedef float v4sf;
typedef int v4si;
typedef double v2df;
typedef float v2sf;
typedef char v16qi;
typedef short v8hi;
typedef long long v2di;
typedef long long v1di;
typedef double v4df;
typedef float v8sf;
typedef int v8si;
typedef char v32qi;
typedef short v16hi;
typedef long long v4di;
typedef float v16sf;
typedef int v16si;
typedef long long v8di;
typedef double v8df;
//typedef int ptest;
typedef char const * pcchar;
typedef double const * pcdouble;
typedef float const * pcfloat;
typedef v2df * pv2df;
typedef char * pchar;
typedef double * pdouble;
typedef short v32hi;
typedef int c8si;
typedef double v2d;
typedef double v4d;
typedef double v8d;
typedef __int64 * pcint64;
typedef float __float128;
typedef v4si * pv4si;
typedef float * pfloat;
typedef v4df * pv4df;
typedef v4sf * pv4sf;
typedef v8sf * pv8sf;
typedef v4di * pv4di;
typedef v8si * pv8si;
typedef v2di * pv2di;
typedef v2di const * pcv2di;
typedef v2df const * pcv2df;
typedef v4df const * pcv4df;
typedef v4sf const * pcv4sf;
typedef v8sf const * pcv8sf;
typedef v8si const * pcv8si;
typedef v4di const * pcv4di;
typedef v4si const * pcv4si;

/* These built-in functions are available for the i386 and x86-64 family of computers, depending on the command-line switches used.

Note that, if you specify command-line switches such as -msse, the compiler could use the extended instruction sets even if the built-ins are not used explicitly in the program. For this reason, applications which perform runtime CPU detection must compile separate files for each supported architecture, using the appropriate flags. In particular, the file containing the CPU detection code should be compiled without these options.

The following machine modes are available for use with MMX built-in functions (see Vector Extensions);: V2SI for a vector of two 32-bit integers, V4HI for a vector of four 16-bit integers, and V8QI for a vector of eight 8-bit integers. Some of the built-in functions operate on MMX registers as a whole 64-bit entity, these use V1DI as their mode.

If 3DNow! extensions are enabled, V2SF is used as a mode for a vector of two 32-bit floating point values.

If SSE extensions are enabled, V4SF is used for a vector of four 32-bit floating point values. Some instructions use a vector of four 32-bit integers, these use V4SI. Finally, some instructions operate on an entire vector register, interpreting it as a 128-bit integer, these use mode TI.

In 64-bit mode, the x86-64 family of processors uses additional built-in functions for efficient use of TF (__float128); 128-bit floating point and TC 128-bit complex floating point values.

The following floating point built-in functions are available in 64-bit mode. All of them implement the function that is part of the name. */

__float128 __builtin_fabsq (__float128);
__float128 __builtin_copysignq (__float128, __float128);

/* The following built-in function is always available. */

void __builtin_ia32_pause (void);

/* The following floating point built-in functions are made available in the 64-bit mode. */

__float128 __builtin_infq (void);
__float128 __builtin_huge_valq (void);

/* The following built-in functions are made available by -mmmx. All of them generate the machine instruction that is part of the name. */

v8qi __builtin_ia32_paddb (v8qi, v8qi);
v4hi __builtin_ia32_paddw (v4hi, v4hi);
v2si __builtin_ia32_paddd (v2si, v2si);
v8qi __builtin_ia32_psubb (v8qi, v8qi);
v4hi __builtin_ia32_psubw (v4hi, v4hi);
v2si __builtin_ia32_psubd (v2si, v2si);
v8qi __builtin_ia32_paddsb (v8qi, v8qi);
v4hi __builtin_ia32_paddsw (v4hi, v4hi);
v8qi __builtin_ia32_psubsb (v8qi, v8qi);
v4hi __builtin_ia32_psubsw (v4hi, v4hi);
v8qi __builtin_ia32_paddusb (v8qi, v8qi);
v4hi __builtin_ia32_paddusw (v4hi, v4hi);
v8qi __builtin_ia32_psubusb (v8qi, v8qi);
v4hi __builtin_ia32_psubusw (v4hi, v4hi);
v4hi __builtin_ia32_pmullw (v4hi, v4hi);
v4hi __builtin_ia32_pmulhw (v4hi, v4hi);
di __builtin_ia32_pand (di, di);
di __builtin_ia32_pandn (di,di);
di __builtin_ia32_por (di, di);
di __builtin_ia32_pxor (di, di);
v8qi __builtin_ia32_pcmpeqb (v8qi, v8qi);
v4hi __builtin_ia32_pcmpeqw (v4hi, v4hi);
v2si __builtin_ia32_pcmpeqd (v2si, v2si);
v8qi __builtin_ia32_pcmpgtb (v8qi, v8qi);
v4hi __builtin_ia32_pcmpgtw (v4hi, v4hi);
v2si __builtin_ia32_pcmpgtd (v2si, v2si);
v8qi __builtin_ia32_punpckhbw (v8qi, v8qi);
v4hi __builtin_ia32_punpckhwd (v4hi, v4hi);
v2si __builtin_ia32_punpckhdq (v2si, v2si);
v8qi __builtin_ia32_punpcklbw (v8qi, v8qi);
v4hi __builtin_ia32_punpcklwd (v4hi, v4hi);
v2si __builtin_ia32_punpckldq (v2si, v2si);
v8qi __builtin_ia32_packsswb (v4hi, v4hi);
v4hi __builtin_ia32_packssdw (v2si, v2si);
v8qi __builtin_ia32_packuswb (v4hi, v4hi);

void __builtin_ia32_emms (void);	// missing from 470 docs
v4hi __builtin_ia32_psllw (v4hi, v4hi);
v2si __builtin_ia32_pslld (v2si, v2si);
v1di __builtin_ia32_psllq (v1di, v1di);
v4hi __builtin_ia32_psrlw (v4hi, v4hi);
v2si __builtin_ia32_psrld (v2si, v2si);
v1di __builtin_ia32_psrlq (v1di, v1di);
v4hi __builtin_ia32_psraw (v4hi, v4hi);
v2si __builtin_ia32_psrad (v2si, v2si);
v4hi __builtin_ia32_psllwi (v4hi, int);
v2si __builtin_ia32_pslldi (v2si, int);
v1di __builtin_ia32_psllqi (v1di, int);
v4hi __builtin_ia32_psrlwi (v4hi, int);
v2si __builtin_ia32_psrldi (v2si, int);
v1di __builtin_ia32_psrlqi (v1di, int);
v4hi __builtin_ia32_psrawi (v4hi, int);
v2si __builtin_ia32_psradi (v2si, int);
v4hi __builtin_ia32_pshufw (v4hi, int);	// missing from 470 docs
v2si __builtin_ia32_pmaddwd (v4hi, v4hi);	// missing from 470 docs
v2si __builtin_ia32_vec_init_v2si (int, int);	// missing from 470 docs
v4hi __builtin_ia32_vec_init_v4hi (short, short, short, short);	// missing from 470 docs
v8qi __builtin_ia32_vec_init_v8qi (char, char, char, char, char, char, char, char);	// missing from 470 docs
int __builtin_ia32_vec_ext_v2si (v2si, int);	// missing from 470 docs

/* The following built-in functions are made available either with -msse, or with a combination of -m3dnow and -march=athlon. All of them generate the machine instruction that is part of the name. */

v4hi __builtin_ia32_pmulhuw (v4hi, v4hi);
v8qi __builtin_ia32_pavgb (v8qi, v8qi);
v4hi __builtin_ia32_pavgw (v4hi, v4hi);
v1di __builtin_ia32_psadbw (v8qi, v8qi);
v8qi __builtin_ia32_pmaxub (v8qi, v8qi);
v4hi __builtin_ia32_pmaxsw (v4hi, v4hi);
v8qi __builtin_ia32_pminub (v8qi, v8qi);
v4hi __builtin_ia32_pminsw (v4hi, v4hi);
/*int __builtin_ia32_pextrw (v4hi, int);
v4hi __builtin_ia32_pinsrw (v4hi, int, int);*/
int __builtin_ia32_pmovmskb (v8qi);
void __builtin_ia32_maskmovq (v8qi, v8qi, char *);
void __builtin_ia32_movntq (di *, di);
void __builtin_ia32_sfence (void);

/* The following built-in functions are available when -msse is used. All of them generate the machine instruction that is part of the name. */

int __builtin_ia32_comieq (v4sf, v4sf);
int __builtin_ia32_comineq (v4sf, v4sf);
int __builtin_ia32_comilt (v4sf, v4sf);
int __builtin_ia32_comile (v4sf, v4sf);
int __builtin_ia32_comigt (v4sf, v4sf);
int __builtin_ia32_comige (v4sf, v4sf);
int __builtin_ia32_ucomieq (v4sf, v4sf);
int __builtin_ia32_ucomineq (v4sf, v4sf);
int __builtin_ia32_ucomilt (v4sf, v4sf);
int __builtin_ia32_ucomile (v4sf, v4sf);
int __builtin_ia32_ucomigt (v4sf, v4sf);
int __builtin_ia32_ucomige (v4sf, v4sf);
/*v4sf __builtin_ia32_addps (v4sf, v4sf);
v4sf __builtin_ia32_subps (v4sf, v4sf);
v4sf __builtin_ia32_mulps (v4sf, v4sf);
v4sf __builtin_ia32_divps (v4sf, v4sf);
v4sf __builtin_ia32_addss (v4sf, v4sf);
v4sf __builtin_ia32_subss (v4sf, v4sf);
v4sf __builtin_ia32_mulss (v4sf, v4sf);
v4sf __builtin_ia32_divss (v4sf, v4sf);*/
v4si __builtin_ia32_cmpeqps (v4sf, v4sf);
v4si __builtin_ia32_cmpltps (v4sf, v4sf);
v4si __builtin_ia32_cmpleps (v4sf, v4sf);
/*v4si __builtin_ia32_cmpgtps (v4sf, v4sf);
v4si __builtin_ia32_cmpgeps (v4sf, v4sf);*/
v4si __builtin_ia32_cmpunordps (v4sf, v4sf);
v4si __builtin_ia32_cmpneqps (v4sf, v4sf);
v4si __builtin_ia32_cmpnltps (v4sf, v4sf);
v4si __builtin_ia32_cmpnleps (v4sf, v4sf);
/*v4si __builtin_ia32_cmpngtps (v4sf, v4sf);
v4si __builtin_ia32_cmpngeps (v4sf, v4sf);*/
v4si __builtin_ia32_cmpordps (v4sf, v4sf);
v4si __builtin_ia32_cmpeqss (v4sf, v4sf);
v4si __builtin_ia32_cmpltss (v4sf, v4sf);
v4si __builtin_ia32_cmpless (v4sf, v4sf);
v4si __builtin_ia32_cmpunordss (v4sf, v4sf);
v4si __builtin_ia32_cmpneqss (v4sf, v4sf);
v4si __builtin_ia32_cmpnlts (v4sf, v4sf);
v4si __builtin_ia32_cmpnless (v4sf, v4sf);
v4si __builtin_ia32_cmpordss (v4sf, v4sf);
v4sf __builtin_ia32_maxps (v4sf, v4sf);
v4sf __builtin_ia32_maxss (v4sf, v4sf);
v4sf __builtin_ia32_minps (v4sf, v4sf);
v4sf __builtin_ia32_minss (v4sf, v4sf);
/*v4sf __builtin_ia32_andps (v4sf, v4sf);
v4sf __builtin_ia32_andnps (v4sf, v4sf);
v4sf __builtin_ia32_orps (v4sf, v4sf);
v4sf __builtin_ia32_xorps (v4sf, v4sf);
v4sf __builtin_ia32_movss (v4sf, v4sf);
v4sf __builtin_ia32_movhlps (v4sf, v4sf);
v4sf __builtin_ia32_movlhps (v4sf, v4sf);
v4sf __builtin_ia32_unpckhps (v4sf, v4sf);
v4sf __builtin_ia32_unpcklps (v4sf, v4sf);*/
v4sf __builtin_ia32_cvtpi2ps (v4sf, v2si);
/*v4sf __builtin_ia32_cvtsi2ss (v4sf, int);*/
v2si __builtin_ia32_cvtps2pi (v4sf);
int __builtin_ia32_cvtss2si (v4sf);
v2si __builtin_ia32_cvttps2pi (v4sf);
int __builtin_ia32_cvttss2si (v4sf);
v4sf __builtin_ia32_rcpps (v4sf);
v4sf __builtin_ia32_rsqrtps (v4sf);
v4sf __builtin_ia32_sqrtps (v4sf);
v4sf __builtin_ia32_rcpss (v4sf);
v4sf __builtin_ia32_rsqrtss (v4sf);
v4sf __builtin_ia32_sqrtss (v4sf);
/*v4sf __builtin_ia32_shufps (v4sf, v4sf, int);*/
void __builtin_ia32_movntps (float *, v4sf);
int __builtin_ia32_movmskps (v4sf);
void __builtin_ia32_ldmxcsr (unsigned);	// missing from 470 docs
unsigned __builtin_ia32_stmxcsr (void);	// missing from 470 docs

/* The following built-in functions are available when -msse is used. */

/*v4sf __builtin_ia32_loadaps (float *);
void __builtin_ia32_storeaps (float *, v4sf);
v4sf __builtin_ia32_loadups (float *);*/
void __builtin_ia32_storeups (float *, v4sf);
/*v4sf __builtin_ia32_loadsss (float *);
void __builtin_ia32_storess (float *, v4sf);
v4sf __builtin_ia32_loadhps (v4sf, const v2sf *);
v4sf __builtin_ia32_loadlps (v4sf, const v2sf *);*/
void __builtin_ia32_storehps (v2sf *, v4sf);
void __builtin_ia32_storelps (v2sf *, v4sf);

/* The following built-in functions are available when -msse2 is used. All of them generate the machine instruction that is part of the name. */

int __builtin_ia32_comisdeq (v2df, v2df);
int __builtin_ia32_comisdlt (v2df, v2df);
int __builtin_ia32_comisdle (v2df, v2df);
int __builtin_ia32_comisdgt (v2df, v2df);
int __builtin_ia32_comisdge (v2df, v2df);
int __builtin_ia32_comisdneq (v2df, v2df);
int __builtin_ia32_ucomisdeq (v2df, v2df);
int __builtin_ia32_ucomisdlt (v2df, v2df);
int __builtin_ia32_ucomisdle (v2df, v2df);
int __builtin_ia32_ucomisdgt (v2df, v2df);
int __builtin_ia32_ucomisdge (v2df, v2df);
int __builtin_ia32_ucomisdneq (v2df, v2df);
v2df __builtin_ia32_cmpeqpd (v2df, v2df);
v2df __builtin_ia32_cmpltpd (v2df, v2df);
v2df __builtin_ia32_cmplepd (v2df, v2df);
/*v2df __builtin_ia32_cmpgtpd (v2df, v2df);
v2df __builtin_ia32_cmpgepd (v2df, v2df);*/
v2df __builtin_ia32_cmpunordpd (v2df, v2df);
v2df __builtin_ia32_cmpneqpd (v2df, v2df);
v2df __builtin_ia32_cmpnltpd (v2df, v2df);
v2df __builtin_ia32_cmpnlepd (v2df, v2df);
/*v2df __builtin_ia32_cmpngtpd (v2df, v2df);
v2df __builtin_ia32_cmpngepd (v2df, v2df);*/
v2df __builtin_ia32_cmpordpd (v2df, v2df);
v2df __builtin_ia32_cmpeqsd (v2df, v2df);
v2df __builtin_ia32_cmpltsd (v2df, v2df);
v2df __builtin_ia32_cmplesd (v2df, v2df);
v2df __builtin_ia32_cmpunordsd (v2df, v2df);
v2df __builtin_ia32_cmpneqsd (v2df, v2df);
v2df __builtin_ia32_cmpnltsd (v2df, v2df);
v2df __builtin_ia32_cmpnlesd (v2df, v2df);
v2df __builtin_ia32_cmpordsd (v2df, v2df);
v2di __builtin_ia32_paddq (v2di, v2di);
v2di __builtin_ia32_psubq (v2di, v2di);
/*v2df __builtin_ia32_addpd (v2df, v2df);
v2df __builtin_ia32_subpd (v2df, v2df);
v2df __builtin_ia32_mulpd (v2df, v2df);
v2df __builtin_ia32_divpd (v2df, v2df);
v2df __builtin_ia32_addsd (v2df, v2df);
v2df __builtin_ia32_subsd (v2df, v2df);
v2df __builtin_ia32_mulsd (v2df, v2df);
v2df __builtin_ia32_divsd (v2df, v2df);*/
v2df __builtin_ia32_minpd (v2df, v2df);
v2df __builtin_ia32_maxpd (v2df, v2df);
v2df __builtin_ia32_minsd (v2df, v2df);
v2df __builtin_ia32_maxsd (v2df, v2df);
/*v2df __builtin_ia32_andpd (v2df, v2df);
v2df __builtin_ia32_andnpd (v2df, v2df);
v2df __builtin_ia32_orpd (v2df, v2df);
v2df __builtin_ia32_xorpd (v2df, v2df);
v2df __builtin_ia32_movsd (v2df, v2df);
v2df __builtin_ia32_unpckhpd (v2df, v2df);
v2df __builtin_ia32_unpcklpd (v2df, v2df);
v16qi __builtin_ia32_paddb128 (v16qi, v16qi);
v8hi __builtin_ia32_paddw128 (v8hi, v8hi);
v4si __builtin_ia32_paddd128 (v4si, v4si);
v2di __builtin_ia32_paddq128 (v2di, v2di);
v16qi __builtin_ia32_psubb128 (v16qi, v16qi);
v8hi __builtin_ia32_psubw128 (v8hi, v8hi);
v4si __builtin_ia32_psubd128 (v4si, v4si);
v2di __builtin_ia32_psubq128 (v2di, v2di);*/
v16qi __builtin_ia32_paddsb128 (v16qi, v16qi);	// missing from 470 docs
v8hi __builtin_ia32_paddsw128 (v8hi, v8hi);	// missing from 470 docs
v16qi __builtin_ia32_psubsb128 (v16qi, v16qi);	// missing from 470 docs
v8hi __builtin_ia32_psubsw128 (v8hi, v8hi);	// missing from 470 docs
v16qi __builtin_ia32_paddusb128 (v16qi, v16qi);	// missing from 470 docs
v8hi __builtin_ia32_paddusw128 (v8hi, v8hi);	// missing from 470 docs
v16qi __builtin_ia32_psubusb128 (v16qi, v16qi);	// missing from 470 docs
v8hi __builtin_ia32_psubusw128 (v8hi, v8hi);	// missing from 470 docs
/*v8hi __builtin_ia32_pmullw128 (v8hi, v8hi);*/
v8hi __builtin_ia32_pmulhw128 (v8hi, v8hi);
/*v2di __builtin_ia32_pand128 (v2di, v2di);
v2di __builtin_ia32_pandn128 (v2di, v2di);
v2di __builtin_ia32_por128 (v2di, v2di);
v2di __builtin_ia32_pxor128 (v2di, v2di);*/
v16qi __builtin_ia32_pavgb128 (v16qi, v16qi);
v8hi __builtin_ia32_pavgw128 (v8hi, v8hi);
v16qi __builtin_ia32_pcmpeqb128 (v16qi, v16qi);
v8hi __builtin_ia32_pcmpeqw128 (v8hi, v8hi);
v4si __builtin_ia32_pcmpeqd128 (v4si, v4si);
v16qi __builtin_ia32_pcmpgtb128 (v16qi, v16qi);
v8hi __builtin_ia32_pcmpgtw128 (v8hi, v8hi);
v4si __builtin_ia32_pcmpgtd128 (v4si, v4si);
v16qi __builtin_ia32_pmaxub128 (v16qi, v16qi);
v8hi __builtin_ia32_pmaxsw128 (v8hi, v8hi);
v16qi __builtin_ia32_pminub128 (v16qi, v16qi);
v8hi __builtin_ia32_pminsw128 (v8hi, v8hi);
/*v16qi __builtin_ia32_punpckhbw128 (v16qi, v16qi);
v8hi __builtin_ia32_punpckhwd128 (v8hi, v8hi);
v4si __builtin_ia32_punpckhdq128 (v4si, v4si);
v2di __builtin_ia32_punpckhqdq128 (v2di, v2di);
v16qi __builtin_ia32_punpcklbw128 (v16qi, v16qi);
v8hi __builtin_ia32_punpcklwd128 (v8hi, v8hi);
v4si __builtin_ia32_punpckldq128 (v4si, v4si);
v2di __builtin_ia32_punpcklqdq128 (v2di, v2di);*/
v16qi __builtin_ia32_packsswb128 (v8hi, v8hi);
v8hi __builtin_ia32_packssdw128 (v4si, v4si);
v16qi __builtin_ia32_packuswb128 (v8hi, v8hi);
v8hi __builtin_ia32_pmulhuw128 (v8hi, v8hi);
void __builtin_ia32_maskmovdqu (v16qi, v16qi, char *);	// fixed from 401. missing last arg
/*v2df __builtin_ia32_loadupd (double *);*/
void __builtin_ia32_storeupd (double *, v2df);
/*v2df __builtin_ia32_loadhpd (v2df, double const *);
v2df __builtin_ia32_loadlpd (v2df, double const *);*/
int __builtin_ia32_movmskpd (v2df);
int __builtin_ia32_pmovmskb128 (v16qi);
void __builtin_ia32_movnti (int *, int);
void __builtin_ia32_movnti64 (long long int *, long long int);
void __builtin_ia32_movntpd (double *, v2df);
void __builtin_ia32_movntdq (v2df *, v2df);
/*v4si __builtin_ia32_pshufd (v4si, int);
v8hi __builtin_ia32_pshuflw (v8hi, int);
v8hi __builtin_ia32_pshufhw (v8hi, int);*/
v2di __builtin_ia32_psadbw128 (v16qi, v16qi);
v2df __builtin_ia32_sqrtpd (v2df);
v2df __builtin_ia32_sqrtsd (v2df);
/*v2df __builtin_ia32_shufpd (v2df, v2df, int);*/
v2df __builtin_ia32_cvtdq2pd (v4si);
v4sf __builtin_ia32_cvtdq2ps (v4si);
v4si __builtin_ia32_cvtpd2dq (v2df);
v2si __builtin_ia32_cvtpd2pi (v2df);
v4sf __builtin_ia32_cvtpd2ps (v2df);
v4si __builtin_ia32_cvttpd2dq (v2df);
v2si __builtin_ia32_cvttpd2pi (v2df);
v2df __builtin_ia32_cvtpi2pd (v2si);
int __builtin_ia32_cvtsd2si (v2df);
int __builtin_ia32_cvttsd2si (v2df);
long long __builtin_ia32_cvtsd2si64 (v2df);
long long __builtin_ia32_cvttsd2si64 (v2df);
v4si __builtin_ia32_cvtps2dq (v4sf);
v2df __builtin_ia32_cvtps2pd (v4sf);
v4si __builtin_ia32_cvttps2dq (v4sf);
/*v2df __builtin_ia32_cvtsi2sd (v2df, int);
v2df __builtin_ia32_cvtsi642sd (v2df, long long);*/
v4sf __builtin_ia32_cvtsd2ss (v4sf, v2df);
/*v2df __builtin_ia32_cvtss2sd (v2df, v4sf);*/
void __builtin_ia32_clflush (const void *);
void __builtin_ia32_lfence (void);
void __builtin_ia32_mfence (void);
v16qi __builtin_ia32_loaddqu (const char *);
void __builtin_ia32_storedqu (char *, v16qi);
v1di __builtin_ia32_pmuludq (v2si, v2si);
v2di __builtin_ia32_pmuludq128 (v4si, v4si);
v8hi __builtin_ia32_psllw128 (v8hi, v8hi);
v4si __builtin_ia32_pslld128 (v4si, v4si);
v2di __builtin_ia32_psllq128 (v2di, v2di);
v8hi __builtin_ia32_psrlw128 (v8hi, v8hi);
v4si __builtin_ia32_psrld128 (v4si, v4si);
v2di __builtin_ia32_psrlq128 (v2di, v2di);
v8hi __builtin_ia32_psraw128 (v8hi, v8hi);
v4si __builtin_ia32_psrad128 (v4si, v4si);
v2di __builtin_ia32_pslldqi128 (v2di, int);
v8hi __builtin_ia32_psllwi128 (v8hi, int);
v4si __builtin_ia32_pslldi128 (v4si, int);
v2di __builtin_ia32_psllqi128 (v2di, int);
v2di __builtin_ia32_psrldqi128 (v2di, int);
v8hi __builtin_ia32_psrlwi128 (v8hi, int);
v4si __builtin_ia32_psrldi128 (v4si, int);
v2di __builtin_ia32_psrlqi128 (v2di, int);
v8hi __builtin_ia32_psrawi128 (v8hi, int);
v4si __builtin_ia32_psradi128 (v4si, int);
v4si __builtin_ia32_pmaddwd128 (v8hi, v8hi);
/*v2di __builtin_ia32_movq128 (v2di);*/

/* The following built-in functions are available when -msse3 is used. All of them generate the machine instruction that is part of the name. */

v2df __builtin_ia32_addsubpd (v2df, v2df);
v4sf __builtin_ia32_addsubps (v4sf, v4sf);
v2df __builtin_ia32_haddpd (v2df, v2df);
v4sf __builtin_ia32_haddps (v4sf, v4sf);
v2df __builtin_ia32_hsubpd (v2df, v2df);
v4sf __builtin_ia32_hsubps (v4sf, v4sf);
v16qi __builtin_ia32_lddqu (char const *);
void __builtin_ia32_monitor (void *, unsigned int, unsigned int);
/*v2df __builtin_ia32_movddup (v2df);
v4sf __builtin_ia32_movshdup (v4sf);
v4sf __builtin_ia32_movsldup (v4sf);*/
void __builtin_ia32_mwait (unsigned int, unsigned int);

/* The following built-in functions are available when -msse3 is used. */

/*v2df __builtin_ia32_loadddup (double const *);*/

/* The following built-in functions are available when -mssse3 is used. All of them generate the machine instruction that is part of the name with MMX registers. */

v2si __builtin_ia32_phaddd (v2si, v2si);
v4hi __builtin_ia32_phaddw (v4hi, v4hi);
v4hi __builtin_ia32_phaddsw (v4hi, v4hi);
v2si __builtin_ia32_phsubd (v2si, v2si);
v4hi __builtin_ia32_phsubw (v4hi, v4hi);
v4hi __builtin_ia32_phsubsw (v4hi, v4hi);
v4hi __builtin_ia32_pmaddubsw (v8qi, v8qi);
v4hi __builtin_ia32_pmulhrsw (v4hi, v4hi);
v8qi __builtin_ia32_pshufb (v8qi, v8qi);
v8qi __builtin_ia32_psignb (v8qi, v8qi);
v2si __builtin_ia32_psignd (v2si, v2si);
v4hi __builtin_ia32_psignw (v4hi, v4hi);
v1di __builtin_ia32_palignr (v1di, v1di, int);
v8qi __builtin_ia32_pabsb (v8qi);
v2si __builtin_ia32_pabsd (v2si);
v4hi __builtin_ia32_pabsw (v4hi);

/* The following built-in functions are available when -mssse3 is used. All of them generate the machine instruction that is part of the name with SSE registers. */

v4si __builtin_ia32_phaddd128 (v4si, v4si);
v8hi __builtin_ia32_phaddw128 (v8hi, v8hi);
v8hi __builtin_ia32_phaddsw128 (v8hi, v8hi);
v4si __builtin_ia32_phsubd128 (v4si, v4si);
v8hi __builtin_ia32_phsubw128 (v8hi, v8hi);
v8hi __builtin_ia32_phsubsw128 (v8hi, v8hi);
v8hi __builtin_ia32_pmaddubsw128 (v16qi, v16qi);
v8hi __builtin_ia32_pmulhrsw128 (v8hi, v8hi);
v16qi __builtin_ia32_pshufb128 (v16qi, v16qi);
v16qi __builtin_ia32_psignb128 (v16qi, v16qi);
v4si __builtin_ia32_psignd128 (v4si, v4si);
v8hi __builtin_ia32_psignw128 (v8hi, v8hi);
v2di __builtin_ia32_palignr128 (v2di, v2di, int);
v16qi __builtin_ia32_pabsb128 (v16qi);
v4si __builtin_ia32_pabsd128 (v4si);
v8hi __builtin_ia32_pabsw128 (v8hi);

/* The following built-in functions are available when -msse4.1 is used. All of them generate the machine instruction that is part of the name. */

v2df __builtin_ia32_blendpd (v2df, v2df, const int);
v4sf __builtin_ia32_blendps (v4sf, v4sf, const int);
v2df __builtin_ia32_blendvpd (v2df, v2df, v2df);
v4sf __builtin_ia32_blendvps (v4sf, v4sf, v4sf);
v2df __builtin_ia32_dppd (v2df, v2df, const int);
v4sf __builtin_ia32_dpps (v4sf, v4sf, const int);
v4sf __builtin_ia32_insertps128 (v4sf, v4sf, const int);
v2di __builtin_ia32_movntdqa (v2di *);
v16qi __builtin_ia32_mpsadbw128 (v16qi, v16qi, const int);
v8hi __builtin_ia32_packusdw128 (v4si, v4si);
v16qi __builtin_ia32_pblendvb128 (v16qi, v16qi, v16qi);
v8hi __builtin_ia32_pblendw128 (v8hi, v8hi, const int);
v2di __builtin_ia32_pcmpeqq (v2di, v2di);
v8hi __builtin_ia32_phminposuw128 (v8hi);
v16qi __builtin_ia32_pmaxsb128 (v16qi, v16qi);
v4si __builtin_ia32_pmaxsd128 (v4si, v4si);
v4si __builtin_ia32_pmaxud128 (v4si, v4si);
v8hi __builtin_ia32_pmaxuw128 (v8hi, v8hi);
v16qi __builtin_ia32_pminsb128 (v16qi, v16qi);
v4si __builtin_ia32_pminsd128 (v4si, v4si);
v4si __builtin_ia32_pminud128 (v4si, v4si);
v8hi __builtin_ia32_pminuw128 (v8hi, v8hi);
v4si __builtin_ia32_pmovsxbd128 (v16qi);
v2di __builtin_ia32_pmovsxbq128 (v16qi);
v8hi __builtin_ia32_pmovsxbw128 (v16qi);
v2di __builtin_ia32_pmovsxdq128 (v4si);
v4si __builtin_ia32_pmovsxwd128 (v8hi);
v2di __builtin_ia32_pmovsxwq128 (v8hi);
v4si __builtin_ia32_pmovzxbd128 (v16qi);
v2di __builtin_ia32_pmovzxbq128 (v16qi);
v8hi __builtin_ia32_pmovzxbw128 (v16qi);
v2di __builtin_ia32_pmovzxdq128 (v4si);
v4si __builtin_ia32_pmovzxwd128 (v8hi);
v2di __builtin_ia32_pmovzxwq128 (v8hi);
v2di __builtin_ia32_pmuldq128 (v4si, v4si);
v4si __builtin_ia32_pmulld128 (v4si, v4si);
int __builtin_ia32_ptestc128 (v2di, v2di);
int __builtin_ia32_ptestnzc128 (v2di, v2di);
int __builtin_ia32_ptestz128 (v2di, v2di);
v2df __builtin_ia32_roundpd (v2df, const int);
v4sf __builtin_ia32_roundps (v4sf, const int);
v2df __builtin_ia32_roundsd (v2df, v2df, const int);
v4sf __builtin_ia32_roundss (v4sf, v4sf, const int);

/* The following built-in functions are available when -msse4.1 is used. */

/*v4sf __builtin_ia32_vec_set_v4sf (v4sf, float, const int);
int __builtin_ia32_vec_ext_v16qi (v16qi, const int);
v16qi __builtin_ia32_vec_set_v16qi (v16qi, int, const int);
v4si __builtin_ia32_vec_set_v4si (v4si, int, const int);
v2di __builtin_ia32_vec_set_v2di (v2di, long long, const int);*/

/* The following built-in functions are changed to generate new SSE4.1 instructions when -msse4.1 is used. */

/*float __builtin_ia32_vec_ext_v4sf (v4sf, const int);
int __builtin_ia32_vec_ext_v4si (v4si, const int);
long long __builtin_ia32_vec_ext_v2di (v2di, const int);*/

/* The following built-in functions are available when -msse4.2 is used. All of them generate the machine instruction that is part of the name. */

v16qi __builtin_ia32_pcmpestrm128 (v16qi, int, v16qi, int, const int);
int __builtin_ia32_pcmpestri128 (v16qi, int, v16qi, int, const int);
int __builtin_ia32_pcmpestria128 (v16qi, int, v16qi, int, const int);
int __builtin_ia32_pcmpestric128 (v16qi, int, v16qi, int, const int);
int __builtin_ia32_pcmpestrio128 (v16qi, int, v16qi, int, const int);
int __builtin_ia32_pcmpestris128 (v16qi, int, v16qi, int, const int);
int __builtin_ia32_pcmpestriz128 (v16qi, int, v16qi, int, const int);
v16qi __builtin_ia32_pcmpistrm128 (v16qi, v16qi, const int);
int __builtin_ia32_pcmpistri128 (v16qi, v16qi, const int);
int __builtin_ia32_pcmpistria128 (v16qi, v16qi, const int);	// ERROR expected 5 args
int __builtin_ia32_pcmpistric128 (v16qi, v16qi, const int);	// ERROR expected 5 args
int __builtin_ia32_pcmpistrio128 (v16qi, v16qi, const int);	// ERROR expected 5 args
int __builtin_ia32_pcmpistris128 (v16qi, v16qi, const int);	// ERROR expected 5 args
int __builtin_ia32_pcmpistriz128 (v16qi, v16qi, const int);
v2di __builtin_ia32_pcmpgtq (v2di, v2di);

/* The following built-in functions are available when -msse4.2 is used. */

unsigned int __builtin_ia32_crc32qi (unsigned int, unsigned char);
unsigned int __builtin_ia32_crc32hi (unsigned int, unsigned short);
unsigned int __builtin_ia32_crc32si (unsigned int, unsigned int);
unsigned long long __builtin_ia32_crc32di (unsigned long long, unsigned long long);

/* The following built-in functions are changed to generate new SSE4.2 instructions when -msse4.2 is used. */

int __builtin_popcount (unsigned int);
int __builtin_popcountl (unsigned long);
int __builtin_popcountll (unsigned long long);

/* The following built-in functions are available when -mavx is used. All of them generate the machine instruction that is part of the name. */

/*v4df __builtin_ia32_addpd256 (v4df,v4df);
v8sf __builtin_ia32_addps256 (v8sf,v8sf);*/
v4df __builtin_ia32_addsubpd256 (v4df,v4df);
v8sf __builtin_ia32_addsubps256 (v8sf,v8sf);
/*v4df __builtin_ia32_andnpd256 (v4df,v4df);
v8sf __builtin_ia32_andnps256 (v8sf,v8sf);
v4df __builtin_ia32_andpd256 (v4df,v4df);
v8sf __builtin_ia32_andps256 (v8sf,v8sf);*/
v4df __builtin_ia32_blendpd256 (v4df,v4df,int);
v8sf __builtin_ia32_blendps256 (v8sf,v8sf,int);
v4df __builtin_ia32_blendvpd256 (v4df,v4df,v4df);
v8sf __builtin_ia32_blendvps256 (v8sf,v8sf,v8sf);
v2df __builtin_ia32_cmppd (v2df,v2df,int);
v4df __builtin_ia32_cmppd256 (v4df,v4df,int);
v4sf __builtin_ia32_cmpps (v4sf,v4sf,int);
v8sf __builtin_ia32_cmpps256 (v8sf,v8sf,int);
v2df __builtin_ia32_cmpsd (v2df,v2df,int);
v4sf __builtin_ia32_cmpss (v4sf,v4sf,int);
v4df __builtin_ia32_cvtdq2pd256 (v4si);
v8sf __builtin_ia32_cvtdq2ps256 (v8si);
v4si __builtin_ia32_cvtpd2dq256 (v4df);
v4sf __builtin_ia32_cvtpd2ps256 (v4df);
v8si __builtin_ia32_cvtps2dq256 (v8sf);
v4df __builtin_ia32_cvtps2pd256 (v4sf);
v4si __builtin_ia32_cvttpd2dq256 (v4df);
v8si __builtin_ia32_cvttps2dq256 (v8sf);
/*v4df __builtin_ia32_divpd256 (v4df,v4df);
v8sf __builtin_ia32_divps256 (v8sf,v8sf);*/
v8sf __builtin_ia32_dpps256 (v8sf,v8sf,int);
v4df __builtin_ia32_haddpd256 (v4df,v4df);
v8sf __builtin_ia32_haddps256 (v8sf,v8sf);
v4df __builtin_ia32_hsubpd256 (v4df,v4df);
v8sf __builtin_ia32_hsubps256 (v8sf,v8sf);
v32qi __builtin_ia32_lddqu256 (pcchar);
v32qi __builtin_ia32_loaddqu256 (pcchar);
v4df __builtin_ia32_loadupd256 (pcdouble);
v8sf __builtin_ia32_loadups256 (pcfloat);
v2df __builtin_ia32_maskloadpd (pcv2df,v2df);
v4df __builtin_ia32_maskloadpd256 (pcv4df,v4df);
v4sf __builtin_ia32_maskloadps (pcv4sf,v4sf);
v8sf __builtin_ia32_maskloadps256 (pcv8sf,v8sf);
void __builtin_ia32_maskstorepd (pv2df,v2df,v2df);
void __builtin_ia32_maskstorepd256 (pv4df,v4df,v4df);
void __builtin_ia32_maskstoreps (pv4sf,v4sf,v4sf);
void __builtin_ia32_maskstoreps256 (pv8sf,v8sf,v8sf);
v4df __builtin_ia32_maxpd256 (v4df,v4df);
v8sf __builtin_ia32_maxps256 (v8sf,v8sf);
v4df __builtin_ia32_minpd256 (v4df,v4df);
v8sf __builtin_ia32_minps256 (v8sf,v8sf);
/*v4df __builtin_ia32_movddup256 (v4df);*/
int __builtin_ia32_movmskpd256 (v4df);
int __builtin_ia32_movmskps256 (v8sf);
/*v8sf __builtin_ia32_movshdup256 (v8sf);
v8sf __builtin_ia32_movsldup256 (v8sf);
v4df __builtin_ia32_mulpd256 (v4df,v4df);
v8sf __builtin_ia32_mulps256 (v8sf,v8sf);
v4df __builtin_ia32_orpd256 (v4df,v4df);
v8sf __builtin_ia32_orps256 (v8sf,v8sf);
v2df __builtin_ia32_pd_pd256 (v4df);
v4df __builtin_ia32_pd256_pd (v2df);
v4sf __builtin_ia32_ps_ps256 (v8sf);
v8sf __builtin_ia32_ps256_ps (v4sf);*/
int __builtin_ia32_ptestc256 (v4di,v4di); //,ptest);	// ERROR expected 2 args
int __builtin_ia32_ptestnzc256 (v4di,v4di);	// ,ptest);	// ERROR expected 2 args
int __builtin_ia32_ptestz256 (v4di,v4di);	//,ptest);	// ERROR expected 2 args
v8sf __builtin_ia32_rcpps256 (v8sf);
v4df __builtin_ia32_roundpd256 (v4df,int);
v8sf __builtin_ia32_roundps256 (v8sf,int);
/*v8sf __builtin_ia32_rsqrtps_nr256 (v8sf);*/
v8sf __builtin_ia32_rsqrtps256 (v8sf);
/*v4df __builtin_ia32_shufpd256 (v4df,v4df,int);
v8sf __builtin_ia32_shufps256 (v8sf,v8sf,int);
v4si __builtin_ia32_si_si256 (v8si);
v8si __builtin_ia32_si256_si (v4si);*/
v4df __builtin_ia32_sqrtpd256 (v4df);
/*v8sf __builtin_ia32_sqrtps_nr256 (v8sf);*/
v8sf __builtin_ia32_sqrtps256 (v8sf);
void __builtin_ia32_storedqu256 (pchar,v32qi);
void __builtin_ia32_storeupd256 (pdouble,v4df);
void __builtin_ia32_storeups256 (pfloat,v8sf);
/*v4df __builtin_ia32_subpd256 (v4df,v4df);
v8sf __builtin_ia32_subps256 (v8sf,v8sf);
v4df __builtin_ia32_unpckhpd256 (v4df,v4df);
v8sf __builtin_ia32_unpckhps256 (v8sf,v8sf);
v4df __builtin_ia32_unpcklpd256 (v4df,v4df);
v8sf __builtin_ia32_unpcklps256 (v8sf,v8sf);*/
v4df __builtin_ia32_vbroadcastf128_pd256 (pcv2df);
v8sf __builtin_ia32_vbroadcastf128_ps256 (pcv4sf);
v4df __builtin_ia32_vbroadcastsd256 (pcdouble);
v4sf __builtin_ia32_vbroadcastss (pcfloat);
v8sf __builtin_ia32_vbroadcastss256 (pcfloat);
v2df __builtin_ia32_vextractf128_pd256 (v4df,int);
v4sf __builtin_ia32_vextractf128_ps256 (v8sf,int);
v4si __builtin_ia32_vextractf128_si256 (v8si,int);
v4df __builtin_ia32_vinsertf128_pd256 (v4df,v2df,int);
v8sf __builtin_ia32_vinsertf128_ps256 (v8sf,v4sf,int);
v8si __builtin_ia32_vinsertf128_si256 (v8si,v4si,int);
v4df __builtin_ia32_vperm2f128_pd256 (v4df,v4df,int);
v8sf __builtin_ia32_vperm2f128_ps256 (v8sf,v8sf,int);
v8si __builtin_ia32_vperm2f128_si256 (v8si,v8si,int);
v2df __builtin_ia32_vpermil2pd (v2df,v2df,v2di,int);
v4df __builtin_ia32_vpermil2pd256 (v4df,v4df,v4di,int);
v4sf __builtin_ia32_vpermil2ps (v4sf,v4sf,v4si,int);
v8sf __builtin_ia32_vpermil2ps256 (v8sf,v8sf,v8si,int);
v2df __builtin_ia32_vpermilpd (v2df,int);
v4df __builtin_ia32_vpermilpd256 (v4df,int);
v4sf __builtin_ia32_vpermilps (v4sf,int);
v8sf __builtin_ia32_vpermilps256 (v8sf,int);
v2df __builtin_ia32_vpermilvarpd (v2df,v2di);
v4df __builtin_ia32_vpermilvarpd256 (v4df,v4di);
v4sf __builtin_ia32_vpermilvarps (v4sf,v4si);
v8sf __builtin_ia32_vpermilvarps256 (v8sf,v8si);
int __builtin_ia32_vtestcpd (v2df,v2df);	//,ptest);	// ERROR expected 2 args
int __builtin_ia32_vtestcpd256 (v4df,v4df);	//,ptest);	// ERROR expected 2 args
int __builtin_ia32_vtestcps (v4sf,v4sf);	//,ptest);	// ERROR expected 2 args
int __builtin_ia32_vtestcps256 (v8sf,v8sf);	//,ptest);	// ERROR expected 2 args
int __builtin_ia32_vtestnzcpd (v2df,v2df);	//,ptest);	// ERROR expected 2 args
int __builtin_ia32_vtestnzcpd256 (v4df,v4df);	//,ptest);	// ERROR expected 2 args
int __builtin_ia32_vtestnzcps (v4sf,v4sf);	//,ptest);	// ERROR expected 2 args
int __builtin_ia32_vtestnzcps256 (v8sf,v8sf);	//,ptest);	// ERROR expected 2 args
int __builtin_ia32_vtestzpd (v2df,v2df);	//,ptest);	// ERROR expected 2 args
int __builtin_ia32_vtestzpd256 (v4df,v4df);	//,ptest);	// ERROR expected 2 args
int __builtin_ia32_vtestzps (v4sf,v4sf);	//,ptest);	// ERROR expected 2 args
int __builtin_ia32_vtestzps256 (v8sf,v8sf);	//,ptest);	// ERROR expected 2 args
void __builtin_ia32_vzeroall (void);
void __builtin_ia32_vzeroupper (void);
/*v4df __builtin_ia32_xorpd256 (v4df,v4df);
v8sf __builtin_ia32_xorps256 (v8sf,v8sf);*/

/* The following built-in functions are available when -mavx2 is used. All of them generate the machine instruction that is part of the name. */

v32qi __builtin_ia32_mpsadbw256 (v32qi,v32qi,v32qi);  //,int);    // ERROR expected 3 args
v32qi __builtin_ia32_pabsb256 (v32qi);
v16hi __builtin_ia32_pabsw256 (v16hi);
v8si __builtin_ia32_pabsd256 (v8si);
v16hi __builtin_ia32_packssdw256 (v8si,v8si);
v32qi __builtin_ia32_packsswb256 (v16hi,v16hi);
v16hi __builtin_ia32_packusdw256 (v8si,v8si);
v32qi __builtin_ia32_packuswb256 (v16hi,v16hi);
/*v32qi __builtin_ia32_paddb256 (v32qi,v32qi);
v16hi __builtin_ia32_paddw256 (v16hi,v16hi);
v8si __builtin_ia32_paddd256 (v8si,v8si);
v4di __builtin_ia32_paddq256 (v4di,v4di);*/
v32qi __builtin_ia32_paddsb256 (v32qi,v32qi);
v16hi __builtin_ia32_paddsw256 (v16hi,v16hi);
v32qi __builtin_ia32_paddusb256 (v32qi,v32qi);
v16hi __builtin_ia32_paddusw256 (v16hi,v16hi);
v4di __builtin_ia32_palignr256 (v4di,v4di,int);
/*v4di __builtin_ia32_andsi256 (v4di,v4di);
v4di __builtin_ia32_andnotsi256 (v4di,v4di);*/
v32qi __builtin_ia32_pavgb256 (v32qi,v32qi);
v16hi __builtin_ia32_pavgw256 (v16hi,v16hi);
v32qi __builtin_ia32_pblendvb256 (v32qi,v32qi,v32qi);
/*v16hi __builtin_ia32_pblendw256 (v16hi,v16hi,int);
v32qi __builtin_ia32_pcmpeqb256 (v32qi,v32qi);
v16hi __builtin_ia32_pcmpeqw256 (v16hi,v16hi);
v8si __builtin_ia32_pcmpeqd256 (c8si,v8si);
v4di __builtin_ia32_pcmpeqq256 (v4di,v4di);
v32qi __builtin_ia32_pcmpgtb256 (v32qi,v32qi);*/
v16hi __builtin_ia32_pcmpgtw256 (v16hi,v16hi);
/*v8si __builtin_ia32_pcmpgtd256 (v8si,v8si);
v4di __builtin_ia32_pcmpgtq256 (v4di,v4di);*/
v16hi __builtin_ia32_phaddw256 (v16hi,v16hi);
v8si __builtin_ia32_phaddd256 (v8si,v8si);
v16hi __builtin_ia32_phaddsw256 (v16hi,v16hi);
v16hi __builtin_ia32_phsubw256 (v16hi,v16hi);
v8si __builtin_ia32_phsubd256 (v8si,v8si);
v16hi __builtin_ia32_phsubsw256 (v16hi,v16hi);
v32qi __builtin_ia32_pmaddubsw256 (v32qi,v32qi);
v16hi __builtin_ia32_pmaddwd256 (v16hi,v16hi);
v32qi __builtin_ia32_pmaxsb256 (v32qi,v32qi);
v16hi __builtin_ia32_pmaxsw256 (v16hi,v16hi);
v8si __builtin_ia32_pmaxsd256 (v8si,v8si);
v32qi __builtin_ia32_pmaxub256 (v32qi,v32qi);
v16hi __builtin_ia32_pmaxuw256 (v16hi,v16hi);
v8si __builtin_ia32_pmaxud256 (v8si,v8si);
v32qi __builtin_ia32_pminsb256 (v32qi,v32qi);
v16hi __builtin_ia32_pminsw256 (v16hi,v16hi);
v8si __builtin_ia32_pminsd256 (v8si,v8si);
v32qi __builtin_ia32_pminub256 (v32qi,v32qi);
v16hi __builtin_ia32_pminuw256 (v16hi,v16hi);
v8si __builtin_ia32_pminud256 (v8si,v8si);
int __builtin_ia32_pmovmskb256 (v32qi);
/*v16hi __builtin_ia32_pmovsxbw256 (v16qi);
v8si __builtin_ia32_pmovsxbd256 (v16qi);
v4di __builtin_ia32_pmovsxbq256 (v16qi);
v8si __builtin_ia32_pmovsxwd256 (v8hi);
v4di __builtin_ia32_pmovsxwq256 (v8hi);
v4di __builtin_ia32_pmovsxdq256 (v4si);
v16hi __builtin_ia32_pmovzxbw256 (v16qi);
v8si __builtin_ia32_pmovzxbd256 (v16qi);
v4di __builtin_ia32_pmovzxbq256 (v16qi);
v8si __builtin_ia32_pmovzxwd256 (v8hi);
v4di __builtin_ia32_pmovzxwq256 (v8hi);
v4di __builtin_ia32_pmovzxdq256 (v4si);*/
v4di __builtin_ia32_pmuldq256 (v8si,v8si);
v16hi __builtin_ia32_pmulhrsw256 (v16hi, v16hi);
v16hi __builtin_ia32_pmulhuw256 (v16hi,v16hi);
v16hi __builtin_ia32_pmulhw256 (v16hi,v16hi);
/*v16hi __builtin_ia32_pmullw256 (v16hi,v16hi);
v8si __builtin_ia32_pmulld256 (v8si,v8si);*/
v4di __builtin_ia32_pmuludq256 (v8si,v8si);
/*v4di __builtin_ia32_por256 (v4di,v4di);*/
v16hi __builtin_ia32_psadbw256 (v32qi,v32qi);
v32qi __builtin_ia32_pshufb256 (v32qi,v32qi);
/*v8si __builtin_ia32_pshufd256 (v8si,int);
v16hi __builtin_ia32_pshufhw256 (v16hi,int);
v16hi __builtin_ia32_pshuflw256 (v16hi,int);*/
v32qi __builtin_ia32_psignb256 (v32qi,v32qi);
v16hi __builtin_ia32_psignw256 (v16hi,v16hi);
v8si __builtin_ia32_psignd256 (v8si,v8si);
/*v4di __builtin_ia32_pslldqi256 (v4di,int);*/
v16hi __builtin_ia32_psllwi256 (v16hi,int);
v16hi __builtin_ia32_psllw256(v16hi,v8hi);
v8si __builtin_ia32_pslldi256 (v8si,int);
v8si __builtin_ia32_pslld256(v8si,v4si);
v4di __builtin_ia32_psllqi256 (v4di,int);
v4di __builtin_ia32_psllq256(v4di,v2di);
v16hi __builtin_ia32_psrawi256 (v16hi,int);
v16hi __builtin_ia32_psraw256 (v16hi,v8hi);
v8si __builtin_ia32_psradi256 (v8si,int);
v8si __builtin_ia32_psrad256 (v8si,v4si);
v4di __builtin_ia32_psrldqi256 (v4di, int);
v16hi __builtin_ia32_psrlwi256 (v16hi,int);
v16hi __builtin_ia32_psrlw256 (v16hi,v8hi);
v8si __builtin_ia32_psrldi256 (v8si,int);
v8si __builtin_ia32_psrld256 (v8si,v4si);
v4di __builtin_ia32_psrlqi256 (v4di,int);
v4di __builtin_ia32_psrlq256(v4di,v2di);
/*v32qi __builtin_ia32_psubb256 (v32qi,v32qi);
v32hi __builtin_ia32_psubw256 (v16hi,v16hi);
v8si __builtin_ia32_psubd256 (v8si,v8si);
v4di __builtin_ia32_psubq256 (v4di,v4di);*/
v32qi __builtin_ia32_psubsb256 (v32qi,v32qi);
v16hi __builtin_ia32_psubsw256 (v16hi,v16hi);
v32qi __builtin_ia32_psubusb256 (v32qi,v32qi);
v16hi __builtin_ia32_psubusw256 (v16hi,v16hi);
/*v32qi __builtin_ia32_punpckhbw256 (v32qi,v32qi);
v16hi __builtin_ia32_punpckhwd256 (v16hi,v16hi);
v8si __builtin_ia32_punpckhdq256 (v8si,v8si);
v4di __builtin_ia32_punpckhqdq256 (v4di,v4di);
v32qi __builtin_ia32_punpcklbw256 (v32qi,v32qi);
v16hi __builtin_ia32_punpcklwd256 (v16hi,v16hi);
v8si __builtin_ia32_punpckldq256 (v8si,v8si);
v4di __builtin_ia32_punpcklqdq256 (v4di,v4di);
v4di __builtin_ia32_pxor256 (v4di,v4di);*/
v4di __builtin_ia32_movntdqa256 (pv4di);
/*v4sf __builtin_ia32_vbroadcastss_ps (v4sf);
v8sf __builtin_ia32_vbroadcastss_ps256 (v4sf);
v4df __builtin_ia32_vbroadcastsd_pd256 (v2df);
v4di __builtin_ia32_vbroadcastsi256 (v2di);
v4si __builtin_ia32_pblendd128 (v4si,v4si);
v8si __builtin_ia32_pblendd256 (v8si,v8si);
v32qi __builtin_ia32_pbroadcastb256 (v16qi);
v16hi __builtin_ia32_pbroadcastw256 (v8hi);
v8si __builtin_ia32_pbroadcastd256 (v4si);
v4di __builtin_ia32_pbroadcastq256 (v2di);
v16qi __builtin_ia32_pbroadcastb128 (v16qi);
v8hi __builtin_ia32_pbroadcastw128 (v8hi);
v4si __builtin_ia32_pbroadcastd128 (v4si);
v2di __builtin_ia32_pbroadcastq128 (v2di);*/
v8si __builtin_ia32_permvarsi256 (v8si,v8si);
/*v4df __builtin_ia32_permdf256 (v4df,int);*/
v8sf __builtin_ia32_permvarsf256 (v8sf,v8sf);
/*v4di __builtin_ia32_permdi256 (v4di,int);*/
v4di __builtin_ia32_permti256 (v4di,v4di,int);
/*v4di __builtin_ia32_extract128i256 (v4di,int);
v4di __builtin_ia32_insert128i256 (v4di,v2di,int);*/
v8si __builtin_ia32_maskloadd256 (pcv8si,v8si);
v4di __builtin_ia32_maskloadq256 (pcv4di,v4di);
v4si __builtin_ia32_maskloadd (pcv4si,v4si);
v2di __builtin_ia32_maskloadq (pcv2di,v2di);
void __builtin_ia32_maskstored256 (pv8si,v8si,v8si);
void __builtin_ia32_maskstoreq256 (pv4di,v4di,v4di);
void __builtin_ia32_maskstored (pv4si,v4si,v4si);
void __builtin_ia32_maskstoreq (pv2di,v2di,v2di);
v8si __builtin_ia32_psllv8si (v8si,v8si);
v4si __builtin_ia32_psllv4si (v4si,v4si);
v4di __builtin_ia32_psllv4di (v4di,v4di);
v2di __builtin_ia32_psllv2di (v2di,v2di);
v8si __builtin_ia32_psrav8si (v8si,v8si);
v4si __builtin_ia32_psrav4si (v4si,v4si);
v8si __builtin_ia32_psrlv8si (v8si,v8si);
v4si __builtin_ia32_psrlv4si (v4si,v4si);
v4di __builtin_ia32_psrlv4di (v4di,v4di);
v2di __builtin_ia32_psrlv2di (v2di,v2di);
/*v2df __builtin_ia32_gathersiv2df (v2df, pcdouble,v4si,v2df,int);
v4df __builtin_ia32_gathersiv4df (v4df, pcdouble,v4si,v4df,int);
v2df __builtin_ia32_gatherdiv2df (v2df, pcdouble,v2di,v2df,int);
v4df __builtin_ia32_gatherdiv4df (v4df, pcdouble,v4di,v4df,int);
v4sf __builtin_ia32_gathersiv4sf (v4sf, pcfloat,v4si,v4sf,int);
v8sf __builtin_ia32_gathersiv8sf (v8sf, pcfloat,v8si,v8sf,int);
v4sf __builtin_ia32_gatherdiv4sf (v4sf, pcfloat,v2di,v4sf,int);
v4sf __builtin_ia32_gatherdiv4sf256 (v4sf, pcfloat,v4di,v4sf,int);
v2di __builtin_ia32_gathersiv2di (v2di, pcint64,v4si,v2di,int);
v4di __builtin_ia32_gathersiv4di (v4di, pcint64,v4si,v4di,int);
v2di __builtin_ia32_gatherdiv2di (v2di, pcint64,v2di,v2di,int);
v4di __builtin_ia32_gatherdiv4di (v4di, pcint64,v4di,v4di,int);
v4si __builtin_ia32_gathersiv4si (v4si, pcint,v4si,v4si,int);
v8si __builtin_ia32_gathersiv8si (v8si, pcint,v8si,v8si,int);
v4si __builtin_ia32_gatherdiv4si (v4si, pcint,v2di,v4si,int);
v4si __builtin_ia32_gatherdiv4si256 (v4si, pcint,v4di,v4si,int);*/

/* The following built-in functions are available when -maes is used. All of them generate the machine instruction that is part of the name. */

v2di __builtin_ia32_aesenc128 (v2di, v2di);
v2di __builtin_ia32_aesenclast128 (v2di, v2di);
v2di __builtin_ia32_aesdec128 (v2di, v2di);
v2di __builtin_ia32_aesdeclast128 (v2di, v2di);
v2di __builtin_ia32_aeskeygenassist128 (v2di, const int);
v2di __builtin_ia32_aesimc128 (v2di);

/* The following built-in function is available when -mpclmul is used. */

v2di __builtin_ia32_pclmulqdq128 (v2di, v2di, const int);

/* The following built-in function is available when -mfsgsbase is used. All of them generate the machine instruction that is part of the name. */

unsigned int __builtin_ia32_rdfsbase32 (void);
unsigned long long __builtin_ia32_rdfsbase64 (void);
unsigned int __builtin_ia32_rdgsbase32 (void);
unsigned long long __builtin_ia32_rdgsbase64 (void);
/*void _writefsbase_u32 (unsigned int);
void _writefsbase_u64 (unsigned long long);
void _writegsbase_u32 (unsigned int);
void _writegsbase_u64 (unsigned long long);*/

/* The following built-in function is available when -mrdrnd is used. All of them generate the machine instruction that is part of the name. */

unsigned int __builtin_ia32_rdrand16_step (unsigned short *);
unsigned int __builtin_ia32_rdrand32_step (unsigned int *);
unsigned int __builtin_ia32_rdrand64_step (unsigned long long *);

/* The following built-in functions are available when -msse4a is used. All of them generate the machine instruction that is part of the name. */

void __builtin_ia32_movntsd (double *, v2df);
void __builtin_ia32_movntss (float *, v4sf);
v2di __builtin_ia32_extrq  (v2di, v16qi);
v2di __builtin_ia32_extrqi (v2di, const unsigned int, const unsigned int);
v2di __builtin_ia32_insertq (v2di, v2di);
v2di __builtin_ia32_insertqi (v2di, v2di, const unsigned int, const unsigned int);

/* The following built-in functions are available when -mxop is used. */

v2df __builtin_ia32_vfrczpd (v2df);
v4sf __builtin_ia32_vfrczps (v4sf);
v2df __builtin_ia32_vfrczsd (v2df, v2df);
v4sf __builtin_ia32_vfrczss (v4sf, v4sf);
v4df __builtin_ia32_vfrczpd256 (v4df);
v8sf __builtin_ia32_vfrczps256 (v8sf);
v2di __builtin_ia32_vpcmov (v2di, v2di, v2di);
v2di __builtin_ia32_vpcmov_v2di (v2di, v2di, v2di);
v4si __builtin_ia32_vpcmov_v4si (v4si, v4si, v4si);
v8hi __builtin_ia32_vpcmov_v8hi (v8hi, v8hi, v8hi);
v16qi __builtin_ia32_vpcmov_v16qi (v16qi, v16qi, v16qi);
v2df __builtin_ia32_vpcmov_v2df (v2df, v2df, v2df);
v4sf __builtin_ia32_vpcmov_v4sf (v4sf, v4sf, v4sf);
v4di __builtin_ia32_vpcmov_v4di256 (v4di, v4di, v4di);
v8si __builtin_ia32_vpcmov_v8si256 (v8si, v8si, v8si);
/*v16hi __builtin_ia32_vpcmov_v16hi256 (v16hi, v16hi, v16hi);*/
v32qi __builtin_ia32_vpcmov_v32qi256 (v32qi, v32qi, v32qi);
v4df __builtin_ia32_vpcmov_v4df256 (v4df, v4df, v4df);
v8sf __builtin_ia32_vpcmov_v8sf256 (v8sf, v8sf, v8sf);
/*v16qi __builtin_ia32_vpcomeqb (v16qi, v16qi);
v8hi __builtin_ia32_vpcomeqw (v8hi, v8hi);
v4si __builtin_ia32_vpcomeqd (v4si, v4si);
v2di __builtin_ia32_vpcomeqq (v2di, v2di);
v16qi __builtin_ia32_vpcomequb (v16qi, v16qi);
v4si __builtin_ia32_vpcomequd (v4si, v4si);
v2di __builtin_ia32_vpcomequq (v2di, v2di);
v8hi __builtin_ia32_vpcomequw (v8hi, v8hi);
v8hi __builtin_ia32_vpcomeqw (v8hi, v8hi);
v16qi __builtin_ia32_vpcomfalseb (v16qi, v16qi);
v4si __builtin_ia32_vpcomfalsed (v4si, v4si);
v2di __builtin_ia32_vpcomfalseq (v2di, v2di);
v16qi __builtin_ia32_vpcomfalseub (v16qi, v16qi);
v4si __builtin_ia32_vpcomfalseud (v4si, v4si);
v2di __builtin_ia32_vpcomfalseuq (v2di, v2di);
v8hi __builtin_ia32_vpcomfalseuw (v8hi, v8hi);
v8hi __builtin_ia32_vpcomfalsew (v8hi, v8hi);
v16qi __builtin_ia32_vpcomgeb (v16qi, v16qi);
v4si __builtin_ia32_vpcomged (v4si, v4si);
v2di __builtin_ia32_vpcomgeq (v2di, v2di);
v16qi __builtin_ia32_vpcomgeub (v16qi, v16qi);
v4si __builtin_ia32_vpcomgeud (v4si, v4si);
v2di __builtin_ia32_vpcomgeuq (v2di, v2di);
v8hi __builtin_ia32_vpcomgeuw (v8hi, v8hi);
v8hi __builtin_ia32_vpcomgew (v8hi, v8hi);
v16qi __builtin_ia32_vpcomgtb (v16qi, v16qi);
v4si __builtin_ia32_vpcomgtd (v4si, v4si);
v2di __builtin_ia32_vpcomgtq (v2di, v2di);
v16qi __builtin_ia32_vpcomgtub (v16qi, v16qi);
v4si __builtin_ia32_vpcomgtud (v4si, v4si);
v2di __builtin_ia32_vpcomgtuq (v2di, v2di);
v8hi __builtin_ia32_vpcomgtuw (v8hi, v8hi);
v8hi __builtin_ia32_vpcomgtw (v8hi, v8hi);
v16qi __builtin_ia32_vpcomleb (v16qi, v16qi);
v4si __builtin_ia32_vpcomled (v4si, v4si);
v2di __builtin_ia32_vpcomleq (v2di, v2di);
v16qi __builtin_ia32_vpcomleub (v16qi, v16qi);
v4si __builtin_ia32_vpcomleud (v4si, v4si);
v2di __builtin_ia32_vpcomleuq (v2di, v2di);
v8hi __builtin_ia32_vpcomleuw (v8hi, v8hi);
v8hi __builtin_ia32_vpcomlew (v8hi, v8hi);
v16qi __builtin_ia32_vpcomltb (v16qi, v16qi);
v4si __builtin_ia32_vpcomltd (v4si, v4si);
v2di __builtin_ia32_vpcomltq (v2di, v2di);
v16qi __builtin_ia32_vpcomltub (v16qi, v16qi);
v4si __builtin_ia32_vpcomltud (v4si, v4si);
v2di __builtin_ia32_vpcomltuq (v2di, v2di);
v8hi __builtin_ia32_vpcomltuw (v8hi, v8hi);
v8hi __builtin_ia32_vpcomltw (v8hi, v8hi);
v16qi __builtin_ia32_vpcomneb (v16qi, v16qi);
v4si __builtin_ia32_vpcomned (v4si, v4si);
v2di __builtin_ia32_vpcomneq (v2di, v2di);
v16qi __builtin_ia32_vpcomneub (v16qi, v16qi);
v4si __builtin_ia32_vpcomneud (v4si, v4si);
v2di __builtin_ia32_vpcomneuq (v2di, v2di);
v8hi __builtin_ia32_vpcomneuw (v8hi, v8hi);
v8hi __builtin_ia32_vpcomnew (v8hi, v8hi);
v16qi __builtin_ia32_vpcomtrueb (v16qi, v16qi);
v4si __builtin_ia32_vpcomtrued (v4si, v4si);
v2di __builtin_ia32_vpcomtrueq (v2di, v2di);
v16qi __builtin_ia32_vpcomtrueub (v16qi, v16qi);
v4si __builtin_ia32_vpcomtrueud (v4si, v4si);
v2di __builtin_ia32_vpcomtrueuq (v2di, v2di);
v8hi __builtin_ia32_vpcomtrueuw (v8hi, v8hi);
v8hi __builtin_ia32_vpcomtruew (v8hi, v8hi);*/
v4si __builtin_ia32_vphaddbd (v16qi);
v2di __builtin_ia32_vphaddbq (v16qi);
v8hi __builtin_ia32_vphaddbw (v16qi);
v2di __builtin_ia32_vphadddq (v4si);
v4si __builtin_ia32_vphaddubd (v16qi);
v2di __builtin_ia32_vphaddubq (v16qi);
v8hi __builtin_ia32_vphaddubw (v16qi);
v2di __builtin_ia32_vphaddudq (v4si);
v4si __builtin_ia32_vphadduwd (v8hi);
v2di __builtin_ia32_vphadduwq (v8hi);
v4si __builtin_ia32_vphaddwd (v8hi);
v2di __builtin_ia32_vphaddwq (v8hi);
v8hi __builtin_ia32_vphsubbw (v16qi);
v2di __builtin_ia32_vphsubdq (v4si);
v4si __builtin_ia32_vphsubwd (v8hi);
v4si __builtin_ia32_vpmacsdd (v4si, v4si, v4si);
v2di __builtin_ia32_vpmacsdqh (v4si, v4si, v2di);
v2di __builtin_ia32_vpmacsdql (v4si, v4si, v2di);
v4si __builtin_ia32_vpmacssdd (v4si, v4si, v4si);
v2di __builtin_ia32_vpmacssdqh (v4si, v4si, v2di);
v2di __builtin_ia32_vpmacssdql (v4si, v4si, v2di);
v4si __builtin_ia32_vpmacsswd (v8hi, v8hi, v4si);
v8hi __builtin_ia32_vpmacssww (v8hi, v8hi, v8hi);
v4si __builtin_ia32_vpmacswd (v8hi, v8hi, v4si);
v8hi __builtin_ia32_vpmacsww (v8hi, v8hi, v8hi);
v4si __builtin_ia32_vpmadcsswd (v8hi, v8hi, v4si);
v4si __builtin_ia32_vpmadcswd (v8hi, v8hi, v4si);
v16qi __builtin_ia32_vpperm (v16qi, v16qi, v16qi);
v16qi __builtin_ia32_vprotb (v16qi, v16qi);
v4si __builtin_ia32_vprotd (v4si, v4si);
v2di __builtin_ia32_vprotq (v2di, v2di);
v8hi __builtin_ia32_vprotw (v8hi, v8hi);
v16qi __builtin_ia32_vpshab (v16qi, v16qi);
v4si __builtin_ia32_vpshad (v4si, v4si);
v2di __builtin_ia32_vpshaq (v2di, v2di);
v8hi __builtin_ia32_vpshaw (v8hi, v8hi);
v16qi __builtin_ia32_vpshlb (v16qi, v16qi);
v4si __builtin_ia32_vpshld (v4si, v4si);
v2di __builtin_ia32_vpshlq (v2di, v2di);
v8hi __builtin_ia32_vpshlw (v8hi, v8hi);

/* The following built-in functions are available when -mfma4 is used. All of them generate the machine instruction that is part of the name with MMX registers. */

/*v2df __builtin_ia32_fmaddpd (v2df, v2df, v2df);
v4sf __builtin_ia32_fmaddps (v4sf, v4sf, v4sf);
v2df __builtin_ia32_fmaddsd (v2df, v2df, v2df);
v4sf __builtin_ia32_fmaddss (v4sf, v4sf, v4sf);
v2df __builtin_ia32_fmsubpd (v2df, v2df, v2df);
v4sf __builtin_ia32_fmsubps (v4sf, v4sf, v4sf);
v2df __builtin_ia32_fmsubsd (v2df, v2df, v2df);
v4sf __builtin_ia32_fmsubss (v4sf, v4sf, v4sf);
v2df __builtin_ia32_fnmaddpd (v2df, v2df, v2df);
v4sf __builtin_ia32_fnmaddps (v4sf, v4sf, v4sf);
v2df __builtin_ia32_fnmaddsd (v2df, v2df, v2df);
v4sf __builtin_ia32_fnmaddss (v4sf, v4sf, v4sf);
v2df __builtin_ia32_fnmsubpd (v2df, v2df, v2df);
v4sf __builtin_ia32_fnmsubps (v4sf, v4sf, v4sf);
v2df __builtin_ia32_fnmsubsd (v2df, v2df, v2df);
v4sf __builtin_ia32_fnmsubss (v4sf, v4sf, v4sf);
v2df __builtin_ia32_fmaddsubpd  (v2df, v2df, v2df);
v4sf __builtin_ia32_fmaddsubps  (v4sf, v4sf, v4sf);
v2df __builtin_ia32_fmsubaddpd  (v2df, v2df, v2df);
v4sf __builtin_ia32_fmsubaddps  (v4sf, v4sf, v4sf);
v4df __builtin_ia32_fmaddpd256 (v4df, v4df, v4df);
v8sf __builtin_ia32_fmaddps256 (v8sf, v8sf, v8sf);
v4df __builtin_ia32_fmsubpd256 (v4df, v4df, v4df);
v8sf __builtin_ia32_fmsubps256 (v8sf, v8sf, v8sf);
v4df __builtin_ia32_fnmaddpd256 (v4df, v4df, v4df);
v8sf __builtin_ia32_fnmaddps256 (v8sf, v8sf, v8sf);
v4df __builtin_ia32_fnmsubpd256 (v4df, v4df, v4df);
v8sf __builtin_ia32_fnmsubps256 (v8sf, v8sf, v8sf);
v4df __builtin_ia32_fmaddsubpd256 (v4df, v4df, v4df);
v8sf __builtin_ia32_fmaddsubps256 (v8sf, v8sf, v8sf);
v4df __builtin_ia32_fmsubaddpd256 (v4df, v4df, v4df);
v8sf __builtin_ia32_fmsubaddps256 (v8sf, v8sf, v8sf);*/

/* The following built-in functions are available when -mlwp is used. */

/*void __builtin_ia32_llwpcb16 (void *);
void __builtin_ia32_llwpcb32 (void *);
void __builtin_ia32_llwpcb64 (void *);
void * __builtin_ia32_llwpcb16 (void);
void * __builtin_ia32_llwpcb32 (void);
void * __builtin_ia32_llwpcb64 (void);
void __builtin_ia32_lwpval16 (unsigned short, unsigned int, unsigned short);
void __builtin_ia32_lwpval32 (unsigned int, unsigned int, unsigned int);
void __builtin_ia32_lwpval64 (unsigned __int64, unsigned int, unsigned int);
unsigned char __builtin_ia32_lwpins16 (unsigned short, unsigned int, unsigned short);
unsigned char __builtin_ia32_lwpins32 (unsigned int, unsigned int, unsigned int);
unsigned char __builtin_ia32_lwpins64 (unsigned __int64, unsigned int, unsigned int);*/

/* The following built-in functions are available when -mbmi is used. All of them generate the machine instruction that is part of the name. */

unsigned int __builtin_ia32_bextr_u32(unsigned int, unsigned int);
unsigned long long __builtin_ia32_bextr_u64 (unsigned long long, unsigned long long);

/* The following built-in functions are available when -mbmi2 is used. All of them generate the machine instruction that is part of the name. */

/*unsigned int _bzhi_u32 (unsigned int, unsigned int);
unsigned int _pdep_u32 (unsigned int, unsigned int);
unsigned int _pext_u32 (unsigned int, unsigned int);
unsigned long long _bzhi_u64 (unsigned long long, unsigned long long);
unsigned long long _pdep_u64 (unsigned long long, unsigned long long);
unsigned long long _pext_u64 (unsigned long long, unsigned long long);*/

/* The following built-in functions are available when -mlzcnt is used. All of them generate the machine instruction that is part of the name. */

/*unsigned short __builtin_ia32_lzcnt_16(unsigned short);
unsigned int __builtin_ia32_lzcnt_u32(unsigned int);
unsigned long long __builtin_ia32_lzcnt_u64 (unsigned long long);*/

/* The following built - in functions are available when - mlzcnt is used.All of them generate the machine instruction that is part of the name. */

/*unsigned short __builtin_ia32_lzcnt_16(unsigned short);
unsigned int __builtin_ia32_lzcnt_u32(unsigned int);
unsigned long long __builtin_ia32_lzcnt_u64(unsigned long long);*/

/* The following built - in functions are available when - mfxsr is used.All of them generate the machine instruction that is part of the name. */

void __builtin_ia32_fxsave(void *);
void __builtin_ia32_fxrstor(void *);
void __builtin_ia32_fxsave64(void *);
void __builtin_ia32_fxrstor64(void *);

/* The following built - in functions are available when - mxsave is used.All of them generate the machine instruction that is part of the name. */

void __builtin_ia32_xsave(void *, long long);
void __builtin_ia32_xrstor(void *, long long);
void __builtin_ia32_xsave64(void *, long long);
void __builtin_ia32_xrstor64(void *, long long);

/* The following built - in functions are available when - mxsaveopt is used.All of them generate the machine instruction that is part of the name. */

void __builtin_ia32_xsaveopt(void *, long long);
void __builtin_ia32_xsaveopt64(void *, long long);

/* The following built-in functions are available when -mtbm is used. Both of them generate the immediate form of the bextr machine instruction. */

unsigned int __builtin_ia32_bextri_u32 (unsigned int, const unsigned int);
unsigned long long __builtin_ia32_bextri_u64 (unsigned long long, const unsigned long long);

/* The following built-in functions are available when -m3dnow is used. All of them generate the machine instruction that is part of the name. */

void __builtin_ia32_femms (void);
v8qi __builtin_ia32_pavgusb (v8qi, v8qi);
v2si __builtin_ia32_pf2id (v2sf);
v2sf __builtin_ia32_pfacc (v2sf, v2sf);
v2sf __builtin_ia32_pfadd (v2sf, v2sf);
v2si __builtin_ia32_pfcmpeq (v2sf, v2sf);
v2si __builtin_ia32_pfcmpge (v2sf, v2sf);
v2si __builtin_ia32_pfcmpgt (v2sf, v2sf);
v2sf __builtin_ia32_pfmax (v2sf, v2sf);
v2sf __builtin_ia32_pfmin (v2sf, v2sf);
v2sf __builtin_ia32_pfmul (v2sf, v2sf);
v2sf __builtin_ia32_pfrcp (v2sf);
v2sf __builtin_ia32_pfrcpit1 (v2sf, v2sf);
v2sf __builtin_ia32_pfrcpit2 (v2sf, v2sf);
v2sf __builtin_ia32_pfrsqrt (v2sf);
v2sf __builtin_ia32_pfrsqrtit1 (v2sf, v2sf);
v2sf __builtin_ia32_pfsub (v2sf, v2sf);
v2sf __builtin_ia32_pfsubr (v2sf, v2sf);
v2sf __builtin_ia32_pi2fd (v2si);
v4hi __builtin_ia32_pmulhrw (v4hi, v4hi);

/* The following built-in functions are available when both -m3dnow and -march=athlon are used. All of them generate the machine instruction that is part of the name. */

v2si __builtin_ia32_pf2iw (v2sf);
v2sf __builtin_ia32_pfnacc (v2sf, v2sf);
v2sf __builtin_ia32_pfpnacc (v2sf, v2sf);
v2sf __builtin_ia32_pi2fw (v2si);
v2sf __builtin_ia32_pswapdsf (v2sf);
v2si __builtin_ia32_pswapdsi (v2si);

/* Additional built-in functions */

v2d __builtin_ia32_undef128 (void);
v4d __builtin_ia32_undef256 (void);
v8d __builtin_ia32_undef512(void);
unsigned long long __builtin_ia32_rdtsc (void);
unsigned long long __builtin_ia32_rdtscp (unsigned*);
void __builtin_ia32_xsaves (void*, long long);
void __builtin_ia32_xrstors (void*, long long);
void __builtin_ia32_xsavec (void*, long long);
void __builtin_ia32_xrstors64 (void*, long long);
void __builtin_ia32_xsavec64 (void*, long long);
void __builtin_ia32_compressstoresf512_mask (v16sf*, v16sf, short);
void __builtin_ia32_compressstoresi512_mask (v16si*, v16si, short);
void __builtin_ia32_compressstoredf512_mask (v8df*, v8df, char);
void __builtin_ia32_compressstoredi512_mask (v8di*, v8di, char);
v16sf __builtin_ia32_expandloadsf512_mask (const v16sf*, v16sf, short);
v16si __builtin_ia32_expandloadsi512_mask (const v16si*, v16si, short);
v8df __builtin_ia32_expandloaddf512_mask (const v8df*, v8df, char);
v8di __builtin_ia32_expandloaddi512_mask (const v8di*, v8di, char);
v16si __builtin_ia32_loaddqusi512_mask (const v16si*, v16si, short);
v8di __builtin_ia32_loaddqudi512_mask (const v8di*, v8di, char);
v8df __builtin_ia32_loadupd512_mask (const v8df*, v8df, char);
v16sf __builtin_ia32_loadups512_mask (const v16sf*, v16sf, short);
v16sf __builtin_ia32_loadaps512_mask (const v16sf*, v16sf, short);
v16si __builtin_ia32_movdqa32load512_mask (const v16si*, v16si, short);
v8df __builtin_ia32_loadapd512_mask (const v8df*, v8df, char);
v8di __builtin_ia32_movdqa64load512_mask (const v8di*, v8di, char);
v8di __builtin_ia32_movntdqa512 (v8di*);
void __builtin_ia32_storedqusi512_mask (v16si*, v16si, short);
void __builtin_ia32_storedqudi512_mask (v8di*, v8di, char);
void __builtin_ia32_storeupd512_mask (v8df*, v8df, char);
void __builtin_ia32_pmovusqd512mem_mask (v8si*, v8di, char);
void __builtin_ia32_pmovsqd512mem_mask (v8si*, v8di, char);
void __builtin_ia32_pmovqd512mem_mask (v8si*, v8di, char);
void __builtin_ia32_pmovusqw512mem_mask (v8hi*, v8di, char);
void __builtin_ia32_pmovsqw512mem_mask (v8hi*, v8di, char);
void __builtin_ia32_pmovqw512mem_mask (v8hi*, v8di, char);
void __builtin_ia32_pmovusdw512mem_mask (v16hi*, v16si, short);
void __builtin_ia32_pmovsdw512mem_mask (v16hi*, v16si, short);
void __builtin_ia32_pmovdw512mem_mask (v16hi*, v16si, short);
void __builtin_ia32_pmovqb512mem_mask (v16qi*, v8di, char);
void __builtin_ia32_pmovusqb512mem_mask (v16qi*, v8di, char);
void __builtin_ia32_pmovsqb512mem_mask (v16qi*, v8di, char);
void __builtin_ia32_pmovusdb512mem_mask (v16qi*, v16si, short);
void __builtin_ia32_pmovsdb512mem_mask (v16qi*, v16si, short);
void __builtin_ia32_pmovdb512mem_mask (v16qi*, v16si, short);
void __builtin_ia32_storeups512_mask (v16sf*, v16sf, short);
void __builtin_ia32_storeaps512_mask (v16sf*, v16sf, short);
void __builtin_ia32_movdqa32store512_mask (v16si*, v16si, short);
void __builtin_ia32_storeapd512_mask (v8df*, v8df, char);
void __builtin_ia32_movdqa64store512_mask (v8di*, v8di, char);
void __builtin_ia32_wrfsbase32 (unsigned);
void __builtin_ia32_wrfsbase64 (unsigned long long);
void __builtin_ia32_wrgsbase32 (unsigned);
void __builtin_ia32_wrgsbase64 (unsigned long long);
unsigned __builtin_ia32_xbegin (void);
void __builtin_ia32_xend (void);
int __builtin_ia32_xtest (void);
unsigned long long __builtin_ia32_rdpmc (int);
v2si __builtin_ia32_pfrsqit1 (v2sf, v2sf);
v4sf __builtin_ia32_vcvtph2ps(v8hi);
v8sf __builtin_ia32_vcvtph2ps256(v8hi);
v8hi __builtin_ia32_vcvtps2ph(v4sf, int);
v8hi __builtin_ia32_vcvtps2ph256 (v8sf, int);
unsigned __builtin_ia32_bzhi_si (unsigned, unsigned);
unsigned long long __builtin_ia32_bzhi_di (unsigned long long, unsigned long long);
unsigned __builtin_ia32_pdep_si (unsigned, unsigned);
unsigned long long __builtin_ia32_pdep_di (unsigned long long, unsigned long long);
unsigned __builtin_ia32_pext_si (unsigned, unsigned);
unsigned long long __builtin_ia32_pext_di (unsigned long long, unsigned long long);
v16si __builtin_ia32_alignd512_mask (v16si, v16si, int, v16si, short);
v8di __builtin_ia32_alignq512_mask (v8di, v8di, int, v8di, char);
v16sf __builtin_ia32_broadcastf32x4_512 (v4sf, v16sf, short);
v8df __builtin_ia32_broadcastf64x4_512 (v4df, v8df, char);
v16si __builtin_ia32_broadcasti32x4_512 (v4si, v16si, short);
v8di __builtin_ia32_broadcasti64x4_512 (v4di, v8di, char);
short __builtin_ia32_cmpd512_mask (v16si, v16si, int, short);
char __builtin_ia32_cmpq512_mask (v8di, v8di, int, char);
v8df __builtin_ia32_compressdf512_mask (v8df, v8df, char);
v16sf __builtin_ia32_compresssf512_mask (v16sf, v16sf, short);
v8df __builtin_ia32_cvtdq2pd512_mask (v8si, v8df, char);
v16hi __builtin_ia32_vcvtps2ph512_mask (v16sf, int, v16hi, short);
v8df __builtin_ia32_cvtudq2pd512_mask (v8si, v8df, char);
v2df __builtin_ia32_cvtusi2sd32 (v2df, unsigned);
v8df __builtin_ia32_expanddf512_mask (v8df, v8df, char);
v16sf __builtin_ia32_expandsf512_mask (v16sf, v16sf, short);
v4sf __builtin_ia32_extractf32x4_mask (v16sf, int, v4sf, char);
v4df __builtin_ia32_extractf64x4_mask (v8df, int, v4df, char);
v4si __builtin_ia32_extracti32x4_mask (v16si, int, v4si, char);
v4di __builtin_ia32_extracti64x4_mask (v8di, int, v4di, char);
v16sf __builtin_ia32_insertf32x4_mask (v16sf, v4sf, int, v16sf, short);
v8df __builtin_ia32_insertf64x4_mask (v8df, v4df, int, v8df, char);
v16si __builtin_ia32_inserti32x4_mask (v16si, v4si, int, v16si, short);
v8di __builtin_ia32_inserti64x4_mask (v8di, v4di, int, v8di, char);
v16sf __builtin_ia32_movaps512_mask (v16sf, v16sf, short);
v8df __builtin_ia32_movddup512_mask (v8df, v8df, char);
v16si __builtin_ia32_movdqa32_512_mask (v16si, v16si, short);
v8di __builtin_ia32_movdqa64_512_mask (v8di, v8di, char);
v16sf __builtin_ia32_movshdup512_mask (v16sf, v16sf, short);
v16sf __builtin_ia32_movsldup512_mask (v16sf, v16sf, short);
v16si __builtin_ia32_pabsd512_mask (v16si, v16si, short);
v8di __builtin_ia32_pabsq512_mask (v8di, v8di, char);
v16si __builtin_ia32_paddd512_mask (v16si, v16si, v16si, short);
v8di __builtin_ia32_paddq512_mask (v8di, v8di, v8di, char);
v16si __builtin_ia32_pandd512_mask (v16si, v16si, v16si, short);
v16si __builtin_ia32_pandnd512_mask (v16si, v16si, v16si, short);
v8di __builtin_ia32_pandnq512_mask (v8di, v8di, v8di, char);
v8di __builtin_ia32_pandq512_mask (v8di, v8di, v8di, char);
v16si __builtin_ia32_pbroadcastd512 (v4si, v16si, short);
v16si __builtin_ia32_pbroadcastd512_gpr_mask (int, v16si, short);
v8di __builtin_ia32_pbroadcastq512_gpr_mask (long long, v8di, char);
v8di __builtin_ia32_pbroadcastq512_mem_mask (long long, v8di, char);
short __builtin_ia32_pcmpeqd512_mask (v16si, v16si, short);
char __builtin_ia32_pcmpeqq512_mask (v8di, v8di, char);
short __builtin_ia32_pcmpgtd512_mask (v16si, v16si, short);
char __builtin_ia32_pcmpgtq512_mask (v8di, v8di, char);
v16si __builtin_ia32_compresssi512_mask (v16si, v16si, short);
v8di __builtin_ia32_compressdi512_mask (v8di, v8di, char);
v16si __builtin_ia32_expandsi512_mask (v16si, v16si, short);
v8di __builtin_ia32_expanddi512_mask (v8di, v8di, char);
v16si __builtin_ia32_pmaxsd512_mask (v16si, v16si, v16si, short);
v8di __builtin_ia32_pmaxsq512_mask (v8di, v8di, v8di, char);
v16si __builtin_ia32_pmaxud512_mask (v16si, v16si, v16si, short);
v8di __builtin_ia32_pmaxuq512_mask (v8di, v8di, v8di, char);
v16si __builtin_ia32_pminsd512_mask (v16si, v16si, v16si, short);
v8di __builtin_ia32_pminsq512_mask (v8di, v8di, v8di, char);
v16si __builtin_ia32_pminud512_mask (v16si, v16si, v16si, short);
v8di __builtin_ia32_pminuq512_mask (v8di, v8di, v8di, char);
v16qi __builtin_ia32_pmovdb512_mask (v16si, v16qi, short);
v16hi __builtin_ia32_pmovdw512_mask (v16si, v16hi, short);
v16qi __builtin_ia32_pmovqb512_mask (v8di, v16qi, char);
v8si __builtin_ia32_pmovqd512_mask (v8di, v8si, char);
v8hi __builtin_ia32_pmovqw512_mask (v8di, v8hi, char);
v16qi __builtin_ia32_pmovsdb512_mask (v16si, v16qi, short);
v16hi __builtin_ia32_pmovsdw512_mask (v16si, v16hi, short);
v16qi __builtin_ia32_pmovsqb512_mask (v8di, v16qi, char);
v8si __builtin_ia32_pmovsqd512_mask (v8di, v8si, char);
v8hi __builtin_ia32_pmovsqw512_mask (v8di, v8hi, char);
v16si __builtin_ia32_pmovsxbd512_mask (v16qi, v16si, short);
v8di __builtin_ia32_pmovsxbq512_mask (v16qi, v8di, char);
v8di __builtin_ia32_pmovsxdq512_mask (v8si, v8di, char);
v16si __builtin_ia32_pmovsxwd512_mask (v16hi, v16si, short);
v8di __builtin_ia32_pmovsxwq512_mask (v8hi, v8di, char);
v16qi __builtin_ia32_pmovusdb512_mask (v16si, v16qi, short);
v16hi __builtin_ia32_pmovusdw512_mask (v16si, v16hi, short);
v16qi __builtin_ia32_pmovusqb512_mask (v8di, v16qi, char);
v8si __builtin_ia32_pmovusqd512_mask (v8di, v8si, char);
v8hi __builtin_ia32_pmovusqw512_mask (v8di, v8hi, char);
v16si __builtin_ia32_pmovzxbd512_mask (v16qi, v16si, short);
v8di __builtin_ia32_pmovzxbq512_mask (v16qi, v8di, char);
v8di __builtin_ia32_pmovzxdq512_mask (v8si, v8di, char);
v16si __builtin_ia32_pmovzxwd512_mask (v16hi, v16si, short);
v8di __builtin_ia32_pmovzxwq512_mask (v8hi, v8di, char);
v8di __builtin_ia32_pmuldq512_mask (v16si, v16si, v8di, char);
v16si __builtin_ia32_pmulld512_mask (v16si, v16si, v16si, short);
v8di __builtin_ia32_pmuludq512_mask (v16si, v16si, v8di, char);
v16si __builtin_ia32_prold512_mask (v16si, int, v16si, short);
v8di __builtin_ia32_prolq512_mask (v8di, int, v8di, char);
v16si __builtin_ia32_prolvd512_mask (v16si, v16si, v16si, short);
v8di __builtin_ia32_prolvq512_mask (v8di, v8di, v8di, char);
v16si __builtin_ia32_prord512_mask (v16si, int, v16si, short);
v8di __builtin_ia32_prorq512_mask (v8di, int, v8di, char);
v16si __builtin_ia32_prorvd512_mask (v16si, v16si, v16si, short);
v8di __builtin_ia32_prorvq512_mask (v8di, v8di, v8di, char);
v16si __builtin_ia32_pslld512_mask (v16si, v4si, v16si, short);
v16si __builtin_ia32_pslldi512_mask (v16si, int, v16si, short);
v8di __builtin_ia32_psllq512_mask (v8di, v2di , v8di, char);
v8di __builtin_ia32_psllqi512_mask (v8di, int, v8di, char);
v16si __builtin_ia32_psllv16si_mask (v16si, v16si, v16si, short);
v8di __builtin_ia32_psllv8di_mask (v8di, v8di, v8di, char);
v16si __builtin_ia32_psrad512_mask (v16si, v4si, v16si, short);
v16si __builtin_ia32_psradi512_mask (v16si, int, v16si, short);
v8di __builtin_ia32_psraq512_mask (v8di, v2di , v8di, char);
v8di __builtin_ia32_psraqi512_mask (v8di, int, v8di, char);
v16si __builtin_ia32_psrav16si_mask (v16si, v16si, v16si, short);
v8di __builtin_ia32_psrav8di_mask (v8di, v8di, v8di, char);
v16si __builtin_ia32_psrld512_mask (v16si, v4si, v16si, short);
v16si __builtin_ia32_psrldi512_mask (v16si, int, v16si, short);
v8di __builtin_ia32_psrlq512_mask (v8di, v2di , v8di, char);
v8di __builtin_ia32_psrlqi512_mask (v8di, int, v8di, char);
v16si __builtin_ia32_psrlv16si_mask (v16si, v16si, v16si, short);
v8di __builtin_ia32_psrlv8di_mask (v8di, v8di, v8di, char);
v16si __builtin_ia32_psubd512_mask (v16si, v16si, v16si, short);
v8di __builtin_ia32_psubq512_mask (v8di, v8di, v8di, char);
short __builtin_ia32_ptestmd512 (v16si, v16si, short);
char __builtin_ia32_ptestmq512 (v8di, v8di, char);
short __builtin_ia32_ptestnmd512 (v16si, v16si, short);
char __builtin_ia32_ptestnmq512 (v8di, v8di, char);
v8df __builtin_ia32_rcp14pd512_mask (v8df, v8df, char);
v16sf __builtin_ia32_rcp14ps512_mask (v16sf, v16sf, short);
v8df __builtin_ia32_rsqrt14pd512_mask (v8df, v8df, char);
v16sf __builtin_ia32_rsqrt14ps512_mask (v16sf, v16sf, short);
v16sf __builtin_ia32_shuf_f32x4_mask (v16sf, v16sf, int, v16sf, short);
v8df __builtin_ia32_shuf_f64x2_mask (v8df, v8df, int, v8df, char);
v16si __builtin_ia32_shuf_i32x4_mask (v16si, v16si, int, v16si, short);
v8di __builtin_ia32_shuf_i64x2_mask (v8di, v8di, int, v8di, char);
short __builtin_ia32_ucmpd512_mask (v16si, v16si, int, short);
char __builtin_ia32_ucmpq512_mask (v8di, v8di, int, char);
v16si __builtin_ia32_vplzcntd_512_mask (v16si, v16si, short);
v8di __builtin_ia32_vplzcntq_512_mask (v8di, v8di, char);
v16si __builtin_ia32_vpconflictsi_512_mask (v16si, v16si, short);
v8di __builtin_ia32_vpconflictdi_512_mask (v8di, v8di, char);
v16si __builtin_ia32_vpermi2vard512_mask (v16si, v16si, v16si, short);
v8df __builtin_ia32_vpermi2varpd512_mask (v8df, v8di, v8df, char);
v16sf __builtin_ia32_vpermi2varps512_mask (v16sf, v16si, v16sf, short);
v8di __builtin_ia32_vpermi2varq512_mask (v8di, v8di, v8di, char);
v8df __builtin_ia32_vpermilvarpd512_mask (v8df, v8di, v8df, char);
v16sf __builtin_ia32_vpermilvarps512_mask (v16sf, v16si, v16sf, short);
v16si __builtin_ia32_vpermt2vard512_mask (v16si, v16si, v16si, short);
v16si __builtin_ia32_vpermt2vard512_maskz (v16si, v16si, v16si, short);
v8df __builtin_ia32_vpermt2varpd512_mask (v8di, v8df, v8df, char);
v8df __builtin_ia32_vpermt2varpd512_maskz (v8di, v8df, v8df, char);
v16sf __builtin_ia32_vpermt2varps512_mask (v16si, v16sf, v16sf, short);
v16sf __builtin_ia32_vpermt2varps512_maskz (v16si, v16sf, v16sf, short);
v8di __builtin_ia32_vpermt2varq512_mask (v8di, v8di, v8di, char);
v8di __builtin_ia32_vpermt2varq512_maskz (v8di, v8di, v8di, char);
v8df __builtin_ia32_permvardf512_mask (v8df, v8di, v8df, char);
v8di __builtin_ia32_permvardi512_mask (v8di, v8di, v8di, char);
v16sf __builtin_ia32_permvarsf512_mask (v16sf, v16si, v16sf, short);
v16si __builtin_ia32_permvarsi512_mask (v16si, v16si, v16si, short);
v16si __builtin_ia32_pternlogd512_mask (v16si, v16si, v16si, int, short);
v16si __builtin_ia32_pternlogd512_maskz (v16si, v16si, v16si, int, short);
v8di __builtin_ia32_pternlogq512_mask (v8di, v8di, v8di, int, char);
v8di __builtin_ia32_pternlogq512_maskz (v8di, v8di, v8di, int, char);
short __builtin_ia32_kandhi (short, short);
short __builtin_ia32_kandnhi (short, short);
short __builtin_ia32_knothi (short);
short __builtin_ia32_korhi (short, short);
short __builtin_ia32_kortestchi (short, short);
short __builtin_ia32_kortestzhi (short, short);
short __builtin_ia32_kunpckhi (short, short);
short __builtin_ia32_kxnorhi (short, short);
short __builtin_ia32_kxorhi (short, short);
v8df __builtin_ia32_addpd512_mask (v8df, v8df, v8df, char, int);
v16sf __builtin_ia32_addps512_mask (v16sf, v16sf, v16sf, short, int);
char __builtin_ia32_cmppd512_mask (v8df, v8df, int, char, int);
short __builtin_ia32_cmpps512_mask (v16sf, v16sf, int, short, int);
char __builtin_ia32_cmpsd_mask (v2df, v2df, int, char, int);
char __builtin_ia32_cmpss_mask (v4sf, v4sf, int, char, int);
int __builtin_ia32_vcomisd (v2df, v2df, int, int);
int __builtin_ia32_vcomiss (v4sf, v4sf, int, int);
v16sf __builtin_ia32_cvtdq2ps512_mask (v16si, v16sf, short, int);
v8si __builtin_ia32_cvtpd2dq512_mask (v8df, v8si, char, int);
v8sf __builtin_ia32_cvtpd2ps512_mask (v8df, v8sf, char, int);
v8si __builtin_ia32_cvtpd2udq512_mask (v8df, v8si, char, int);
v16sf __builtin_ia32_vcvtph2ps512_mask (v16hi, v16sf, short, int);
v16si __builtin_ia32_cvtps2dq512_mask (v16sf, v16si, short, int);
v8df __builtin_ia32_cvtps2pd512_mask (v8sf, v8df, char, int);
v16si __builtin_ia32_cvtps2udq512_mask (v16sf, v16si, short, int);
v2df __builtin_ia32_cvtsi2sd64 (v2df, long long, int);
v4sf __builtin_ia32_cvtsi2ss32 (v4sf, int, int);
v4sf __builtin_ia32_cvtsi2ss64 (v4sf, long long, int);
v8si __builtin_ia32_cvttpd2dq512_mask (v8df, v8si, char, int);
v8si __builtin_ia32_cvttpd2udq512_mask (v8df, v8si, char, int);
v16si __builtin_ia32_cvttps2dq512_mask (v16sf, v16si, short, int);
v16si __builtin_ia32_cvttps2udq512_mask (v16sf, v16si, short, int);
v16sf __builtin_ia32_cvtudq2ps512_mask (v16si, v16sf, short, int);
v2df __builtin_ia32_cvtusi2sd64 (v2df, unsigned long long, int);
v4sf __builtin_ia32_cvtusi2ss32 (v4sf, unsigned, int);
v4sf __builtin_ia32_cvtusi2ss64 (v4sf, unsigned long long, int);
v8df __builtin_ia32_divpd512_mask (v8df, v8df, v8df, char, int);
v16sf __builtin_ia32_divps512_mask (v16sf, v16sf, v16sf, short, int);
v8df __builtin_ia32_fixupimmpd512_mask (v8df, v8df, v8di, int, char, int);
v8df __builtin_ia32_fixupimmpd512_maskz (v8df, v8df, v8di, int, char, int);
v16sf __builtin_ia32_fixupimmps512_mask (v16sf, v16sf, v16si, int, short, int);
v16sf __builtin_ia32_fixupimmps512_maskz (v16sf, v16sf, v16si, int, short, int);
v2df __builtin_ia32_fixupimmsd_mask (v2df, v2df, v2di , int, char, int);
v2df __builtin_ia32_fixupimmsd_maskz (v2df, v2df, v2di , int, char, int);
v4sf __builtin_ia32_fixupimmss_mask (v4sf, v4sf, v4si, int, char, int);
v4sf __builtin_ia32_fixupimmss_maskz (v4sf, v4sf, v4si, int, char, int);
v8df __builtin_ia32_getexppd512_mask (v8df, v8df, char, int);
v16sf __builtin_ia32_getexpps512_mask (v16sf, v16sf, short, int);
v8df __builtin_ia32_getmantpd512_mask (v8df, int, v8df, char, int);
v16sf __builtin_ia32_getmantps512_mask (v16sf, int, v16sf, short, int);
v8df __builtin_ia32_maxpd512_mask (v8df, v8df, v8df, char, int);
v16sf __builtin_ia32_maxps512_mask (v16sf, v16sf, v16sf, short, int);
v8df __builtin_ia32_minpd512_mask (v8df, v8df, v8df, char, int);
v16sf __builtin_ia32_minps512_mask (v16sf, v16sf, v16sf, short, int);
v8df __builtin_ia32_mulpd512_mask (v8df, v8df, v8df, char, int);
v16sf __builtin_ia32_mulps512_mask (v16sf, v16sf, v16sf, short, int);
v8df __builtin_ia32_rndscalepd_mask (v8df, int, v8df, char, int);
v16sf __builtin_ia32_rndscaleps_mask (v16sf, int, v16sf, short, int);
v8df __builtin_ia32_scalefpd512_mask (v8df, v8df, v8df, char, int);
v16sf __builtin_ia32_scalefps512_mask (v16sf, v16sf, v16sf, short, int);
v8df __builtin_ia32_sqrtpd512_mask (v8df, v8df, char, int);
v16sf __builtin_ia32_sqrtps512_mask (v16sf, v16sf, short, int);
v8df __builtin_ia32_subpd512_mask (v8df, v8df, v8df, char, int);
v16sf __builtin_ia32_subps512_mask (v16sf, v16sf, v16sf, short, int);
int __builtin_ia32_vcvtsd2si32 (v2df, int);
long long __builtin_ia32_vcvtsd2si64 (v2df, int);
unsigned __builtin_ia32_vcvtsd2usi32 (v2df, int);
unsigned long long __builtin_ia32_vcvtsd2usi64 (v2df, int);
int __builtin_ia32_vcvtss2si32 (v4sf, int);
long long __builtin_ia32_vcvtss2si64 (v4sf, int);
unsigned __builtin_ia32_vcvtss2usi32 (v4sf, int);
unsigned long long __builtin_ia32_vcvtss2usi64 (v4sf, int);
int __builtin_ia32_vcvttsd2si32 (v2df, int);
long long __builtin_ia32_vcvttsd2si64 (v2df, int);
unsigned __builtin_ia32_vcvttsd2usi32 (v2df, int);
unsigned long long __builtin_ia32_vcvttsd2usi64 (v2df, int);
int __builtin_ia32_vcvttss2si32 (v4sf, int);
long long __builtin_ia32_vcvttss2si64 (v4sf, int);
unsigned __builtin_ia32_vcvttss2usi32 (v4sf, int);
unsigned long long __builtin_ia32_vcvttss2usi64 (v4sf, int);
v8df __builtin_ia32_vfmaddpd512_mask (v8df, v8df, v8df, char, int);
v8df __builtin_ia32_vfmaddpd512_mask3 (v8df, v8df, v8df, char, int);
v8df __builtin_ia32_vfmaddpd512_maskz (v8df, v8df, v8df, char, int);
v16sf __builtin_ia32_vfmaddps512_mask (v16sf, v16sf, v16sf, short, int);
v16sf __builtin_ia32_vfmaddps512_mask3 (v16sf, v16sf, v16sf, short, int);
v16sf __builtin_ia32_vfmaddps512_maskz (v16sf, v16sf, v16sf, short, int);
v8df __builtin_ia32_vfmaddsubpd512_mask (v8df, v8df, v8df, char, int);
v8df __builtin_ia32_vfmaddsubpd512_mask3 (v8df, v8df, v8df, char, int);
v8df __builtin_ia32_vfmaddsubpd512_maskz (v8df, v8df, v8df, char, int);
v16sf __builtin_ia32_vfmaddsubps512_mask (v16sf, v16sf, v16sf, short, int);
v16sf __builtin_ia32_vfmaddsubps512_mask3 (v16sf, v16sf, v16sf, short, int);
v16sf __builtin_ia32_vfmaddsubps512_maskz (v16sf, v16sf, v16sf, short, int);
v8df __builtin_ia32_vfmsubaddpd512_mask3 (v8df, v8df, v8df, char, int);
v16sf __builtin_ia32_vfmsubaddps512_mask3 (v16sf, v16sf, v16sf, short, int);
v8df __builtin_ia32_vfmsubpd512_mask3 (v8df, v8df, v8df, char, int);
v16sf __builtin_ia32_vfmsubps512_mask3 (v16sf, v16sf, v16sf, short, int);
v8df __builtin_ia32_vfnmaddpd512_mask (v8df, v8df, v8df, char, int);
v16sf __builtin_ia32_vfnmaddps512_mask (v16sf, v16sf, v16sf, short, int);
v8df __builtin_ia32_vfnmsubpd512_mask (v8df, v8df, v8df, char, int);
v8df __builtin_ia32_vfnmsubpd512_mask3 (v8df, v8df, v8df, char, int);
v16sf __builtin_ia32_vfnmsubps512_mask (v16sf, v16sf, v16sf, short, int);
v16sf __builtin_ia32_vfnmsubps512_mask3 (v16sf, v16sf, v16sf, short, int);
v8df __builtin_ia32_exp2pd_mask (v8df, v8df, char, int);
v16sf __builtin_ia32_exp2ps_mask (v16sf, v16sf, short, int);
v8df __builtin_ia32_rcp28pd_mask (v8df, v8df, char, int);
v16sf __builtin_ia32_rcp28ps_mask (v16sf, v16sf, short, int);
v8df __builtin_ia32_rsqrt28pd_mask (v8df, v8df, char, int);
v16sf __builtin_ia32_rsqrt28ps_mask (v16sf, v16sf, short, int);

/* Clang built-in extensions */

typedef signed char __intellisense_int8t;
typedef short __intellisense_int16t;
typedef int __intellisense_int32t;
typedef long __intellisense_int64t;
typedef long long __intellisense_int128t;

typedef unsigned char __intellisense_uint8t;
typedef unsigned short __intellisense_uint16t;
typedef unsigned int __intellisense_uint32t;
typedef unsigned long __intellisense_uint64t;
typedef unsigned long long __intellisense_uint128t;

#if !defined(__cplusplus)
 typedef int __intellisense_type;
 typedef int __intellisense_type1;
 typedef int __intellisense_type2;
 typedef int __intellisense_type3;
 #define size_t int
 #define bool int
#endif

/* Other built-in GCC extensions */

/*int __builtin_types_compatible_p (type1, type2);*/
#define __intellisense__builtin_types_compatible_p(type1, type2) 1
#define __builtin_types_compatible_p(type1, type2) __intellisense__builtin_types_compatible_p(type1, type2)
/*type __builtin_choose_expr (const_exp, exp1, exp2);*/
#define __intellisense__builtin_choose_expr(const_exp, exp1, exp2) (void)0
#define __builtin_choose_expr(const_exp, exp1, exp2) __intellisense__builtin_choose_expr(const_exp, exp1, exp2)
/*int __builtin_constant_p (exp);*/
#define __intellisense__builtin_constant_p(exp) 1
#define __builtin_constant_p(exp) __intellisense__builtin_constant_p(exp)
long __builtin_expect (long exp, long c);
void __builtin_prefetch (const void *addr, ...);
double __builtin_huge_val (void);
float __builtin_huge_valf (void);
long double __builtin_huge_vall (void);
double __builtin_inf (void);
float __builtin_inff (void);
long double __builtin_infl (void);
double __builtin_nan (const char *str);
float __builtin_nanf (const char *str);
long double __builtin_nanl (const char *str);
double __builtin_nans (const char *str);
float __builtin_nansf (const char *str);
long double __builtin_nansl (const char *str);

int __builtin_isgreater (float, float);
int __builtin_isgreaterequal (float, float);
int __builtin_isless (float, float);
int __builtin_islessequal (float, float);
int __builtin_islessgreater (float, float);
int __builtin_isunordered (float, float);
int __builtin_fpclassify (int, int, int, int, int, float);
int __builtin_isfinite (float);
int __builtin_isinf (float);
int __builtin_isinf_sign (float);
int __builtin_isnan (float);
int __builtin_isnormal (float);
int __builtin_signbit (double);
int __builtin_signbitf (float);
int __builtin_signbitl (long double);
int __builtin_clzs (unsigned short);
int __builtin_clz (unsigned int);
int __builtin_clzl (unsigned long);
int __builtin_clzll (unsigned long long);
int __builtin_ctzs (unsigned short);
int __builtin_ctz (unsigned int);
int __builtin_ctzl (unsigned long);
int __builtin_ctzll (unsigned long long);
int __builtin_ffs (int);
int __builtin_ffsl (long);
int __builtin_ffsll (long long);
int __builtin_parity (unsigned int);
int __builtin_parityl (unsigned long);
int __builtin_parityll (unsigned long long);

double __builtin_powi (double, int);
float __builtin_powif (float, int);
long double __builtin_powil (long double, int);
__intellisense_uint16t __builtin_bswap16 (__intellisense_uint16t x);
__intellisense_uint32t __builtin_bswap32 (__intellisense_uint32t x);
__intellisense_uint64t __builtin_bswap64 (__intellisense_uint64t x);

/* Additional built-in GCC extensions */

typedef char * __builtin_va_list;
#define __intellisense__builtin_va_start(__builtin_va_list, format) 0
#define __builtin_va_start(__builtin_va_list, format) __intellisense__builtin_va_start(__builtin_va_list, format)

#if defined(__cplusplus)
 template<typename T> T __intellisense__return_T();
 #define __intellisense__builtin_va_arg(__builtin_va_list, type) __intellisense__return_T<type>()
#else /* !defined(__cplusplus) */
 void __intellisense__builtin_va_arg(__builtin_va_list, __intellisense_type);
#endif /* defined(__cplusplus) */

#define __builtin_va_arg(__builtin_va_list, type) __intellisense__builtin_va_arg(__builtin_va_list, type)
void __builtin_va_end (__builtin_va_list);
void __builtin_va_copy ( __builtin_va_list dest, __builtin_va_list src );
void * __builtin_memset ( void * ptr, int value, size_t num );
void * __builtin_memcpy ( void * destination, const void * source, size_t num );
void *__builtin_alloca (long size);
void __builtin_trap (void);
#define __intellisense__builtin_offsetof(type, member) 0
#define __builtin_offsetof(type, member) __intellisense__builtin_offsetof(type, member)
void * __builtin_return_address (unsigned int level);

#if defined(__cplusplus)

 #define BUILTIN_ATOMIC_FN_T(type) \
 type __sync_fetch_and_add (volatile type *ptr, type value, ...); \
 type __sync_fetch_and_sub (volatile type *ptr, type value, ...); \
 type __sync_fetch_and_or (volatile type *ptr, type value, ...); \
 type __sync_fetch_and_and (volatile type *ptr, type value, ...); \
 type __sync_fetch_and_xor (volatile type *ptr, type value, ...); \
 type __sync_add_and_fetch (volatile type *ptr, type value, ...); \
 type __sync_sub_and_fetch (volatile type *ptr, type value, ...); \
 type __sync_or_and_fetch (volatile type *ptr, type value, ...); \
 type __sync_and_and_fetch (volatile type *ptr, type value, ...); \
 type __sync_xor_and_fetch (volatile type *ptr, type value, ...); \
 bool __sync_bool_compare_and_swap (volatile type *ptr, type oldval, type newval, ...); \
 type __sync_val_compare_and_swap (volatile type *ptr, type compare, type swap, ...); \
 type __sync_lock_test_and_set (volatile type *ptr, type value, ...); \
 void __sync_lock_release (volatile type *ptr, ...); \

 BUILTIN_ATOMIC_FN_T(__intellisense_int8t)
 BUILTIN_ATOMIC_FN_T(__intellisense_int16t)
 BUILTIN_ATOMIC_FN_T(__intellisense_int32t)
 BUILTIN_ATOMIC_FN_T(__intellisense_int64t)
 BUILTIN_ATOMIC_FN_T(__intellisense_int128t)

 #undef BUILTIN_ATOMIC_FN_T

#else /* !defined(__cplusplus) */

 int __sync_fetch_and_add (volatile __intellisense_type *ptr, __intellisense_type value, ...);
 int __sync_fetch_and_sub (volatile __intellisense_type *ptr, __intellisense_type value, ...);
 int __sync_fetch_and_or (volatile __intellisense_type *ptr, __intellisense_type value, ...);
 int __sync_fetch_and_and (volatile __intellisense_type *ptr, __intellisense_type value, ...);
 int __sync_fetch_and_xor (volatile __intellisense_type *ptr, __intellisense_type value, ...);
 int __sync_add_and_fetch (volatile __intellisense_type *ptr, __intellisense_type value, ...);
 int __sync_sub_and_fetch (volatile __intellisense_type *ptr, __intellisense_type value, ...);
 int __sync_or_and_fetch (volatile __intellisense_type *ptr, __intellisense_type value, ...);
 int __sync_and_and_fetch (volatile __intellisense_type *ptr, __intellisense_type value, ...);
 int __sync_xor_and_fetch (volatile __intellisense_type *ptr, __intellisense_type value, ...);
 int __sync_bool_compare_and_swap (volatile __intellisense_type *ptr, __intellisense_type oldval, __intellisense_type newval, ...);
 int __sync_val_compare_and_swap (volatile __intellisense_type *ptr, __intellisense_type compare, __intellisense_type swap, ...);
 int __sync_lock_test_and_set (volatile __intellisense_type *ptr, __intellisense_type value, ...);
 void __sync_lock_release (volatile __intellisense_type *ptr, ...);

#endif /* defined(__cplusplus) */

#if defined(__cplusplus)
 void __sync_synchronize(...);
#else
 #define __sync_synchronize(...)
#endif

/* Clang specific built-ins from http://clang.llvm.org/docs/LanguageExtensions.html */

void __builtin_assume(bool);
unsigned long long __builtin_readcyclecounter();
void __builtin_unreachable();
bool __builtin_unpredictable(long long);
#define __intellisense__builtin_convertvector(src_vec, dst_vec_type) (void)0
#define __builtin_convertvector(src_vec, dst_vec_type) __intellisense__builtin_convertvector(src_vec, dst_vec_type)
#define __intellisense__builtin_addressof(value) 0
#define __builtin_addressof(value) __intellisense__builtin_addressof(value)

#if defined(__cplusplus)
 template<typename T> T __builtin_shufflevector(T vec1, T vec2, int index1, ...);
 template<typename T> T __sync_swap(T * ptr, T value, ...);
#else /* !defined(__cplusplus) */
 __intellisense_type __builtin_shufflevector(__intellisense_type vec1, __intellisense_type vec2, int index1, ...);
 __intellisense_type __sync_swap(__intellisense_type * ptr, __intellisense_type value, ...);
#endif /* defined(__cplusplus) */

/* Clang Multiprecision Arithmetic builtins */
unsigned char      __builtin_addcb (unsigned char x, unsigned char y, unsigned char carryin, unsigned char *carryout);
unsigned short     __builtin_addcs (unsigned short x, unsigned short y, unsigned short carryin, unsigned short *carryout);
unsigned           __builtin_addc  (unsigned x, unsigned y, unsigned carryin, unsigned *carryout);
unsigned long      __builtin_addcl (unsigned long x, unsigned long y, unsigned long carryin, unsigned long *carryout);
unsigned long long __builtin_addcll(unsigned long long x, unsigned long long y, unsigned long long carryin, unsigned long long *carryout);
unsigned char      __builtin_subcb (unsigned char x, unsigned char y, unsigned char carryin, unsigned char *carryout);
unsigned short     __builtin_subcs (unsigned short x, unsigned short y, unsigned short carryin, unsigned short *carryout);
unsigned           __builtin_subc  (unsigned x, unsigned y, unsigned carryin, unsigned *carryout);
unsigned long      __builtin_subcl (unsigned long x, unsigned long y, unsigned long carryin, unsigned long *carryout);
unsigned long long __builtin_subcll(unsigned long long x, unsigned long long y, unsigned long long carryin, unsigned long long *carryout);

/* Clang Checked Arithmetic builtins */
#if defined(__cplusplus) 
 template<typename T1, typename T2, typename T3> bool __builtin_add_overflow (T1 x, T2 y, T3 *sum);
 template<typename T1, typename T2, typename T3> bool __builtin_sub_overflow (T1 x, T2 y, T3 *diff);
 template<typename T1, typename T2, typename T3> bool __builtin_mul_overflow (T1 x, T2 y, T3 *prod);
#else /* !defined(__cplusplus) */
 bool __builtin_add_overflow (__intellisense_type1 x, __intellisense_type2 y, __intellisense_type3 *sum);
 bool __builtin_sub_overflow (__intellisense_type1 x, __intellisense_type2 y, __intellisense_type3 *diff);
 bool __builtin_mul_overflow (__intellisense_type1 x, __intellisense_type2 y, __intellisense_type3 *prod);
#endif /* defined(__cplusplus) */
bool __builtin_uadd_overflow  (unsigned x, unsigned y, unsigned *sum);
bool __builtin_uaddl_overflow (unsigned long x, unsigned long y, unsigned long *sum);
bool __builtin_uaddll_overflow(unsigned long long x, unsigned long long y, unsigned long long *sum);
bool __builtin_usub_overflow  (unsigned x, unsigned y, unsigned *diff);
bool __builtin_usubl_overflow (unsigned long x, unsigned long y, unsigned long *diff);
bool __builtin_usubll_overflow(unsigned long long x, unsigned long long y, unsigned long long *diff);
bool __builtin_umul_overflow  (unsigned x, unsigned y, unsigned *prod);
bool __builtin_umull_overflow (unsigned long x, unsigned long y, unsigned long *prod);
bool __builtin_umulll_overflow(unsigned long long x, unsigned long long y, unsigned long long *prod);
bool __builtin_sadd_overflow  (int x, int y, int *sum);
bool __builtin_saddl_overflow (long x, long y, long *sum);
bool __builtin_saddll_overflow(long long x, long long y, long long *sum);
bool __builtin_ssub_overflow  (int x, int y, int *diff);
bool __builtin_ssubl_overflow (long x, long y, long *diff);
bool __builtin_ssubll_overflow(long long x, long long y, long long *diff);
bool __builtin_smul_overflow  (int x, int y, int *prod);
bool __builtin_smull_overflow (long x, long y, long *prod);
bool __builtin_smulll_overflow(long long x, long long y, long long *prod);

/* Clang Floating point builtins */
double __builtin_canonicalize(double);
float __builtin_canonicalizef(float);
long double__builtin_canonicalizel(long double);

/* Clang __c11_atomic builtins */
#define __c11_atomic_init (void)0
#define __c11_atomic_thread_fence(order) (void)0
#define __c11_atomic_signal_fence(order) (void)0
#define __c11_atomic_is_lock_free(sizeof_addr_obj) (void)0
#define __c11_atomic_store(object, desired, __ATOMIC_SEQ_CST) (void)0
#define __c11_atomic_load(object, __ATOMIC_SEQ_CST) (void)0
#define __c11_atomic_exchange(object, desired, __ATOMIC_SEQ_CST) (void)0
#define __c11_atomic_compare_exchange_strong(object, expected, desired, __ATOMIC_SEQ_CST) (void)0
#define __c11_atomic_compare_exchange_weak(object, expected, desired, __ATOMIC_SEQ_CST) (void)0
#define __c11_atomic_fetch_add(object, operand, __ATOMIC_SEQ_CST) (void)0
#define __c11_atomic_fetch_sub(object, operand, __ATOMIC_SEQ_CST) (void)0
#define __c11_atomic_fetch_and(object, operand, __ATOMIC_SEQ_CST) (void)0
#define __c11_atomic_fetch_or(object, operand, __ATOMIC_SEQ_CST) (void)0
#define __c11_atomic_fetch_xor(object, operand, __ATOMIC_SEQ_CST) (void)0

/* Clang Non-temporal load/store builtins */
#if defined(__cplusplus)
 template<typename T> T __builtin_nontemporal_load(T *addr);
 template<typename T> void __builtin_nontemporal_store(T value, T *addr);
#else /* !defined(__cplusplus) */
 __intellisense_type __builtin_nontemporal_load(__intellisense_type *addr);
 void __builtin_nontemporal_store(__intellisense_type value, __intellisense_type *addr);
#endif /* defined(__cplusplus) */

#if !defined(__cplusplus)
 #undef size_t
 #undef bool
#endif
