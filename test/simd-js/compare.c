/* Copyright (c) 2017 Evan Nemerson <evan@nemerson.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <test/simd-js/simd-js.h>

#if defined(__EMSCRIPTEN__)
#define SIMDE_EM_NO_NATIVE
#include <simde/simd-js/simd-js.h>
#include <emscripten/vector.h>

#define DEFINE_TEST_EM_BINARY(T, op)					\
  static MunitResult							\
  test_simde_em_##T##_##op(const MunitParameter params[], void* data) { \
    (void) params;							\
    (void) data;							\
									\
    T na, nb, nr;							\
    simde_em_##T ea, eb, er;						\
									\
    munit_rand_memory(sizeof(na), (uint8_t*) &na);			\
    munit_rand_memory(sizeof(nb), (uint8_t*) &nb);			\
    memcpy(&ea, &na, sizeof(na));					\
    memcpy(&eb, &nb, sizeof(nb));					\
									\
    nr = emscripten_##T##_##op(na, nb);					\
    er = simde_em_##T##_##op(ea, eb);					\
									\
    simde_assert_##T(nr, ==, er);					\
									\
    return MUNIT_OK;							\
  }

DEFINE_TEST_EM_BINARY(int32x4, add)
DEFINE_TEST_EM_BINARY(int32x4, sub)
DEFINE_TEST_EM_BINARY(int32x4, mul)

static MunitTest test_suite_tests[] = {
  TEST_FUNC_CMP(em_int32x4_add),
  TEST_FUNC_CMP(em_int32x4_sub),
  TEST_FUNC_CMP(em_int32x4_mul),

  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};
#else
static MunitTest test_suite_tests[] = {
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};
#endif

MunitSuite simde_simd_js_cmp_test_suite = {
  (char*) "",
  test_suite_tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};
