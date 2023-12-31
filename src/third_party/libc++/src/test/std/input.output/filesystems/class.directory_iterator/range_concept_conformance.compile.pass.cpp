//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03, c++11, c++14, c++17
// UNSUPPORTED: no-filesystem
// UNSUPPORTED: availability-filesystem-missing

// directory_iterator

#include "filesystem_include.h"

#include <concepts>
#include <ranges>

static_assert(std::same_as<std::ranges::iterator_t<fs::directory_iterator>, fs::directory_iterator>);
static_assert(std::ranges::common_range<fs::directory_iterator>);
static_assert(std::ranges::input_range<fs::directory_iterator>);
static_assert(std::ranges::view<fs::directory_iterator>);
static_assert(!std::ranges::sized_range<fs::directory_iterator>);
static_assert(std::ranges::borrowed_range<fs::directory_iterator>);
static_assert(std::ranges::viewable_range<fs::directory_iterator>);

static_assert(std::same_as<std::ranges::iterator_t<fs::directory_iterator&>, fs::directory_iterator>);
static_assert(std::ranges::common_range<fs::directory_iterator&>);
static_assert(std::ranges::input_range<fs::directory_iterator&>);
static_assert(!std::ranges::view<fs::directory_iterator&>);
static_assert(!std::ranges::sized_range<fs::directory_iterator&>);
static_assert(std::ranges::borrowed_range<fs::directory_iterator&>);
static_assert(std::ranges::viewable_range<fs::directory_iterator&>);

static_assert(std::same_as<std::ranges::iterator_t<const fs::directory_iterator&>, fs::directory_iterator>);
static_assert(std::ranges::common_range<const fs::directory_iterator&>);
static_assert(std::ranges::input_range<const fs::directory_iterator&>);
static_assert(!std::ranges::view<const fs::directory_iterator&>);
static_assert(!std::ranges::sized_range<const fs::directory_iterator&>);
static_assert(std::ranges::borrowed_range<const fs::directory_iterator&>);
static_assert(std::ranges::viewable_range<const fs::directory_iterator&>);

