//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: !stdlib=libc++ && (c++03 || c++11 || c++14)

// <string_view>

// [string.view.capacity], capacity
// constexpr size_type size()     const noexcept;
// constexpr size_type length()   const noexcept;
// constexpr size_type max_size() const noexcept;
// constexpr bool empty()         const noexcept;

#include <string_view>
#include <cassert>
#include <iterator>
#include <limits>

#include "test_macros.h"

template <typename SV>
void test1() {
#if TEST_STD_VER > 11
  {
    constexpr SV sv1;
    static_assert(sv1.size() == 0, "");
    static_assert(sv1.empty(), "");
    static_assert(sv1.size() == sv1.length(), "");
    static_assert(sv1.max_size() > sv1.size(), "");
  }
#endif

  {
    SV sv1;
    ASSERT_NOEXCEPT(sv1.size());
    ASSERT_NOEXCEPT(sv1.empty());
    ASSERT_NOEXCEPT(sv1.max_size());
    ASSERT_NOEXCEPT(sv1.length());
    assert(sv1.size() == 0);
    assert(sv1.empty());
    assert(sv1.size() == sv1.length());
    assert(sv1.max_size() > sv1.size());
  }

  // Sanity check max_size() -- a string_view can't store more bytes than a single object
  // can contain. Any implementation that fails this check is certainly lying.
  {
    typedef typename SV::value_type CharT;
    typedef typename SV::size_type Size;
    SV sv;
    assert(sv.max_size() <= std::numeric_limits<Size>::max() / sizeof(CharT));
    LIBCPP_ASSERT(sv.max_size() == std::numeric_limits<Size>::max() / sizeof(CharT));
  }
}

template <typename CharT>
void test2(const CharT* s, std::size_t len) {
  {
    std::basic_string_view<CharT> sv1(s);
    assert(sv1.size() == len);
    assert(sv1.data() == s);
    assert(sv1.empty() == (len == 0));
    assert(sv1.size() == sv1.length());
    assert(sv1.max_size() > sv1.size());
#if TEST_STD_VER > 14
    //  make sure we pick up std::size, too!
    assert(sv1.size() == std::size(sv1));
    assert(sv1.empty() == std::empty(sv1));
#endif
  }
}

int main(int, char**) {
  test1<std::string_view>();
#ifndef TEST_HAS_NO_CHAR8_T
  test1<std::u8string_view>();
#endif
  test1<std::u16string_view>();
  test1<std::u32string_view>();
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
  test1<std::wstring_view>();
#endif

  test2("ABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDE",
        105);
  test2("ABCDE", 5);
  test2("a", 1);
  test2("", 0);

#ifndef TEST_HAS_NO_WIDE_CHARACTERS
  test2(L"ABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDE",
        105);
  test2(L"ABCDE", 5);
  test2(L"a", 1);
  test2(L"", 0);
#endif

#ifndef TEST_HAS_NO_CHAR8_T
  test2(u8"ABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDE",
        105);
  test2(u8"ABCDE", 5);
  test2(u8"a", 1);
  test2(u8"", 0);
#endif

#if TEST_STD_VER >= 11
  test2(u"ABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDE",
        105);
  test2(u"ABCDE", 5);
  test2(u"a", 1);
  test2(u"", 0);

  test2(U"ABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDEABCDE",
        105);
  test2(U"ABCDE", 5);
  test2(U"a", 1);
  test2(U"", 0);
#endif

  return 0;
}
