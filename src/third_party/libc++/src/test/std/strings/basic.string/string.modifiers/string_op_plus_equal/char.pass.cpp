//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <string>

// basic_string<charT,traits,Allocator>& operator+=(charT c); // constexpr since C++20

#include <string>
#include <cassert>

#include "test_macros.h"
#include "min_allocator.h"

template <class S>
TEST_CONSTEXPR_CXX20 void test(S s, typename S::value_type str, S expected) {
  s += str;
  LIBCPP_ASSERT(s.__invariants());
  assert(s == expected);
}

template <class S>
TEST_CONSTEXPR_CXX20 void test_string() {
  test(S(), 'a', S("a"));
  test(S("12345"), 'a', S("12345a"));
  test(S("1234567890"), 'a', S("1234567890a"));
  test(S("12345678901234567890"), 'a', S("12345678901234567890a"));
}

TEST_CONSTEXPR_CXX20 bool test() {
  test_string<std::string>();
#if TEST_STD_VER >= 11
  test_string<std::basic_string<char, std::char_traits<char>, min_allocator<char> > >();
#endif

  return true;
}

int main(int, char**) {
  test();
#if TEST_STD_VER > 17
  static_assert(test());
#endif

  return 0;
}
